#ifndef DATAMAPS_TILEPOOL_H
#define DATAMAPS_TILEPOOL_H

#include <tile/tile.h>

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>

#include <string>
#include <queue>

namespace datamaps {
/**
 * @brief The TilePool struct
 */
struct TilePool
{
	TilePool();

	/**
     * @brief	向队列中添加瓦片
     * @param	tile	入队的瓦片
	**/
    void push(Tile& tile);

    /**
     * @brief	从队列中移除瓦片
     * @return	tile	出队的瓦片
    **/
    Tile& pop();

    /**
     * @brief	获取队列中瓦片个数
     * @return  个数
    **/
    int size();

    /**
     * @brief	check队列是否设置结束
     * @return  是否结束添加
    **/
    bool check_finish();

    /**
     * @brief	设置结束添加
	 */
    void finish();

    /**
     * @brief	重置所有成员变量到初始状态
	 */
    void reset();

public:
    std::queue<Tile> tilepool_;         ///<用于存储所有瓦片的队列
    std::size_t maxitems_;              ///<队列最大值
    bool finished_;						///<标示是否还会有新的瓦片添加到队列中
    boost::condition cond_;             ///<线程条件变量,用于瓦片池中瓦片数量过多时线程暂停等待
    // TODO 使用read_write_mutex区分读写锁可进一步提高效率
    boost::mutex mutex_;                ///<队列锁,用来保证队列读取和写入的唯一性
};
}

#endif  //DATAMAPS_TILEPOOL_H
