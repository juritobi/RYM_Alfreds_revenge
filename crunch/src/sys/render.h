#pragma once
#include <cpctelera.h>
#include <man/man_ent.h>

typedef struct tile_to_render{
   u8* pos;
   void* sprite;
}tile;

//tile drawing


void sys_ren_draw_tilemap(u8* tilemap);
void sys_ren_set_tile(u8 tile_index, u8 x, u8 y);
void sys_ren_tile(u8 tile_index, u8 x, u8 y);

void sys_ren_setup();
void sys_ren_render();