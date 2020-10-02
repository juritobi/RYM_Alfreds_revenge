#include "app.h"
#include <man/man_game.h>

void man_app_init(){

    cpct_clearScreen(0x0);

    // Draw a string using drawString function for mode 1
    cpct_setDrawCharM1(0xf0, 0x0f);
    cpct_drawStringM1("Mode 1 string :D", CPCT_VMEM_START+30);
}

void man_app_update(){
    man_game_init();
    man_game_play();
}