#include "anim.h"
#include <man/man_ent.h>

const spr_frame_t c_s_0 = {
    4,
    spr_char_0,
    &c_s_0
};
const spr_frame_t c_w_0 = {
    4,
    spr_char_0,
    &c_w_1
};
const spr_frame_t c_w_1 = {
    4,
    spr_char_1,
    &c_w_0
};
const spr_frame_t c_j_0 = {
    4,
    spr_char_2,
    &c_j_0
};
const spr_frame_t c_h_0 = {
    4,
    spr_char_3,
    &c_h_0
};
const spr_frame_t* c_tset[char_sprset_W] = {
    &c_s_0,
    &c_w_0,
    &c_h_0,
    &c_h_0
};
const spr_set_t character_spriteset = {
    c_tset,
    char_sprsheet_line
};

void sys_anim_one(ent_t* e){
    u8 action = e->action & 0x0F;
    u8 prev_action = e->action >> 4;
    u8 timer = e->anim_timer;
    spr_frame_t* frame = e->frame;

    if(action != prev_action){
        frame = e->sprite_set->array[action];
        timer = frame->time;
    }

    timer --;
    if(!timer){
        frame = frame->next;
        timer = frame->time;
    }

    if(e->move_dir){
        e->sprite = frame->frame + e->sprite_set->l;
    }
    else{
        e->sprite = frame->frame;
    }
    
    e->action = action<<4;
    e->anim_timer = timer;
    e->frame = frame;
}
void sys_anim_update(){
    man_ent_forall_type(sys_anim_one, e_t_anim);
}
