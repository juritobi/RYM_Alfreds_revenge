#pragma once
#include <cpctelera.h>
#include <sprites/char.h>
#include <sprites/sword.h>
#include <sprites/knife.h>

#include <sprites/shooter.h>
#include <sprites/ghost.h>
#include <sprites/zombi.h>
#include <sprites/dasher.h>

#include <sprites/boss.h>

typedef struct spr_frame spr_frame_t;
typedef struct spr_set spr_set_t;
struct spr_frame{
    u8 time;
    u8* frame;
    spr_frame_t* next;
};
struct spr_set{
    spr_frame_t** array;
    u16 l;
};

//CHARACTER-----------------------------------------------------------------------------------------------------------------------------------------------------------
#define char_sprset_W 4
#define char_sprsheet_line (SPR_CHAR_0_W * SPR_CHAR_0_H * 4)//4 number of images in right direction
extern const spr_set_t c_spriteset;
extern const spr_frame_t c_s_0;
extern const spr_frame_t c_w_0;
extern const spr_frame_t c_w_1;
extern const spr_frame_t c_j_0;
extern const spr_frame_t c_h_0;
//SWORD---------------------------------------------------------------------------------------------------------------------------------------------------------------
#define sword_sprset_W 1
#define sword_sprsheet_line (SPR_SWORD_0_W * SPR_SWORD_0_H * 1)//4 number of images in right direction
extern const spr_set_t sw_spriteset;
extern const spr_frame_t sw_0;
//KNIFE---------------------------------------------------------------------------------------------------------------------------------------------------------------
#define knife_sprset_W 1
#define knife_sprsheet_line (SPR_KNIFE_0_W * SPR_KNIFE_0_H * 1)//4 number of images in right direction
extern const spr_set_t kn_spriteset;
extern const spr_frame_t kn_0;

//SHOOTER-------------------------------------------------------------------------------------------------------------------------------------------------------------
#define shooter_sprset_W 1
#define shooter_sprsheet_line (SPR_SHOOTER_0_W * SPR_SHOOTER_0_H * 2)//4 number of images in right direction
extern const spr_set_t s_spriteset;
extern const spr_frame_t s_0;
extern const spr_frame_t s_1;
//GHOST---------------------------------------------------------------------------------------------------------------------------------------------------------------
#define ghost_sprset_W 1
#define ghost_sprsheet_line (SPR_GHOST_0_W * SPR_GHOST_0_H * 2)//4 number of images in right direction
extern const spr_set_t g_spriteset;
extern const spr_frame_t g_0;
extern const spr_frame_t g_1;
//ZOMBI---------------------------------------------------------------------------------------------------------------------------------------------------------------
#define zombi_sprset_W 1
#define zombi_sprsheet_line (SPR_ZOMBI_0_W * SPR_ZOMBI_0_H * 2)//4 number of images in right direction
extern const spr_set_t z_spriteset;
extern const spr_frame_t z_0;
extern const spr_frame_t z_1;
//DASHER---------------------------------------------------------------------------------------------------------------------------------------------------------------
#define dasher_sprset_W 3
#define dasher_sprsheet_line (SPR_DASHER_00_W * SPR_DASHER_00_H * 5)//4 number of images in right direction
extern const spr_set_t d_spriteset;
extern const spr_frame_t d_w_0;
extern const spr_frame_t d_w_1;
extern const spr_frame_t d_d_0;
extern const spr_frame_t d_d_1;
extern const spr_frame_t d_c_0;


//BOSS----------------------------------------------------------------------------------------------------------------------------------------------------------------
#define boss_sprset_W 2
#define boss_sprsheet_line (SPR_BOSS_0_W * SPR_BOSS_0_H * 2)//4 number of images in right direction
extern const spr_set_t b_spriteset;
extern const spr_frame_t b_s_0;
extern const spr_frame_t b_h_0;





void sys_anim_init();
void sys_anim_update();