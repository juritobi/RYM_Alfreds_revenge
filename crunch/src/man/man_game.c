#include "man_game.h"
#include <sys/physics.h>
#include <sys/render.h>
#include <sys/input.h>
#include <sys/AI.h>
#include <man/level.h>

#include <constants.h>

const lvl_t init_lvl0 = {
    lvl0_pack_end,      //this
    0,                  //top
    lvl1_pack_end,      //right
    0,                  //right
    0                   //bot
};
const lvl_t init_lvl1 = {
    lvl1_pack_end,
    0,                  
    lvl0_pack_end,      
    0,
    0                   
};

void wait(u8 n){
    do{
        cpct_waitHalts(2);
        cpct_waitVSYNC();
    }while (--n);
}

void man_game_init(){

    man_ent_init();
    man_level_load(lvl1_pack_end);
}

void man_game_play(){
    while (1){
        sys_AI_update();
        sys_input_update();
        sys_phy_update();
        sys_ren_update();
        wait(1);
    }
}
