#include <tile/tile_mix.h>

//#include <FreeImage.h>

namespace datamaps {

Tile& tile_mix(std::vector<Tile> tile_list)
{
    Tile new_tile;
    Tile& tile = tile_list[0];
    TILE_FORMAT format = tile.format_;
    if (int(format) < 40)   // handle by freeimage
    {
        ;
    }
    else if(format == TF_GeoJSON)
    {
        ;
    }
    else if(format == TF_TopoJSON)
    {
        ;
    }
    else if(format == TF_MB_Vector)
    {
        ;
    }
    else if(format == TF_UTFGrid)
    {
        ;
    }
    else
    {
        ;
    }
    return new_tile;
}

}
