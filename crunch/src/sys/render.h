#pragma once
#include <cpctelera.h>
#include <man/man_ent.h>


//tile drawing
void sys_ren_draw_tilemap(u8* tilemap);
void sys_ren_draw_tile(u8 tile_index, u8 x, u8 y);

void sys_ren_setup();
void sys_ren_render();

//setup
void sys_ren_block_setup(ent_t* e);