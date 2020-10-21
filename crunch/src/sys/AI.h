#pragma once
#include <cpctelera.h>
#include <man/man_ent.h>

void sys_AI_init();
void sys_AI_update();
void sys_AI_shoot(ent_t* e);
void sys_AI_zombi(ent_t* e);
void sys_AI_ghost(ent_t* e);
void sys_AI_sonic(ent_t* e);
