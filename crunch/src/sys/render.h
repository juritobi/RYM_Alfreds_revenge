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
void sys_ren_blend_setup(ent_t* e);
void sys_ren_blend_setup_first(ent_t* e);

//rendering
void sys_ren_no_draw(ent_t* e);

void sys_ren_block_erasing(ent_t* e);
void sys_ren_block(ent_t* e);

void sys_ren_blend_one(ent_t* e);
void sys_ren_blend(ent_t* e);