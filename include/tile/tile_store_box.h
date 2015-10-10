#ifndef TILESTOREBOX_H
#define TILESTOREBOX_H

#include <tile/tile_store.h>
#include <tile/plugin.h>

#include <vector>
#include <map>
#include <set>
#include <memory>

namespace datamaps {

class TileStoreBox
{
public:
    TileStoreBox();
    ~TileStoreBox();

    tilestore_ptr create(std::string type);

    bool has_tilestore(std::string type);
    bool register_tilestores(std::string const& path, bool recurse = false);
    bool register_tilestore(std::string const& filename);

    std::vector<std::string> plugin_names();
    std::string plugin_directories();


private:
    std::map<std::string, std::shared_ptr<PluginInfo>> plugins_;
    std::vector<std::string> plugin_directories_;
};

}
#endif // TILESTOREBOX_H
