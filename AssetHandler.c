#include <raylib.h>

struct AssetHandler
{
    /* data */
    Image assets[1024];
};

void AddAsset(char path[]) {
    assetsLoadImage(path);
}