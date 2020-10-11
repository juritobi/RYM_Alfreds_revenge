#include "UI.h"
#include <man/man_ent.h>
#include <sprites/UI.h>
#include <sprites/numbers.h>

void draw_sprite(u8* sprite, u8 x, u8 y){
    u8* pos = cpct_getScreenPtr (CPCT_VMEM_START,x, y);
    cpct_drawSprite (sprite, pos, 2, 8);
}

void sys_UI_init(){
    u8* pos;
    ent_t* player = man_ent_get_char();
    u8 looper = player->hp;
    u8 index = 4;
    //background
    cpct_drawSolidBox (CPCT_VMEM_START, 0xF0, 40, 24);
    cpct_drawSolidBox (CPCT_VMEM_START+40, 0xF0, 40, 24);

    //hp mp
    draw_sprite(spr_UI_00, 2, 3);
    draw_sprite(spr_UI_05, 2, 13);

    while(looper){
        draw_sprite(spr_UI_01, index, 3);
        --looper;
        index +=2;
    }
    draw_sprite(spr_UI_03, index, 3);

    looper=player->mp;
    index = 4;
    while(looper){
        draw_sprite(spr_UI_06, index, 13);
        --looper;
        index +=2;
    }
    draw_sprite(spr_UI_08, index, 13);

    //damage
    draw_sprite(spr_UI_04, 40, 3);
    draw_sprite(spr_number_00, 44, 3);
    draw_sprite(spr_UI_09, 40, 13);
    draw_sprite(spr_number_00, 44, 13);

    //score
    pos = cpct_getScreenPtr (CPCT_VMEM_START,67, 3);
    cpct_waitHalts(1);
    cpct_drawStringM1 ("score", pos);

    looper = 4;
    index = 68;
    while(looper){
        draw_sprite(spr_number_00, index, 13);
        --looper;
        index +=2;
    }
}

/*void sys_UI_update(){
    cpct_drawSolidBox (CPCT_VMEM_START, 0, 80, 16);
}*/