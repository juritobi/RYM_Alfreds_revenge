#pragma once
#include <cpctelera.h>
#include <man/man_ent.h>
#include <man/level.h>

typedef struct attack attack_t;
typedef struct attack{
    u8 total_time;
    Ptrf_v_v funct;
};

void sys_AI_init();
void sys_AI_update();
void sys_AI_shoot(ent_t* e);
void sys_AI_zombi(ent_t* e);
void sys_AI_boss(ent_t* e);

void att_move();
void att_hor();
