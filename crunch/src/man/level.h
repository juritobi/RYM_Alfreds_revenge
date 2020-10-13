#pragma once
#include <cpctelera.h>
#include <man/man_ent.h>

typedef struct lvl lvl_t;
typedef struct lvl{
    u8* self;
    lvl_t* top;
    lvl_t* right;
    lvl_t* bot;
    lvl_t* left;
    u8 enemies;//always0
    ent_class entities [5];
};

u8* man_level_get_tilemap();

void man_level_init();
void man_level_load(lvl_t* map, u8 x, u8 y);
void man_level_kill_enemy();