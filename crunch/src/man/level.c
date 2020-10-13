#include "level.h"
#include <man/man_ent.h>
#include <sys/render.h>
#include <man/app.h>
#include <constants.h>

extern const lvl_t i_lvl0;
extern const lvl_t i_lvl1;
extern const lvl_t i_lvl2;
extern const lvl_t i_lvl3;
extern const lvl_t i_lvl4;
extern const lvl_t i_lvl5;

const lvl_t i_lvl0 = {
    lvl0_pack_end,      //this
    0,                  //top
    &i_lvl2,      //right
    &i_lvl5,                  //bot
    &i_lvl1,                  //left
    0,
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl1 = {
    lvl1_pack_end,      //this
    0,                  //top
    &i_lvl0,      //right
    &i_lvl0,                  //bot
    0,                  //left
    0,
    {
        {e_c_zombi, 4, 168},
        {e_c_zombi, 72, 168},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl2 = {
    lvl2_pack_end,      //this
    0,                  //top
    0,      //right
    &i_lvl0,                  //bot
    &i_lvl0,                  //left
    0,
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl3 = {
    lvl3_pack_end,      //this
    &i_lvl0,                  //top
    &i_lvl5,      //right
    0,                  //bot
    0,                  //left
    0,
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl4 = {
    lvl4_pack_end,      //this
    &i_lvl0,                  //top
    0,      //right
    0,                  //bot
    &i_lvl5,                  //left
    0,
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl5 = {
    lvl5_pack_end,      //this
    &i_lvl0,                  //top
    &i_lvl4,      //right
    0,                  //bot
    &i_lvl3,                  //left
    0,
    {
        {e_c_shoot, 12, 98},
        {e_c_shoot, 72, 64},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};

lvl_t* level;
u8 tilemap_start[tilemap_size];
#define tilemap_end  (tilemap_start + tilemap_size - 1)

void man_level_init(){
    level = &i_lvl0;
    man_level_load(16, 80);
}

void man_level_load(u8 px, u8 py){
    u8 it = 0;
    ent_class* class = &level->entities[it]; 

    cpct_zx7b_decrunch_s(tilemap_end, level->self);
    sys_ren_draw_tilemap(tilemap_start);
    
    man_ent_init();
    man_ent_create_class(e_c_char, px, py);

    while(class->type != e_c_undefined){
        level->enemies++;
        man_ent_create_class(class->type, class->x, class->y);
        it++;
        class = &level->entities[it];
    }

    cpct_waitVSYNC();
    cpct_waitHalts(2);
    cpct_waitVSYNC();
    cpct_setInterruptHandler(interrupt_1);
}

void man_level_update(){
    ent_t* player = man_ent_get_char();
    if(player->x == 0){
        player->x = 72;
        level = level->left;
        man_level_load(player->x, player->y);
    }
    else if(player->x == 76){
        player->x = 4;
        level = level->right;
        man_level_load(player->x, player->y);
    }
    else if(player->y == 24){
        player->y = 168;
        level = level->top;
        man_level_load(player->x, player->y);
    }
    else if(player->y == 176){
        player->y = 32;
        level = level->bot;
        man_level_load(player->x, player->y);
    }
}

void man_level_kill_enemy(){
    //level->enemies--;
}

u8* man_level_get_tilemap(){
    return tilemap_start;
}