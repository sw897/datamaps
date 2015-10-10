#include <tile/tile_io.h>

#include <boost/threadpool.hpp>

namespace datamaps {


void async_save(TilePool* tile_pool, TileStore* tile_store, int max_threads)
{
    boost::threadpool::pool thread_pool(max_threads);
    thread_pool.schedule(boost::bind(save_thread, tile_pool, tile_store));
    thread_pool.wait();
}

void save_thread(TilePool* tile_pool, TileStore* tile_store)
{
    bool bfinished = tile_pool->check_finish();
    int item_count = tile_pool->size();
    while (!bfinished || 0 < item_count)
    {
        if (0 != item_count)
        {
            Tile& tile = tile_pool->pop();
            if (tile.buf_)
                tile_store->save(tile);
        }

        item_count = tile_pool->size();
        bfinished = tile_pool->check_finish();
    }
}

void async_load(TilePool* src_tile_pool, TilePool* dist_tile_pool, TileStore* tile_store, int max_threads)
{
    boost::threadpool::pool thread_pool(max_threads);
    thread_pool.schedule(boost::bind(load_thread, src_tile_pool, dist_tile_pool, tile_store));
    thread_pool.wait();
}

void load_thread(TilePool* src_tile_pool, TilePool* dist_tile_pool, TileStore* tile_store)
{
    bool bfinished = src_tile_pool->check_finish();
    int item_count = src_tile_pool->size();
    while (!bfinished || 0 < item_count)
    {
        if (0 != item_count)
        {
            Tile& tile = src_tile_pool->pop();
            if (tile.valid_)
            {
                tile_store->load(tile);
                dist_tile_pool->push(tile);
            }
        }

        item_count = src_tile_pool->size();
        bfinished = src_tile_pool->check_finish();
    }
}

void sync_pool_to_list(TilePool* tile_pool, std::vector<Tile> tile_list)
{
    boost::unique_lock<boost::mutex> lock(tile_pool->mutex_);
    bool bfinished = tile_pool->check_finish();
    if(bfinished)
    {
        while(tile_pool->size() > 0)
        {
            tile_list.push_back(tile_pool->pop());
        }
    }
}

void sync_list_to_pool(TilePool* tile_pool, std::vector<Tile> tile_list)
{
    for (auto it = tile_list.begin(); it != tile_list.end(); ++it)
    {
        tile_pool->push(*it);
    }
}

}
