#ifndef DATAMAPS_TILEIO_H
#define DATAMAPS_TILEIO_H

#include <tile/tile.h>
#include <tile/tile_pool.h>
#include <tile/tile_store.h>

#include <vector>

namespace datamaps {

void async_save(TilePool* tile_pool, TileStore* tile_store, int max_threads = 8);
void save_thread(TilePool* tile_pool, TileStore* tile_store);
void async_load(TilePool* src_tile_pool, TilePool* dist_tile_pool, TileStore* tile_store, int max_threads = 8);
void load_thread(TilePool* src_tile_pool, TilePool* dist_tile_pool, TileStore* tile_store);

void sync_pool_to_list(TilePool* tile_pool, std::vector<Tile> tile_list);
void sync_list_to_pool(TilePool* tile_pool, std::vector<Tile> tile_list);

}
#endif // DATAMAPS_TILEIO_H
