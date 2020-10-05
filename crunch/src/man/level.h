#pragma once
#include <cpctelera.h>


typedef struct lvl lvl_t;
typedef struct lvl{
    u8* pack_end;
    u8* top;
    u8* right;
    u8* bot;
    u8* left;
};

u8* man_level_get_tilemap();

void man_level_init();
void man_level_load(u8* map);