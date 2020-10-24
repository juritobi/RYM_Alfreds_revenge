#pragma once
#include <cpctelera.h>
void interrupt_1();
void interrupt_2();
void interrupt_3();
void interrupt_4();
void interrupt_5();
void interrupt_6();


void man_app_init(); 
void man_app_update();


void man_app_main();
void man_app_main_update();
void man_app_controls();
void man_app_controls_update();
void man_app_sel();
void man_app_sel_update();
void man_app_game();
void man_app_game_update();

extern const cpct_keyID* left;
extern const cpct_keyID* right;
extern const cpct_keyID* up;
extern const cpct_keyID* down;
extern const cpct_keyID* fire1;
extern const cpct_keyID* fire2;