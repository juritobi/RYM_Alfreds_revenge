#include "physics.h"
#include <man/man_ent.h>

#define rate_of_fire 100
u8 shoot_timer;

//character must always be the first entity in the entity array
void sys_AI_follow(ent_t* e){
    e->vy = 0;
}
void sys_AI_shoot(ent_t* e){
    if(shoot_timer > rate_of_fire){
        shoot_timer = 0;
        man_ent_resurrect(e, 1);
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