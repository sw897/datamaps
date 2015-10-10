#ifndef DATAMAPS_TILE_FORMAT
#define DATAMAPS_TILE_FORMAT

namespace datamaps {

/**
 * @brief The TILE_FORMAT enum, 依据 FreeImageFormat 扩展
 */
enum TILE_FORMAT
{
    TF_UNKNOWN = -1,
    TF_BMP		= 0,
    TF_ICO		= 1,
    TF_JPEG     = 2,
    TF_JNG		= 3,
    TF_KOALA	= 4,
    TF_LBM		= 5,
    TF_IFF = TF_LBM,
    TF_MNG		= 6,
    TF_PBM		= 7,
    TF_PBMRAW	= 8,
    TF_PCD		= 9,
    TF_PCX		= 10,
    TF_PGM		= 11,
    TF_PGMRAW	= 12,
    TF_PNG		= 13,
    TF_PPM		= 14,
    TF_PPMRAW	= 15,
    TF_RAS		= 16,
    TF_TARGA	= 17,
    TF_TIFF     = 18,
    TF_WBMP     = 19,
    TF_PSD		= 20,
    TF_CUT		= 21,
    TF_XBM		= 22,
    TF_XPM		= 23,
    TF_DDS		= 24,
    TF_GIF      = 25,
    TF_HDR		= 26,
    TF_FAXG3	= 27,
    TF_SGI		= 28,
    TF_EXR		= 29,
    TF_J2K		= 30,
    TF_JP2		= 31,
    TF_PFM		= 32,
    TF_PICT     = 33,
    TF_RAW		= 34,
    TF_WEBP     = 35,
    TF_JXR		= 36,
    TF_UTFGrid = 101,
    TF_GeoJSON = 102,
    TF_MB_Vector=103,
    TF_TopoJSON= 104
};

}

#endif // DATAMAPS_TILE_FORMAT

