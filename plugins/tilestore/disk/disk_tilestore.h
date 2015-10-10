#ifndef DISK_TILESTORE_H
#define DISK_TILESTORE_H

#include <tile/tile_store.h>

namespace datamaps {

class DiskTileStore : public TileStore
{
public:
    DiskTileStore();
    virtual bool load(Tile& tile);
    virtual bool save(Tile& tile);
    virtual bool remove(Tile& tile);

    virtual bool create_dir(int level1, int level2);

    static const char* name()
    {
        std::string name = "disk_tilestore";
        return name.c_str();
    }

    static const char* version()
    {
        std::string version = "1.0.0";
        return version.c_str();
    }

    static const char* description()
    {
        std::string description = "simple disk tile store";
        return description.c_str();
    }

protected:

    /**
     * @brief get_tile_name     get the tile filepath
     * @param tile              Tile, the tile
     * @return                  filepath
     */
    virtual std::string get_tile_name(Tile& tile);

    std::string get_extension(TILE_FORMAT tf);
};

}
#endif // DISK_TILESTORE_H
