

#include <tile/tile_store_box.h>
#include <tile/tile_store.h>

// stl
#include <stdexcept>
#include <map>

// static plugin linkage
#ifdef STATIC_TILESTORE_PLUGINS
    #if defined(STATIC_TILESTORE_PLUGIN_DISK)
        #include "tilestore/disk/disk_tilestore.h"
    #endif
#endif

namespace datamaps {

#ifdef STATIC_TILESTORE_PLUGINS
template<typename T>
tilestore_ptr tilestore_generator()
{
    return std::make_shared<T>(T());
}

typedef tilestore_ptr (*tilestore_generator_ptr)();
typedef std::map<std::string, tilestore_generator_ptr> tilestore_map;

class TileStoreMap : public tilestore_map
{
public:
    TileStoreMap()
    {
#if defined(STATIC_TILESTORE_PLUGIN_DISK)
        (*this)["disk_tilestore"] = &tilestore_generator<DiskTileStore>;
#endif
    }
};

static TileStoreMap satic_tilestores;

#endif

#ifdef STATIC_TILESTORE_PLUGINS
tilestore_ptr create_static_tilestore(std::string type)
{
    tilestore_ptr ts;
    tilestore_map::iterator it = satic_tilestores.find(type);
    if (it != satic_tilestores.end())
    {
        ts = it->second();
    }
    return ts;
}
#else
tilestore_ptr create_static_tilestore(std::string type)
{
    return tilestore_ptr();
}
#endif

std::vector<std::string> get_static_tilestore_names()
{
    std::vector<std::string> names;

#ifdef STATIC_TILESTORE_PLUGINS
    tilestore_map::iterator it = satic_tilestores.begin();
    while (it != satic_tilestores.end())
    {
        names.push_back(it->first);

        it++;
    }
#endif

    return names;
}

}
