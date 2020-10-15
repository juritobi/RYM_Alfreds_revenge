#include "anim.h"
#include <sprites/char.h>
#include <man/man_ent.h>

const anim_frame_t char_walking_right [] = {
    {anim_frame_time, {.spr = spr_char_0} },
    {anim_frame_time, {.spr = spr_char_1} },
    {0, {.next = char_walking_right} }
};
const anim_frame_t char_standing_right [] = {
    {anim_frame_time, {.spr = spr_char_0} },
    {0, {.next = char_standing_right} }
};
const anim_frame_t char_jumping_right [] = {
    {anim_frame_time, {.spr = spr_char_0} },
    {0, {.next = char_jumping_right} }
};
const anim_frame_t char_hitting_right [] = {
    {anim_frame_time, {.spr = spr_char_0} },
    {0, {.next = char_hitting_right} }
};

void sys_anim_one(ent_t* e){
    if( -- (e->anim_timer) == 0){
        ++e->anim;
        if(e->anim->time==0){
            e->anim = e->anim->value.next;
        }
        e->sprite = e->anim->value.spr;
        e->anim_timer = e->anim->time;
    }
}
void sys_anim_update(){
    man_ent_forall_type(sys_anim_one, e_t_anim);
}

