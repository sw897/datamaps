#ifndef DATAMAPS_TILESTORE_H
#define DATAMAPS_TILESTORE_H

#include <tile/tile.h>
#include <tile/config.h>

#include <string>
#include <memory>

namespace datamaps {
/**
 * @brief tile store引擎抽象基类
 *
 * 用于统一进行瓦片存储操作
 */
struct TileStore
{
    TileStore() {}
    virtual ~TileStore() {}

    /**
     * @brief load      加载瓦片
     * @param tile      需要加载瓦片
     * @return          成功获取返回true,否则返回false
     */
    virtual bool load(Tile& tile) = 0;

    /**
     * @brief save      保存瓦片
     * @param tile      需要保存的瓦片
     * @return          成功保存返回true,否则返回false
     */
    virtual bool save(Tile& tile) = 0;

    /**
     * @brief remove    删除瓦片
     * @param tile      需要删除的瓦片
     * @return          成功保存返回true,否则返回false
     */
    virtual bool remove(Tile& tile) = 0;

    std::string path_;
};


typedef const char* (*tilestore_profile) ();
typedef TileStore* (*create_tilestore) (const char *);
typedef void (*destroy_tilestore) (TileStore *);

class TileStore_Deleter
{
public:
    void operator() (TileStore* tile_store)
    {
        delete tile_store;
    }
};

typedef std::shared_ptr<TileStore> tilestore_ptr;

#ifdef STATIC_TILESTORE_PLUGINS
    #define TILESTORE_PLUGIN(classname)
#else
    #define TILESTORE_PLUGIN(classname)                                       \
        extern "C" DATAMAPS_EXP const char * tilestore_name()                 \
        {                                                                     \
            return classname::name();                                         \
        }                                                                     \
        extern "C" DATAMAPS_EXP const char * tilestore_version()              \
        {                                                                     \
            return classname::version();                                      \
        }                                                                     \
        extern "C" DATAMAPS_EXP const char * tilestore_description()          \
        {                                                                     \
            return classname::description();                                  \
        }                                                                     \
        extern "C"  DATAMAPS_EXP TileStore* create()                          \
        {                                                                     \
            return new classname();                                           \
        }                                                                     \
        extern "C" DATAMAPS_EXP void destroy(TileStore *tile_store)           \
        {                                                                     \
            delete tile_store;                                                \
        }
#endif


}
#endif  //DATAMAPS_TILEPOOL_H
