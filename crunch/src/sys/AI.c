#include "physics.h"
#include <man/man_ent.h>

#define rate_of_fire 100
#define move_rate 4
u8 shoot_timer;
u8 move_counter;
void sys_AI_shoot(ent_t* e){
    shoot_timer--;
    if(shoot_timer == 0){
        shoot_timer = rate_of_fire;
        man_ent_resurrect(e, 1);
    }
}
void sys_AI_zombi(ent_t* e){
    
    if(move_counter == 0 && e->vx == 0){
        if(e->prev_vx == -1)
            e->prev_vx = 1;
        else 
            e->prev_vx = -1;
    }
    e->vy = 4;
    e->vx = 0;
    move_counter++;
    if(move_counter == move_rate){
        move_counter = 0;
        e->vx = e->prev_vx;
    }
}

void sys_AI_boss(ent_t* e){

}

void sys_AI_one(ent_t* e){
    e->act(e);
}

void sys_AI_init(){
    shoot_timer=rate_of_fire;
    move_counter = 0;
}
void sys_AI_update(){
    man_ent_forall_type(sys_AI_one, e_t_AI);
}