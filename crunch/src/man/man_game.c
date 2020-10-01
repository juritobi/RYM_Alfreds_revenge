#include "man_game.h"
#include <man/man_ent.h>
#include <sys/physics.h>
#include <sys/render.h>
#include <sprites/char.h>
#include <sprites/tileset.h>
#include <tilemaps/lvl0.h>
#include <tilemaps/lvl0_pack.h> 

const ent_t init_player = {
    e_t_physics | e_t_render | e_t_input,
    4,168,
    4,168,
    4,24,
    0,0,
    0,0,
    spr_char_0
};

u8 tset[lvl0_pack_size];


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
    u8* tset_end= &tset[lvl0_pack_size-1];
    man_ent_init();
    create_ent();

    cpct_zx7b_decrunch_s(tset_end, lvl0_pack_end);
    cpct_etm_setDrawTilemap4x8_ag (lvl0_W, lvl0_H, lvl0_W, tileset_00);
    cpct_etm_drawTilemap4x8_ag(CPCT_VMEM_START, tset);
}

void man_game_play(){
    while (1){
        sys_phy_update();
        sys_ren_update();
        wait(3);
    }
}