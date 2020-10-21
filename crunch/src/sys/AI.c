#include "AI.h"
#include <man/man_ent.h>

#define rate_of_fire 100
#define move_rate 4


void sys_AI_shoot(ent_t* e){
    e->Ai_counter--;
    if(e->Ai_counter == 0){
        e->Ai_counter = rate_of_fire;
        man_ent_resurrect(e, 1);
    }
}
void sys_AI_zombi(ent_t* e){
    
    if(e->Ai_counter == 0 && e->vx == 0){
        if(e->prev_vx == -1)
            e->prev_vx = 1;
        else 
            e->prev_vx = -1;
    }
    e->vy = 4;
    e->vx = 0;
    e->Ai_counter++;
    if(e->Ai_counter == move_rate){
        e->Ai_counter = 0;
        e->vx = e->prev_vx;
    }
}

void sys_AI_ghost(ent_t* e){
    
    if(e->x < man_ent_get_char()->x){
        e->prev_vx = 1;
    }
    else if (e->x > man_ent_get_char()->x){
        e->prev_vx = -1;
    }
    else{
        e->prev_vx = 0;
    }

    if(e->y < man_ent_get_char()->y){
        e->prev_vy = 4;
    }
    else if (e->y > man_ent_get_char()->y){
        e->prev_vy = -4;
    }
    else{
        e->prev_vy = 0;
    }
    e->vy = 0;
    e->vx = 0;
    e->Ai_counter++;
    if(e->Ai_counter == move_rate){
        e->Ai_counter = 0;
        e->vx = e->prev_vx;
        e->vy = e->prev_vy;
    }

}

void sys_AI_sonic(ent_t* e){
    if(e->Ai_counter == 0 && e->vx == 0){
        if(e->prev_vx == -1)
            e->prev_vx = 1;
        else 
            e->prev_vx = -1;
    }
    e->vy = 4;
    e->vx = 0;
    e->Ai_counter++;
    if(e->Ai_counter%move_rate == 0 || e->Ai_counter > 28){
        e->vx = e->prev_vx;

        if(e->Ai_counter == 20 || e->Ai_counter == 24){
            e->vx = 0;
        }

        else if(e->Ai_counter > 28 && e->Ai_counter < 36){
            e->action |= 1;
        }

        else if (e->Ai_counter == 36){
            e->Ai_counter = 0;
        }

    }
}
void sys_AI_one(ent_t* e){
    e->act(e);
}

void sys_AI_init(){

}
void sys_AI_update(){
    man_ent_forall_type(sys_AI_one, e_t_AI);
}