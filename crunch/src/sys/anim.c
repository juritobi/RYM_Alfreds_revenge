#include "anim.h"
#include <man/man_ent.h>

spr_frame_t* c_tset[char_sprset_W];
spr_frame_t* s_tset[shooter_sprset_W];
spr_frame_t* b_tset[boss_sprset_W];

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
const spr_set_t c_spriteset = {
    c_tset,
    char_sprsheet_line
};



const spr_frame_t s_w_0 = {
    20,
    spr_shooter_0,
    &s_w_1
};
const spr_frame_t s_w_1 = {
    4,
    spr_shooter_1,
    &s_w_0
};
const spr_set_t s_spriteset = {
    s_tset,
    shooter_sprsheet_line
};

const spr_frame_t b_s_0 = {
    0xFF,
    spr_boss_0,
    &b_s_0
};
const spr_frame_t b_h_0 = {
    0xFF,
    spr_boss_1,
    &b_s_0
};
const spr_set_t b_spriteset = {
    b_tset,
    boss_sprsheet_line
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
void sys_anim_init(){
    c_tset[0] = &c_s_0;
    c_tset[1] = &c_w_0;
    c_tset[2] = &c_j_0;
    c_tset[3] = &c_h_0;//this is supose to be constant but the compiles is poopoo and doesn't let me do that

    s_tset[0] = &s_w_0;

    b_tset[0] = &b_s_0;
    b_tset[1] = &b_h_0;
}
