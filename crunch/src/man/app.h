#pragma once
#include <cpctelera.h>
void interrupt_1();
void interrupt_2();
void interrupt_3();
void interrupt_4();
void interrupt_5();
void interrupt_6();


typedef struct player player_t;
typedef struct player{
   u8 hp, mp, ap, ad;   
};

void app_draw_string(u8 x, u8 y, void* string);

void man_app_init(); 
void man_app_update();

void man_app_intro();
void man_app_intro_update();
void man_app_main();
void man_app_main_update();
void man_app_controls();
void man_app_controls_update();
void man_app_sel();
void man_app_sel_update();
void man_app_game();
void man_app_game_update();
void man_app_end();
void man_app_end_update();

extern cpct_keyID* left;
extern cpct_keyID* right;
extern cpct_keyID* up;
extern cpct_keyID* down;
extern cpct_keyID* fire1;
extern cpct_keyID* fire2;