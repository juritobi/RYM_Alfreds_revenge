#pragma once
#include <cpctelera.h>
#include <man/man_ent.h>

typedef void (*Ptrf_v_v)(void);
typedef struct lvl lvl_t;
typedef struct lvl{
    u8 id;
    u8* self;
    lvl_t* top;
    lvl_t* right;
    lvl_t* bot;
    lvl_t* left;
    Ptrf_v_v cleared_func;
    u8 enemies;//always0
    ent_class entities [5];
};

u8* man_level_get_tilemap();

void man_level_init();
void man_level_update();
void man_level_load(u8 px, u8 py);
void man_level_kill_enemy();
void sys_ren_init();