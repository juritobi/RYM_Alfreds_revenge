#include "UI.h"
#include <man/man_ent.h>
#include <sprites/UI.h>
#include <sprites/numbers.h>

u16 score;
ent_t* player; 
u8 prev_hp;
u8 prev_mp;
u8 ad;
u8 ap;
u8 down_score_timer;

u8* numbers[9];

void draw_sprite(u8* sprite, u8 x, u8 y){
    u8* pos = cpct_getScreenPtr (CPCT_VMEM_START,x, y);
    cpct_drawSprite (sprite, pos, 2, 8);
}

void draw_score(){
    u8 index = 75;
    u16 inscore = score;
    while(inscore){
        u8 carry = inscore%10; 
        inscore = inscore/10;
        draw_sprite(numbers[carry], index, 13);
        index -=2;
    }
}


void sys_UI_init(){
    u8* pos;
    u8 looper;
    u8 index;

    score = 60000;
    player = man_ent_get_char();
    prev_hp = player->hp;
    prev_mp = player->mp;
    ad = (player+1)->damage;
    ap = (player+2)->damage;
    down_score_timer= 0xFF;

    numbers[0] = spr_number_00;
    numbers[1] = spr_number_01;
    numbers[2] = spr_number_02;
    numbers[3] = spr_number_03;
    numbers[4] = spr_number_04;
    numbers[5] = spr_number_05;
    numbers[6] = spr_number_06;
    numbers[7] = spr_number_07;
    numbers[8] = spr_number_08;
    numbers[9] = spr_number_09;



    //background
    cpct_drawSolidBox (CPCT_VMEM_START, 0xF0, 40, 24);
    cpct_drawSolidBox (CPCT_VMEM_START+40, 0xF0, 40, 24);

    //hp mp
    draw_sprite(spr_UI_00, 2, 3);
    draw_sprite(spr_UI_05, 2, 13);

    looper=player->hp;
    index = 4;
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
    draw_sprite(numbers[ad], 44, 3);
    draw_sprite(spr_UI_09, 40, 13);
    draw_sprite(numbers[ap], 44, 13);

    //score
    pos = cpct_getScreenPtr (CPCT_VMEM_START,67, 3);
    cpct_waitHalts(1);
    cpct_drawStringM1 ("score", pos);
    draw_score();
}




void sys_UI_update(){
    if(prev_hp > player->hp){ // pierdes vida
        draw_sprite(spr_UI_02, 2+prev_hp*2, 3);
        prev_hp = player->hp;
    }
    else if(prev_hp < player->hp) { // ganas vida
        draw_sprite(spr_UI_01, 2+(prev_hp+1)*2, 3);
        prev_hp = player->hp;
    }

    if(prev_mp > player->mp){ // pierdes mana
        draw_sprite(spr_UI_07, 2+prev_mp*2, 13);
        prev_mp = player->mp;
    }
     
    while(prev_mp < player->mp){// ganas mana
        draw_sprite(spr_UI_06, 2+(prev_mp+1)*2, 13);
        prev_mp++;
    }

    --down_score_timer;
    if(!down_score_timer){
        score--;
        draw_score();
    }


}