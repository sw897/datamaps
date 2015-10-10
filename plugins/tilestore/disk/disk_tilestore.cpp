#include <tilestore/disk/disk_tilestore.h>

#include <boost/filesystem.hpp>
#include <boost/locale.hpp>

#include <sstream>

namespace datamaps {

TILESTORE_PLUGIN(DiskTileStore)

DiskTileStore::DiskTileStore()
{
	// Create and install global locale
	std::locale::global(boost::locale::generator().generate(""));
	// Make boost.filesystem use it
	boost::filesystem::path::imbue(std::locale());
}

bool DiskTileStore::load(Tile& tile)
{
    std::string tilepath = get_tile_name(tile);
    bool success = false;

    return success;
}

bool DiskTileStore::save(Tile& tile)
{
    std::string tilepath = get_tile_name(tile);
    bool success = false;
    ;
    return success;
}

bool DiskTileStore::remove(Tile& tile)
{
    std::string tilePath = get_tile_name(tile);
	return boost::filesystem::remove(tilePath);
}

std::string DiskTileStore::get_extension(TILE_FORMAT tf)
{
    switch(tf)
	{
        case TF_DDS:
            return ".dds";
        case TF_JPEG:
            return ".jpg";
        case TF_PNG:
            return ".png";
        case TF_GeoJSON:
            return ".geojson";
	}
	return "";
}

std::string DiskTileStore::get_tile_name(Tile& tile)
{
    std::ostringstream str;
    str << path_ << "/" << tile.level_ << "/" << tile.col_ << "/" << tile.row_
        << get_extension(tile.format_);
    return str.str();
}

bool DiskTileStore::create_dir(int level1, int level2)
{
    std::ostringstream str;
    str << path_ << "/" << level1 << "/" << level2 << "/";
    std::string dirPath = str.str();
	return boost::filesystem::create_directories(dirPath.c_str());
}

}
