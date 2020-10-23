#include "level.h"
#include <man/man_ent.h>
#include <sys/render.h>
#include <man/app.h>
#include <constants.h>

u8 final_door_open;

extern const lvl_t i_lvl0;
extern const lvl_t i_lvl1;
extern const lvl_t i_lvl2;
extern const lvl_t i_lvl3;
extern const lvl_t i_lvl4;
extern const lvl_t i_lvl5;

void lt_room();
void rt_room();
void lb_room();
void rb_room();
void final_room();
void normal_room();
void boss_room();

const lvl_t i_lvl0 = {//center room
    0,                  //id
    lvl0_pack_end,      //this
    0,                  //top
    &i_lvl2,      //right
    &i_lvl5,                  //bot
    &i_lvl1,                  //left
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
const lvl_t i_lvl1 = {//top left
    1,                  //id
    lvl1_pack_end,      //this
    0,                  //top
    &i_lvl0,      //right
    &i_lvl0,                  //bot
    0,                  //left
    lt_room,
    0,
    {
        {e_c_zombi, 4, 168, 0},
        {e_c_zombi, 72, 168, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl2 = {//right top
    2,                  //id
    lvl2_pack_end,      //this
    0,                  //top
    0,      //right
    &i_lvl0,                  //bot
    &i_lvl0,                  //left
    rt_room,
    0,
    {
        {e_c_ghost, 72, 168, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl3 = {//left bottom
    3,                  //id
    lvl3_pack_end,      //this
    &i_lvl0,                  //top
    &i_lvl5,      //right
    0,                  //bot
    0,                  //left
    lb_room,
    0,
    {
        {e_c_powerUp, 4, 96, 2},
        {e_c_ghost, 20, 168, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl4 = {//right bottom
    4,                  //id
    lvl4_pack_end,      //this
    &i_lvl0,                  //top
    0,      //right
    0,                  //bot
    &i_lvl5,                  //left
    rb_room,
    0,
    {
        {e_c_sonic, 72, 152, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl5 = {
    5,                  //id
    lvl5_pack_end,      //this
    &i_lvl0,                  //top
    &i_lvl4,      //right
    0,                  //bot
    &i_lvl3,                  //left
    normal_room,
    0,
    {
        {e_c_shoot, 72, 64, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};

const lvl_t i_boss1 = {
    6,                  //id
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

u8 cleared_rooms[8];
lvl_t level;
u8 tilemap_start[tilemap_size];
#define tilemap_end  (tilemap_start + tilemap_size - 1)

void lt_room(){
    tilemap_start[21*tilemap_W + 9] = 19;
    sys_ren_tile(19, 9*4, (21+3)*8 );
    tilemap_start[21*tilemap_W + 10] = 19;
    sys_ren_tile(19, 10*4, (21+3)*8);
    cleared_rooms[0]|=0x01;
}
void lb_room(){
    tilemap_start[9] = 19;
    sys_ren_tile(19, 9*4, 3*8);
    tilemap_start[10] = 19;
    sys_ren_tile(19, 10*4, 3*8);
    cleared_rooms[0]|=0x08;
}
void rt_room(){
    tilemap_start[21*tilemap_W + 9] = 19;
    sys_ren_tile(19, 9*4, (21+3)*8 );
    tilemap_start[21*tilemap_W + 10] = 19;
    sys_ren_tile(19, 10*4, (21+3)*8);
    cleared_rooms[0]|=0x02;
}
void rb_room(){
    tilemap_start[9] = 19;
    sys_ren_tile(19, 9*4, 3*8);
    tilemap_start[10] = 19;
    sys_ren_tile(19, 10*4, 3*8);
    cleared_rooms[0]|=0x04;
}
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
    final_door_open = 0;
    cpct_memcpy(&level, &i_lvl0, sizeof(lvl_t));//temporal
    cpct_memset(cleared_rooms, 0, sizeof(cleared_rooms));

    man_ent_init();
    man_ent_create_class(e_c_char, 16, 80, 5);
    man_level_load(16, 80);

}

void man_level_load(u8 px, u8 py){
    u8 it = 0;
    ent_class* class = &level.entities[it]; 

    cpct_zx7b_decrunch_s(tilemap_end, level.self);
    sys_ren_draw_tilemap(tilemap_start);
    
    man_ent_reset();
    man_ent_get_char()->x = px;
    man_ent_get_char()->y = py;
    man_ent_create_class(e_c_tools, 0, 0, 0);
    

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
    ent_t* player = man_ent_get_char();
    if(player->x == 0){
        player->x = 72;
        cpct_memcpy(&level, level.left, sizeof(lvl_t));
        man_level_load(player->x, player->y);
    }
    else if(player->x == 76){
        player->x = 4;
        cpct_memcpy(&level, level.right, sizeof(lvl_t));
        man_level_load(player->x, player->y);
    }
    else if(player->y == 24){
        player->y = 168;
        cpct_memcpy(&level, level.top, sizeof(lvl_t));
        man_level_load(player->x, player->y);
    }
    else if(player->y == 176){
        player->y = 32;
        cpct_memcpy(&level, level.bot, sizeof(lvl_t));
        man_level_load(player->x, player->y);
    }
    else if(final_door_open){
        if(level.self == lvl0_pack_end){
            if( player->x+player->w > 36  &&  player->x < 44){
                if(player->y > 140) {
                    if(cpct_isKeyPressed(Key_W)){
                        cpct_memcpy(&level, &i_boss1, sizeof(lvl_t));
                        man_level_load(20, 160);
                    }
                }
            }
        }
    }
}

void man_level_add_mp_end_lvl(){
    ent_t* player = man_ent_get_char();
    if(man_ent_get_char()->mp == player->prev_vy -1){
        man_ent_get_char()->mp++;
    }
    else if(man_ent_get_char()->mp < player->prev_vy -1){
        man_ent_get_char()->mp++;
        man_ent_get_char()->mp++;
    }
}

void man_level_kill_enemy(){
    level.enemies--;
    if(level.enemies == 0){
        cleared_rooms[level.id]=1;
        level.cleared_func();
        man_level_add_mp_end_lvl();
    }
}

u8* man_level_get_tilemap(){
    return tilemap_start;
}
u8 man_level_get_door(){
    return final_door_open;
}
