#include <tile/tile_store_box.h>

#include <map>
#include <string>
#include <exception>

namespace datamaps
{

extern tilestore_ptr create_static_tilestore(std::string type);
extern std::vector<std::string> get_static_tilestore_names();

inline static std::string& join(std::vector<std::string>& elems, std::string delim)
{
    std::string s;
    for (auto it = elems.begin(); it != elems.end(); ++it)
    {
        s += (*it);
        if ( it + 1 != elems.end() ) {
            s += delim;
        }
    }
    return s;
}

inline static bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

bool is_tilestore_plugin(std::string const& filename)
{
    return ends_with(filename,std::string(".tiles"));
}

TileStoreBox::TileStoreBox()
{
    PluginInfo::init();
}

TileStoreBox::~TileStoreBox()
{
    PluginInfo::exit();
}

tilestore_ptr TileStoreBox::create(std::string type)
{
    tilestore_ptr tile_store;

#ifdef STATIC_TILESTORE_PLUGINS
    tile_store = create_static_tilestore(type);
    if (tile_store)
    {
        return tile_store;
    }
#endif

    std::map<std::string,std::shared_ptr<PluginInfo> >::iterator itr;
    // add scope to ensure lock is released asap
    {
#ifdef DATAMAPS_THREADSAFE
        std::lock_guard<std::recursive_mutex> lock(instance_mutex_);
#endif
        itr=plugins_.find(type);
        if (itr == plugins_.end())
        {
            std::string s("Could not create tilestore for type: '");
            s += type + "'";
            if (plugin_directories_.empty())
            {
                s += " (no tilestore plugin directories have been successfully registered)";
            }
            else
            {
                s += " (searched for tilestore plugins in '" + plugin_directories() + "')";
            }
//            throw std::exception(s);
        }
    }

    if (! itr->second->valid())
    {
        throw std::runtime_error(std::string("Cannot load library: ") +
                                 itr->second->get_error());
    }

    create_tilestore create_ts = reinterpret_cast<create_tilestore>(itr->second->get_symbol("create"));

    if (! create_ts)
    {
        throw std::runtime_error(std::string("Cannot load symbols: ") +
                                 itr->second->get_error());
    }

    tile_store = tilestore_ptr(create_ts(type.c_str()), TileStore_Deleter());

    return tile_store;
}

bool TileStoreBox::has_tilestore(std::string type)
{
    bool success = false;
    std::vector<std::string> names = plugin_names();
    for (auto it = names.begin(); it != names.end(); ++it)
    {
        if (type == *it)
        {
            success = true;
            break;
        }
    }
    return success;
}

bool TileStoreBox::register_tilestores(std::string const& /*path*/, bool /*recurse*/)
{
    return true;
}

bool TileStoreBox::register_tilestore(std::string const& filename)
{
    try
    {
        std::shared_ptr<PluginInfo> plugin = std::make_shared<PluginInfo>(PluginInfo(filename, "tilestore_name"));
        if (plugin->valid())
        {
            if (plugin->name().empty())
            {
            }
            else
            {
                plugins_.insert(std::make_pair(plugin->name(), plugin));
                return true;
            }
        }
        else
        {
        }
    }
    catch(std::exception const& ex)
    {
    }
    return false;
}

std::vector<std::string> TileStoreBox::plugin_names()
{
    std::vector<std::string> names;

#ifdef STATIC_TILESTORE_PLUGINS
    names = get_static_tilestore_names();
#endif

    for(auto it = plugins_.begin(); it != plugins_.end(); ++it)
    {
        names.push_back(it->first);
    }
    return names;
}

std::string TileStoreBox::plugin_directories()
{
    std::string directories = join(plugin_directories_, ", ");
    return directories;
}

}
