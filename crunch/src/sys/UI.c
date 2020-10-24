#include "UI.h"
#include <man/man_ent.h>
#include <sprites/UI.h>
#include <sprites/numbers.h>

u16 score;
ent_t* player; 
u8 prev_max_hp;
u8 prev_max_mana;
u8 prev_hp;
u8 prev_mp;
u8 ad;
u8 ap;
u8 down_score_timer;

u8* numbers[10];

void draw_sprite(u8* sprite, u8 x, u8 y){
    u8* pos = cpct_getScreenPtr (CPCT_VMEM_START,x, y);
    cpct_drawSprite (sprite, pos, 2, 8);
}

void sys_UI_hp_mp_bars(u8 w, u8 h, u8* sprite_line, u8 num){
    u8 looper;
    u8 index;

    draw_sprite(sprite_line, w, h);
    looper=num;
    index = w+2;
    while(looper){
        draw_sprite(sprite_line +SPR_UI_00_W*SPR_UI_00_H, index, h);
        --looper;
        index +=2;
    }
    draw_sprite(sprite_line+SPR_UI_00_W*SPR_UI_00_H*3, index, h);
}
void sys_UI_draw_damage(u8 w, u8 h, u8* sprite, u8 num){
    draw_sprite(sprite, w, h);
    draw_sprite(numbers[num], w+4, h);
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

void sys_UI_pre_init(){
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
    prev_max_hp = player->prev_vx;
    prev_max_mana = player->prev_vy;


    //background
    cpct_drawSolidBox (CPCT_VMEM_START, 0xF0, 40, 24);
    cpct_drawSolidBox (CPCT_VMEM_START+40, 0xF0, 40, 24);

    //hp mp
    sys_UI_hp_mp_bars(2, 3, spr_UI_00, prev_max_hp);
    sys_UI_hp_mp_bars(2, 13, spr_UI_05, prev_max_mana);

    
    //damage
    sys_UI_draw_damage(40, 3, spr_UI_04, ad);
    sys_UI_draw_damage(40, 13, spr_UI_09, ap);

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

    if(prev_max_hp < player->prev_vx){
        sys_UI_hp_mp_bars(2, 3, spr_UI_00, player->hp);
        prev_max_hp = player->hp;
    }

    if(prev_max_mana < player->prev_vy){
        sys_UI_hp_mp_bars(2, 13, spr_UI_05, player->mp);
        prev_max_mana = player->mp;
    }
    --down_score_timer;
    if(!down_score_timer){
        score--;
        draw_score();
    }


}