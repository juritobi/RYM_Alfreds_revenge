#include "man_game.h"
#include <sys/physics.h>
#include <sys/render.h>
#include <sys/input.h>
#include <sys/AI.h>
#include <sys/col.h>
#include <man/level.h>
#include <man/man_ent.h>

#include <constants.h>
void man_game_check_level_change();
extern const lvl_t i_lvl0;
extern const lvl_t i_lvl1;

const lvl_t i_lvl0 = {
    lvl0_pack_end,      //this
    0,                  //top
    &i_lvl1,      //right
    0,                  //bot
    0,                  //left
    {
        {e_c_shoot, 70, 176},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl1 = {
    lvl1_pack_end,
    0,                  
    0,      
    0,
    &i_lvl0,
    {
        {e_c_shoot, 50, 100},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }                  
};

lvl_t* actual_level;
u8 in_game;

void wait(u8 n){
    do{
        cpct_waitHalts(2);
        cpct_waitVSYNC();
    }while (--n);
}

void man_game_init(){
    actual_level = &i_lvl0;
    man_level_load(actual_level, 4,168);
    in_game = 1;
}

void man_game_load_level(lvl_t* level_to_load){
    ent_t* player = man_ent_get_char();
    actual_level = level_to_load;
    man_level_load(actual_level, player->x, player->y);
}

void man_game_check_level_change(){
    ent_t* player = man_ent_get_char();
    if(player->x == 0){
        player->x = 72;
        man_game_load_level(actual_level->left);
    }
    else if(player->x == 76){
        player->x = 4;
        man_game_load_level(actual_level->right);
    }
    else if(player->y == 0){
        player->y = 168;
        man_game_load_level(actual_level->top);
    }
    else if(player->y == 176){
        player->y = 8;
        man_game_load_level(actual_level->right);
    }
}

void man_game_exit(){
    in_game=0;
}

void man_game_play(){
    while (in_game){
        sys_AI_update();
        sys_input_update();
        sys_col_update();
        sys_phy_update();
        man_game_check_level_change();
        sys_ren_update();
        wait(1);
    }
}