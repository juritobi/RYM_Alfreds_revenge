#include "UI.h"
#include <man/man_ent.h>
#include <sprites/UI.h>
#include <sprites/numbers.h>
#include <man/app.h>

u16 score;
u8 down_score_timer;
u8 prev_max_hp;
u8 prev_max_mana;
u8 prev_hp;
u8 prev_mp;
u8 ad;
u8 ap;

const u8* numbers[10];

void draw_sprite(const u8* sprite, u8 x, u8 y){
    u8* pos = cpct_getScreenPtr (CPCT_VMEM_START,x, y);
    cpct_drawSprite (sprite, pos, 2, 8);
}

void sys_UI_hp_mp_bars(u8 x, u8 y, u8* sprite_line, u8 num){

    draw_sprite(sprite_line,x, y);
    x += 2;
    while(num){
        draw_sprite(sprite_line +SPR_UI_00_W*SPR_UI_00_H, x, y);
        --num;
        x +=2;
    }
    draw_sprite(sprite_line+SPR_UI_00_W*SPR_UI_00_H*3, x, y);
}
void sys_UI_draw_damage(u8 x, u8 y, u8* sprite, u8 num){
    draw_sprite(sprite, x, y);
    draw_sprite(numbers[num], x+4, y);
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
    score = 0;
    down_score_timer= 0xFF;
    prev_max_hp = prev_hp = player->hp;
    prev_max_mana = prev_mp = player->mp;
    ad = (player+1)->damage;
    ap = (player+2)->damage;
    
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
    cpct_waitHalts(1);
    app_draw_string(67,3,"score");
    draw_sprite(numbers[0], 75, 13);
    draw_score();
}

void sys_UI_update(){
    if(prev_hp != player->hp){
        if(prev_hp > player->hp){ // pierdes vida
            draw_sprite(spr_UI_02, 2+prev_hp*2, 3);
            prev_hp = player->hp;
        }
        else{
            draw_sprite(spr_UI_01, 2+(prev_hp+1)*2, 3);
            prev_hp = player->hp;
        }
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

    if(ad < (player+1)->damage){
        ad = (player+1)->damage;
        sys_UI_draw_damage(40, 3, spr_UI_04, ad);
    }
    if(ap < (player+2)->damage){
        ap = (player+2)->damage;
        sys_UI_draw_damage(40, 13, spr_UI_09, ap);
    }

    --down_score_timer;
    if(!down_score_timer){
        if(score) --score;
        draw_score();
    }


}