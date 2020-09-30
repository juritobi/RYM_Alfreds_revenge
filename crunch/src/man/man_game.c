#include "man_game.h"
#include <man/man_ent.h>
#include <sys/physics.h>
#include <sys/render.h>
#include <sprites/char.h>

const u8 sprite[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 
};

const ent_t init_player = {
    e_t_physics | e_t_render | e_t_input,
    50,50,
    50,50,
    4,32,
    -1,0,
    -1,0,
    spr_char
};

void create_ent(){
    ent_t* e = man_ent_create();
    cpct_memcpy(e, &init_player, sizeof(ent_t));
}

void wait(u8 n){
    do{
        cpct_waitHalts(2);
        cpct_waitVSYNC();
    }while (--n);
}

void man_game_init(){
    man_ent_init();
    create_ent();
}

void man_game_play(){
    while (1){
        sys_phy_update();
        sys_ren_update();
        wait(3);
    }
}