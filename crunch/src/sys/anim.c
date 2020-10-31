#include "anim.h"
#include <man/man_ent.h>
#include <sprites/blue.h>

spr_frame_t const * c_tset[char_sprset_W];
spr_frame_t const * sw_tset[sword_sprset_W];
spr_frame_t const * kn_tset[knife_sprset_W];

spr_frame_t const * s_tset[shooter_sprset_W];
spr_frame_t const * g_tset[ghost_sprset_W];
spr_frame_t const * z_tset[zombi_sprset_W];
spr_frame_t const * d_tset[dasher_sprset_W];
spr_frame_t const * b_tset[boss_sprset_W];

//******************************************************************
//------------------------------------------------------------------
//CHARACTER/////////////////////////////////////////////////////////
//------------------------------------------------------------------
//******************************************************************

//------------------------------------------------------------------
//CHARACTER/////////////////////////////////////////////////////////
//------------------------------------------------------------------
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
//------------------------------------------------------------------
//SWORD/////////////////////////////////////////////////////////////
//------------------------------------------------------------------
const spr_frame_t sw_0 = {
    0xFF,
    spr_sword_0,
    &sw_0
};
const spr_set_t sw_spriteset = {
    sw_tset,
    sword_sprsheet_line
};
//------------------------------------------------------------------
//KNIFE/////////////////////////////////////////////////////////////
//------------------------------------------------------------------
const spr_frame_t kn_0 = {
    0xFF,
    spr_knife_0,
    &kn_0
};
const spr_set_t kn_spriteset = {
    kn_tset,
    knife_sprsheet_line
};

//******************************************************************
//------------------------------------------------------------------
//ENEMIES///////////////////////////////////////////////////////////
//------------------------------------------------------------------
//******************************************************************

//------------------------------------------------------------------
//SHOOTER///////////////////////////////////////////////////////////
//------------------------------------------------------------------
const spr_frame_t s_0 = {
    20,
    spr_shooter_0,
    &s_1
};
const spr_frame_t s_1 = {
    4,
    spr_shooter_1,
    &s_0
};
const spr_set_t s_spriteset = {
    s_tset,
    shooter_sprsheet_line
};
//------------------------------------------------------------------
//GHOST/////////////////////////////////////////////////////////////
//------------------------------------------------------------------
const spr_frame_t g_0 = {
    5,
    spr_ghost_0,
    &g_1
};
const spr_frame_t g_1 = {
    5,
    spr_ghost_1,
    &g_0
};
const spr_set_t g_spriteset = {
    g_tset,
    ghost_sprsheet_line
};
//------------------------------------------------------------------
//ZOMBI/////////////////////////////////////////////////////////////
//------------------------------------------------------------------
const spr_frame_t z_0 = {
    5,
    spr_zombi_0,
    &z_1
};
const spr_frame_t z_1 = {
    5,
    spr_zombi_1,
    &z_0
};
const spr_set_t z_spriteset = {
    z_tset,
    zombi_sprsheet_line
};
//------------------------------------------------------------------
//DASHER/////////////////////////////////////////////////////////////
//------------------------------------------------------------------
const spr_frame_t d_w_0 = {
    5,
    spr_dasher_00,
    &d_w_1
};
const spr_frame_t d_w_1 = {
    5,
    spr_dasher_01,
    &d_w_0
};
const spr_frame_t d_d_0 = {
    5,
    spr_dasher_02,
    &d_d_1
};
const spr_frame_t d_d_1 = {
    5,
    spr_dasher_03,
    &d_d_0
};
const spr_frame_t d_c_0 = {
    5,
    spr_dasher_04,
    &d_c_0
};
const spr_set_t d_spriteset = {
    d_tset,
    dasher_sprsheet_line
};


//******************************************************************
//------------------------------------------------------------------
//BOSS//////////////////////////////////////////////////////////////
//------------------------------------------------------------------
//******************************************************************
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


//************************************************************************************************************************************
//------------------------------------------------------------------------------------------------------------------------------------
//CODE################################################################################################################################
//------------------------------------------------------------------------------------------------------------------------------------
//************************************************************************************************************************************
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

    if(e->invulnerable&0x80){
        e->sprite =spr_blue;
    }
}
void sys_anim_update(){
    man_ent_forall_type(sys_anim_one, e_t_anim);
}
void sys_anim_init(){
    c_tset[0] = &c_s_0;
    c_tset[1] = &c_w_0;
    c_tset[2] = &c_j_0;
    c_tset[3] = &c_h_0;//this is supose to be constant but the compiles is poopoo and doesn't let me do that

    sw_tset[0] = &sw_0;
    kn_tset[0] = &kn_0;

    s_tset[0] = &s_0;
    g_tset[0] = &g_0;
    z_tset[0] = &z_0;
    d_tset[0] = &d_w_0;
    d_tset[1] = &d_d_0;
    d_tset[2] = &d_c_0;

    b_tset[0] = &b_s_0;
    b_tset[1] = &b_h_0;

}
