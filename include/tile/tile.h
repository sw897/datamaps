#ifndef DATAMAPS_TILE_H
#define DATAMAPS_TILE_H

#include <tile/tile_format.h>

namespace datamaps {
/**
 * @brief The Tile struct
 */
struct Tile
{
    /**
     * @brief Tile          瓦片构造函数，根据指定的层级以及行列号构建瓦片
     * @param level         瓦片所在层级
     * @param col           瓦片所在列号
     * @param row           瓦片所在行号
     */

    Tile(int level, int col, int row)
        : level_(level), col_(col), row_(row), face_(-1), buf_(nullptr), valid_(true), format_(TF_UNKNOWN)
    {}

    Tile(int level, int col, int row, int face)
        : level_(level), col_(col), row_(row), face_(face), buf_(nullptr), valid_(true), format_(TF_UNKNOWN)
    {}

    Tile()
        : level_(-1), col_(-1), row_(-1), face_(-1), buf_(nullptr), valid_(false), format_(TF_UNKNOWN)
    {}

    virtual ~Tile()
    {
        if (buf_ != nullptr)
        {
            delete buf_;
            buf_ = nullptr;
        }
    }

    int level_;         ///< 瓦片所属层级，最低为0级
    int row_;           ///< 瓦片在该层所属行号
    int col_;           ///< 瓦片在该层所属列号
    int face_;          ///< 全景瓦片标识瓦片所在cube面
    char* buf_;         ///< 瓦片数据内容
    bool valid_;        ///< 瓦片是否有效
    TILE_FORMAT format_;///< 瓦片类型

};
}
#endif // DATAMAPS_TILE_H
