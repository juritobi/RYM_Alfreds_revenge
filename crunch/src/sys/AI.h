#pragma once
#include <cpctelera.h>
#include <man/man_ent.h>

void sys_AI_init();
void sys_AI_update();
void sys_AI_shoot(ent_t* e);
void sys_AI_zombi(ent_t* e);
void sys_AI_boss(ent_t* e);

u8 att_move();
u8 att_hor();
