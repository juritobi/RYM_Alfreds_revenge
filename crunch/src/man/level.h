#pragma once
#include <cpctelera.h>


typedef struct lvl lvl_t;
typedef struct lvl{
    u8* self;
    lvl_t* top;
    lvl_t* right;
    lvl_t* bot;
    lvl_t* left;
    
};

u8* man_level_get_tilemap();

void man_level_init();
void man_level_load(u8* map);