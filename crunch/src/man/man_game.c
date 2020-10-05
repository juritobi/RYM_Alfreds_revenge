#include "man_game.h"
#include <sys/physics.h>
#include <sys/render.h>
#include <sys/input.h>
<<<<<<< HEAD
#include <sys/AI.h>
#include <man/level.h>
=======
#include <sprites/char.h>
#include <sprites/tileset.h>
#include <tilemaps/lvl0.h>
#include <tilemaps/lvl0_pack.h> 

const ent_t init_player = {
    e_t_physics | e_t_render | e_t_input,
    4,168,                                  // pos
    4,168,                                  // pos ant
    4,24,                                   // ancho - alto
    0,0,                                    // velocidad
    0,0,                                    // velocidad anterior
    -1,                                     // jumping status
    spr_char_0                              // esprait
    
};

u8 tset[lvl0_pack_size];
>>>>>>> input

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
    man_level_load(lvl0_pack_end);
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
