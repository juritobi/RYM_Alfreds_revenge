#pragma once
#include <cpctelera.h>
#include <sprites/char.h>
#include <sprites/shooter.h>


#define anim_frame_time 4

typedef struct spr_frame spr_frame_t;
typedef struct spr_set spr_set_t;
struct spr_frame{
    u8 time;
    u8* frame;
    spr_frame_t* next;
};
struct spr_set{
    spr_frame_t* array;
    u8 l;
};


#define char_sprset_W 4
#define char_sprite_size (SPR_CHAR_0_W * SPR_CHAR_0_H)
#define char_sprsheet_line (char_sprite_size*4)//4 number of images in right direction -1
extern const spr_frame_t* c_tset [char_sprset_W];
extern const spr_set_t c_spriteset;
extern const spr_frame_t c_s_0;
extern const spr_frame_t c_w_0;
extern const spr_frame_t c_w_1;
extern const spr_frame_t c_j_0;
extern const spr_frame_t c_h_0;


void sys_anim_init();
void sys_anim_update();