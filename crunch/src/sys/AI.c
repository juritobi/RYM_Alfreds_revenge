#include "physics.h"
#include <man/man_ent.h>


//character mas always be the first entity in the entity array
void sys_AI_follow(ent_t* e){
    e->vy = 0;
}

void sys_AI_one(ent_t* e){
    e->act(e);
}

void sys_AI_update(){
    man_ent_forall_type(sys_AI_one, e_t_AI);
}