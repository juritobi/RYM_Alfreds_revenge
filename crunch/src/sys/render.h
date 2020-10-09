#pragma once
#include <cpctelera.h>
#include <man/man_ent.h>



void sys_ren_draw_tilemap(u8* tilemap);
void sys_ren_update();
void sys_ren_blend_first(ent_t* e);
void sys_ren_blend(ent_t* e);
void sys_ren_kill(ent_t* e);