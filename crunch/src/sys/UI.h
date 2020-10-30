#pragma once
#include <cpctelera.h>

void sys_UI_pre_init();
void sys_UI_hp_mp_bars(u8 w, u8 h, u8* sprite_line, u8 num);
void sys_UI_draw_damage(u8 w, u8 h, u8* sprite, u8 num);
void sys_UI_init();
void sys_UI_update();
void draw_score(u8 x, u8 y);
extern u16 score;