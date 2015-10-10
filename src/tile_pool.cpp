#include <tile/tile_pool.h>

namespace datamaps {

const static int THREADPOOL_MAXSIZE = 8;

TilePool::TilePool()
    :finished_(false), maxitems_(256)
{
}

void TilePool::push(Tile& tile)
{
    boost::mutex::scoped_lock lock(mutex_);

    if (finished_)
		return;

    while (maxitems_ < tilepool_.size())
        cond_.wait(lock);

    tilepool_.push(tile);
}

Tile& TilePool::pop()
{
    boost::unique_lock<boost::mutex> lock(mutex_);
    int itemCount = tilepool_.size();
    if (0 != itemCount && !finished_)
    {
        if (maxitems_ * 0.6 >= itemCount)
            cond_.notify_all();

        Tile& tile = tilepool_.front();
        tilepool_.pop();
        return tile;
    }
    return Tile();
}

int TilePool::size()
{
    boost::mutex::scoped_lock lock(mutex_);
    return tilepool_.size();
}

bool TilePool::check_finish()
{
    boost::mutex::scoped_lock lock(mutex_);
    return finished_;
}

void TilePool::finish()
{
    boost::mutex::scoped_lock lock(mutex_);
    finished_ = true;
}

void TilePool::reset()
{
    boost::mutex::scoped_lock lock(mutex_);
    finished_ = false;
    while(tilepool_.size() != 0)
        tilepool_.pop();
}


}
