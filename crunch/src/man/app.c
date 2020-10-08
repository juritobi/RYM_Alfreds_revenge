#include "app.h"
#include <man/man_game.h>

void man_app_init(){

    cpct_clearScreen(0x0);
    cpct_setDrawCharM1(3, 0);
    cpct_drawStringM1("press any key to start", CPCT_VMEM_START+500);
}

void man_app_update(){
    while(1){
        cpct_scanKeyboard_f();
        if(cpct_isAnyKeyPressed()){
            man_game_init();
            man_game_play();
            cpct_clearScreen(0x0);
            cpct_drawStringM1("TAS MORIDO", CPCT_VMEM_START+500);
            cpct_drawStringM1("press any key to retry", CPCT_VMEM_START+900);
        }
    }
}