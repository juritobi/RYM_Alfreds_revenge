#include "physics.h"
#include <man/man_ent.h>

#define rate_of_fire 100
u8 shoot_timer;

void sys_AI_shoot(ent_t* e){
    if(shoot_timer > rate_of_fire){
        shoot_timer = 0;
        man_ent_resurrect(e, 1);
    }
}
void sys_AI_zombi(ent_t* e){
    e->vy = 4;
    if(e->vx == 0){
        if(e->prev_vx == -1){
            e->vx = 1;
            e->prev_vx = 1;
        }
        else {
            e->vx = -1;
            e->prev_vx = -1;
        }
    }
}

void sys_AI_one(ent_t* e){
    e->act(e);
}

void sys_AI_init(){
    shoot_timer=0;
}
void sys_AI_update(){
    shoot_timer++;
    man_ent_forall_type(sys_AI_one, e_t_AI);
}