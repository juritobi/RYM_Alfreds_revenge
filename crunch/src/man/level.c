#include "level.h"
#include <man/man_ent.h>
#include <sys/render.h>
#include <man/app.h>
#include <sys/UI.h>

u8 final_door_open;

void lt_room();
void rt_room();
void rb_room();
void final_room();
void normal_room();
void boss_room();


void redraw_tile(u8 x, u8 y, u8 tile){
    tilemap_start[y*tilemap_W + x] = tile;
    sys_ren_tile(tile, x*4, (y+3)*8);
}

void bl_room(){
    redraw_tile(10, 19, 18);
}

void br_room(){
    redraw_tile(10,  8, 6);
}

void tl_room(){
    redraw_tile(9, 8, 6);
}

void tr_room(){
    redraw_tile(9, 21, 18);
    redraw_tile(10, 21, 18);
}

void powerup_tbl_room(){
    redraw_tile(9, 3, 18);
}

void powerup_tbr_room(){
    redraw_tile(10, 18, 18);
}

void powerup_brl_room(){
    redraw_tile(10, 8, 18);
}

void powerup_trl_room(){
    redraw_tile(16, 19, 18);
}

const u8 crap = 0x0;
const lvl_t i_lvl0;
const lvl_t i_lvl0_2;
const lvl_t i_bot_left_1;
const lvl_t i_bot_left_2;
const lvl_t i_bot_left_3;
const lvl_t i_bot_left_4;
const lvl_t i_bot_left_5;
const lvl_t i_bot_left_6;
const lvl_t i_bot_left_extra;
const lvl_t i_top_left_1;
const lvl_t i_top_left_2;
const lvl_t i_top_left_3;
const lvl_t i_top_left_4;
const lvl_t i_top_left_5;
const lvl_t i_top_left_6;
const lvl_t i_top_left_7;
const lvl_t i_top_left_extra;
const lvl_t i_bot_right_1;
const lvl_t i_bot_right_2;
const lvl_t i_bot_right_3;
const lvl_t i_bot_right_4;
const lvl_t i_bot_right_5;
const lvl_t i_bot_right_6;
const lvl_t i_bot_right_extra;
const lvl_t i_top_right_1;
const lvl_t i_top_right_2;
const lvl_t i_top_right_3;
const lvl_t i_top_right_4;
const lvl_t i_top_right_5;
const lvl_t i_top_right_extra;

const lvl_t i_top_bot_right_power_up;
const lvl_t i_top_bot_left_power_up;
const lvl_t i_top_right_left_power_up;
const lvl_t i_bot_right_left_power_up;

const lvl_t i_lvl0 = {//center room
    0,                  //id
    lvl0_pack_end,      //this
    0,                  //top
    &i_top_right_1,     //right
    &i_lvl0_2,          //bot
    &i_top_left_1,      //left
    final_room,
    0,
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl0_2 = {
    1,                          //id
    lvl0_2_pack_end,            //this
    &i_lvl0,                    //top
    &i_bot_right_1,             //right
    0,                          //bot
    &i_bot_left_1,              //left
    normal_room,
    0,
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_bot_left_1 = {
    2,                          //id
    bot_left_1_pack_end,        //this
    0,                          //top
    &i_lvl0_2,                  //right
    &i_bot_left_2,                          //bot
    0,                          //left
    normal_room,
    0,
    {
        {e_c_zombi, 24, 176},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_bot_left_2 = {
    3,                          //id
    bot_left_2_pack_end,        //this
    &i_bot_left_1,              //top
    0,                          //right
    &i_bot_left_extra,          //bot
    &i_bot_left_3,              //left
    normal_room,
    0,
    {
        {e_c_zombi, 52, 88},
        {e_c_shoot, 68, 64},
        {e_c_zombi, 12, 160},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_bot_left_3 = {
    4,                          //id
    bot_left_3_pack_end,        //this
    &i_top_bot_left_power_up,                           //top
    &i_bot_left_2,              //right
    &i_bot_left_4,              //bot
    0,                          //left
    normal_room,
    0,
    {
        {e_c_zombi, 12, 176},
        {e_c_zombi, 32, 80},
        {e_c_zombi, 40, 136},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_bot_left_extra = {
    5,                          //id
    bot_left_extra_pack_end,    //this
    &i_bot_left_2,              //top
    &i_bot_right_left_power_up,                          //right
    0,                          //bot
    &i_bot_left_4,              //left
    normal_room,
    0,
    {
        {e_c_zombi, 52, 176},
        {e_c_zombi, 60, 56},
        {e_c_shoot, 32, 176},
        {e_c_ghost, 8, 24},
        {0, 0, 0}
    }
};
const lvl_t i_bot_left_4 = {
    6,                          //id
    bot_left_4_pack_end,        //this
    &i_bot_left_3,              //top
    &i_bot_left_extra,          //right
    0,                          //bot
    &i_bot_left_5,              //left
    normal_room,
    0,
    {
        {e_c_zombi, 16, 160},
        {e_c_zombi, 52, 160},
        {e_c_ghost, 32, 160},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_bot_left_5 = {
    7,                          //id
    bot_left_5_pack_end,        //this
    0,                          //top
    &i_bot_left_4,              //right
    &i_bot_left_6,               //bot
    0,                          //left
    normal_room,
    0,
    {
        {e_c_ghost, 12, 48},
        {e_c_ghost, 60, 176},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_bot_left_6 = {
    8,                          //id
    bot_left_6_pack_end,        //this
    &i_bot_left_5,              //top
    0,                          //right
    &i_lvl0,                    //bot
    0,                          //left
    bl_room,
    0,
    {
        {e_c_ghost, 68, 40},
        {e_c_shoot, 68, 64},
        {e_c_shoot, 68, 96},
        {e_c_shoot, 68, 128},
        {0, 0, 0}
    }
};

const lvl_t i_bot_right_1 = {
    9,                          //id
    bot_right_1_pack_end,       //this
    0,                          //top
    0,                          //right
    &i_bot_right_2,             //bot
    &i_lvl0_2,                  //left
    normal_room,
    0,
    {
        {e_c_ghost, 56, 88},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_bot_right_2 = {
    10,                          //id
    bot_right_2_pack_end,        //this
    &i_bot_right_1,              //top
    &i_bot_right_3,              //right
    &i_bot_right_extra,          //bot
    0,                           //left
    normal_room,
    0,
    {
        {e_c_ghost, 12, 56},
        {e_c_ghost, 8,  168},
        {e_c_zombi, 48, 176},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_bot_right_3 = {
    11,                          //id
    bot_right_3_pack_end,        //this
    &i_bot_right_4,              //top
    &i_bot_right_2,              //right
    0,                           //bot
    0,                          //left
    normal_room,
    0,
    {
        {e_c_shoot, 72,  80},
        {e_c_sonic, 36, 176},
        {e_c_sonic, 60, 176},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_bot_right_extra = {
    12,                         //id
    bot_right_extra_pack_end,   //this
    &i_bot_right_2,             //top
    0,                          //right
    0,                          //bot
    &i_bot_right_left_power_up,                          //left
    normal_room,
    0,
    {
        {e_c_ghost, 52, 176},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_bot_right_4 = {
    13,                          //id
    bot_right_4_pack_end,        //this
    0,                           //top
    &i_bot_right_5,              //right
    &i_bot_right_3,              //bot
    0,                           //left
    normal_room,
    0,
    {
        {e_c_ghost, 40,  72},
        {e_c_ghost, 35, 120},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_bot_right_5 = {
    14,                          //id
    bot_right_5_pack_end,        //this
    &i_top_bot_right_power_up,                           //top
    &i_bot_right_6,              //right
    0,                           //bot
    &i_bot_right_4,              //left
    normal_room,
    0,
    {
        {e_c_shoot, 60, 104},
        {e_c_shoot, 60, 120},
        {e_c_sonic, 20, 64},
        {e_c_sonic, 48, 64},
        {0, 0, 0}
    }
};
const lvl_t i_bot_right_6 = {
    15,                          //id
    bot_right_6_pack_end,       //this
    &i_lvl0,                    //top
    0,                          //right
    0,                          //bot
    &i_bot_right_5,                          //left
    br_room,
    0,
    {
        {e_c_ghost, 52, 40},
        {e_c_shoot, 68, 128},
        {e_c_shoot, 68, 168},
        {0, 0, 0},
        {0, 0, 0}
    }
};

const lvl_t i_top_left_1 = {
    16,                          //id
    top_left_1_pack_end,        //this
    &i_top_left_2,              //top
    &i_lvl0,                    //right
    0,                          //bot
    0,                          //left
    normal_room,
    0,
    {
        {e_c_zombi, 16, 176},
        {e_c_zombi, 64, 176},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_top_left_2 = {
    17,                          //id
    top_left_2_pack_end,        //this
    0,                          //top
    0,                          //right
    &i_top_left_1,              //bot
    &i_top_left_3,              //left
    normal_room,
    0,
    {
        {e_c_zombi, 24, 176},
        {e_c_zombi, 12, 80},
        {e_c_zombi, 20, 48},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_top_left_3 = {
    18,                          //id
    top_left_3_pack_end,        //this
    &i_top_left_extra,          //top
    &i_top_left_2,              //right
    &i_top_left_4,              //bot
    0,                          //left
    normal_room,
    0,
    {
        {e_c_ghost, 24, 56},
        {e_c_zombi, 24, 176},
        {e_c_zombi, 64, 176},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_top_left_extra = {
    19,                          //id
    top_left_extra_pack_end,     //this
    0,                           //top
    &i_top_right_left_power_up,  //right
    &i_top_left_3,               //bot
    0,                           //left
    normal_room,
    0,
    {
        {e_c_zombi, 32, 176},
        {e_c_zombi, 48, 176},
        {e_c_zombi, 64, 176},
        {e_c_ghost, 28, 64},
        {0, 0, 0}
    }
};
const lvl_t i_top_left_4 = {
    20,                          //id
    top_left_4_pack_end,        //this
    &i_top_left_3,              //top
    0,                          //right
    &i_top_bot_left_power_up,                          //bot
    &i_top_left_5,              //left
    normal_room,
    0,
    {
        {e_c_zombi, 12, 176},
        {e_c_zombi, 40, 176},
        {e_c_zombi, 40, 112},
        {e_c_ghost, 64, 40},
        {0, 0, 0}
    }
};
const lvl_t i_top_left_5 = {
    21,                          //id
    top_left_5_pack_end,        //this
    0,                          //top
    &i_top_left_4,              //right
    &i_top_left_6,               //bot
    0,                          //left
    normal_room,
    0,
    {
        {e_c_zombi, 12, 104},
        {e_c_zombi, 12, 176},
        {e_c_zombi, 40, 72},
        {e_c_zombi, 52, 104},
        {0, 0, 0}
    }
};
const lvl_t i_top_left_6 = {
    22,                          //id
    top_left_6_pack_end,        //this
    &i_top_left_5,              //top
    &i_top_bot_left_power_up,                          //right
    0,                          //bot
    &i_top_left_7,              //left
    normal_room,
    0,
    {
        {e_c_zombi, 4,  128},
        {e_c_zombi, 4,  96},
        {e_c_zombi, 68, 96},
        {e_c_zombi, 68, 128},
        {0, 0, 0}
    }
};
const lvl_t i_top_left_7 = {
    23,                          //id
    top_left_7_pack_end,        //this
    &i_lvl0,                    //top
    &i_top_left_6,              //right
    0,                          //bot
    0,                          //left
    tl_room,
    0,
    {
        {e_c_ghost,  4, 40},
        {e_c_zombi,  4, 168},
        {e_c_zombi, 64, 168},
        {e_c_shoot, 68, 104},
        {0, 0, 0}
    }
};

const lvl_t i_top_right_1 = {
    24,                         //id
    top_right_1_pack_end,       //this
    0,                          //top
    &i_top_right_2,             //right
    0,                          //bot
    &i_lvl0,                    //left
    normal_room,
    0,
    {
        {e_c_zombi, 60, 112},
        {e_c_sonic, 12, 176},
        {e_c_sonic, 60, 176},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_top_right_2 = {
    25,                          //id
    top_right_2_pack_end,        //this
    &i_top_right_extra,          //top
    &i_top_right_3,              //right
    0,                           //bot
    &i_top_right_1,              //left
    normal_room,
    0,
    {
        {e_c_sonic, 40, 176},
        {e_c_shoot, 72, 104},
        {e_c_shoot, 72, 136},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_top_right_3 = {
    26,                          //id
    top_right_3_pack_end,        //this
    &i_top_right_4,              //top
    0,                           //right
    &i_top_bot_right_power_up,   //bot
    &i_top_right_2,              //left
    normal_room,
    0,
    {
        {e_c_sonic, 12, 176},
        {e_c_ghost, 36,  64},
        {e_c_sonic, 60, 176},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_top_right_extra = {
    27,                         //id
    top_right_extra_pack_end,   //this
    &i_top_right_left_power_up,                          //top
    &i_top_right_4,             //right
    &i_top_right_2,             //bot
    0,                          //left
    normal_room,
    0,
    {
        {e_c_shoot, 72, 176},
        {e_c_sonic, 72, 152},
        {e_c_sonic, 12, 88},
        {e_c_sonic, 12, 120},
        {e_c_sonic, 64, 56}
    }
};
const lvl_t i_top_right_4 = {
    28,                          //id
    top_right_4_pack_end,        //this
    0,                           //top
    &i_top_right_5,              //right
    &i_top_right_3,              //bot
    &i_top_right_extra,          //left
    normal_room,
    0,
    {
        {e_c_sonic, 48, 144},
        {e_c_sonic, 8,  80},
        {e_c_sonic, 72, 48},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_top_right_5 = {
    29,                          //id
    top_right_5_pack_end,        //this
    0,                           //top
    0,                           //right
    &i_lvl0,                     //bot
    &i_top_right_4,              //left
    tr_room,
    0,
    {
        {e_c_shoot, 72, 112},
        {e_c_shoot, 72, 64},
        {e_c_sonic, 56, 64},
        {e_c_sonic, 56, 112},
        {0, 0, 0}
    }
};

const lvl_t i_top_bot_right_power_up = {
    30,
    top_bot_right_power_up_pack_end,
    &i_top_right_3,
    0,
    &i_bot_right_5,
    0,
    powerup_tbr_room,
    0,
    {
        {e_c_sonic, 4, 64},
        {e_c_ghost, 40, 88},
        {e_c_powerUp, 40, 176, 2},
        {0, 0, 0},
        {0, 0, 0}
    }
};

const lvl_t i_top_bot_left_power_up = {
    31,
    top_bot_left_power_up_pack_end,
    &i_top_left_4,
    0,
    &i_bot_left_3,
    &i_top_left_6,
    powerup_tbl_room,
    0,
    {
        {e_c_shoot, 40, 128},
        {e_c_shoot, 40, 176},
        {e_c_sonic, 52, 176},
        {e_c_sonic, 68, 176},
        {e_c_powerUp, 36, 32, 1}
    }
};

const lvl_t i_top_right_left_power_up = {
    32,
    top_right_left_power_up_pack_end,
    0,
    0,
    &i_top_right_extra,
    &i_top_left_extra,
    powerup_trl_room,
    0,
    {
        {e_c_sonic, 24, 88},
        {e_c_sonic, 24, 176},
        {e_c_sonic, 48, 56},
        {e_c_sonic, 48, 120},
        {e_c_powerUp, 72, 176, 4}
    }
};

const lvl_t i_bot_right_left_power_up  = {
    33,
    bot_right_left_power_up_pack_end,
    0,
    &i_bot_right_extra,
    0,
    &i_bot_left_extra,
    powerup_brl_room,
    0,
    {
        {e_c_zombi, 8,  48},
        {e_c_shoot, 68, 32},
        {e_c_powerUp, 40, 32, 3},
        {0, 0, 0},
        {0, 0, 0}
    }
};

const lvl_t i_boss1 = {
    34,                  //id
    boss1_pack_end,      //this
    0,                  //top
    0,      //right
    0,                  //bot
    0,                  //left
    boss_room,
    0,
    {
        {e_c_boss1_1, 32, 72, 0},
        {e_c_boss_tools, 0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};

u8 cleared_rooms[35];
lvl_t level;
u8 tilemap_start[tilemap_size];
#define tilemap_end  (tilemap_start + tilemap_size - 1)





void final_room(){
    if(cleared_rooms[level.id] == 0x0F){
        tilemap_start[2*tilemap_W + 6] = 27;
        tilemap_start[2*tilemap_W + 13] = 27;
        tilemap_start[15*tilemap_W + 6] = 27;
        tilemap_start[15*tilemap_W + 13] = 27;

        final_door_open = 1;
    }
    else{
        if(cleared_rooms[level.id] & 1){
            tilemap_start[2*tilemap_W + 6] = 27;
            sys_ren_tile(27, 6*4, (2+3)*8);
        }
        if(cleared_rooms[level.id] & 2){
            tilemap_start[2*tilemap_W + 13] = 27;
            sys_ren_tile(27, 13*4, (2+3)*8);
        }
        if(cleared_rooms[level.id] & 4){
            tilemap_start[15*tilemap_W + 13] = 27;
            sys_ren_tile(27, 13*4, (15+3)*8);
        }
        if(cleared_rooms[level.id] & 8){
            tilemap_start[15*tilemap_W + 6] = 27;
            sys_ren_tile(27, 6*4, (15+3)*8);
        }
    }
}

void boss_room(){
}
void normal_room(){     
}


void man_level_init(){
    u8* lvl_pointer = &crap;
    final_door_open = 0;
    ++lvl_pointer;
    cpct_memcpy(&level, lvl_pointer, sizeof(lvl_t));
    cpct_memset(cleared_rooms, 0, sizeof(cleared_rooms));
    man_level_load();
}

void man_level_load(){
    u8 it = 0;
    ent_class* class = &level.entities[it]; 

    sys_ren_init();
    cpct_zx7b_decrunch_s(tilemap_end, level.self);
    sys_ren_draw_tilemap(tilemap_start);
    

    (player+1)->death(player+1);
    (player+2)->death(player+2);
    man_ent_reset();
    if(level.id){
        if(!cleared_rooms[level.id]){
            while(class->type != e_c_undefined){
                if(class->type != e_c_powerUp){
                    level.enemies++;
                }
                man_ent_create_class(class->type, class->x, class->y, class->mp);
                it++;
                class = &level.entities[it];
            }
        }
        else{
            level.cleared_func();
        }
    }
    else{
        level.cleared_func();
    }

    cpct_waitVSYNC();
    cpct_waitHalts(2);
    cpct_waitVSYNC();
    cpct_setInterruptHandler(interrupt_1);
}

void man_level_update(){
    if(player->x == 0){
        player->x = 72;
        cpct_memcpy(&level, level.left, sizeof(lvl_t));
        man_level_load();
    }
    else if(player->x == 76){
        player->x = 4;
        cpct_memcpy(&level, level.right, sizeof(lvl_t));
        man_level_load();
    }
    else if(player->y == 24){
        player->y = 168;
        cpct_memcpy(&level, level.top, sizeof(lvl_t));
        man_level_load();
    }
    else if(player->y == 176){
        player->y = 32;
        cpct_memcpy(&level, level.bot, sizeof(lvl_t));
        man_level_load();
    }
    else if(final_door_open){
        if(level.self == lvl0_pack_end){
            if( player->x+player->w > 36  &&  player->x < 44){
                if(player->y > 140) {
                    if(cpct_isKeyPressed(Key_W)){
                        cpct_memcpy(&level, &i_boss1, sizeof(lvl_t));
                        man_level_load();
                    }
                }
            }
        }
    }
}

void man_level_add_mp_end_lvl(){
    if(player->mp == player->prev_vy -1){
        player->mp++;
    }
    else if(player->mp < player->prev_vy -1){
        player->mp++;
        player->mp++;
    }
}

void man_level_kill_enemy(){
    level.enemies--;
    if(level.enemies == 0){
        score += 25;
        cleared_rooms[level.id]=1;
        level.cleared_func();
        man_level_add_mp_end_lvl();
    }
}
u8 man_level_get_door(){
    return final_door_open;
}
