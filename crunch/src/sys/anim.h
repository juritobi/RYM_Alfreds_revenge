#pragma once
#include <cpctelera.h>
#include <sprites/char.h>


#define anim_frame_time 4

typedef struct spr_tile spr_tile_t;
struct spr_tile{
    u8 length;
    u8* first_frame;
};

#define char_sprset_W 4
#define char_sprite_size (SPR_CHAR_0_W * SPR_CHAR_0_H)
#define char_sprsheet_line (char_sprite_size*4)//4 number of images in right direction -1
extern const spr_tile_t character_spriteset [char_sprset_W];

void sys_anim_init();
void sys_anim_update();