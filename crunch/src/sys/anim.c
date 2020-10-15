#include "anim.h"
#include <sprites/char.h>
#include <man/man_ent.h>

const anim_frame_t char_walk_right [] = {
    {4, {.spr = spr_char_0} },
    {4, {.spr = spr_char_1} },
    {0, {.next = char_walk_right} }
};

void sys_anim_one(ent_t* e){
    if( -- (e->step) == 0){
        ++e->anim;
        if(e->anim->time==0){
            e->anim = e->anim->value.next;
        }
        e->sprite = e->anim->value.spr;
        e->step = e->anim->time;
    }
}
void sys_anim_update(){
    man_ent_forall_type(sys_anim_one, e_t_anim);
}

