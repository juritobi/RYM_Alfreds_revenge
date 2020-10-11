#include "app.h"
#include <man/man_game.h>
#include <sprites/g_palette.h>

void interrupt_1(){
    //cpct_setBorder(HW_RED);
    cpct_scanKeyboard();
    cpct_setInterruptHandler(interrupt_2);
}
void interrupt_2(){
    //cpct_setBorder(HW_GREEN);
    cpct_setInterruptHandler(interrupt_3);
}
void interrupt_3(){
    //cpct_setBorder(HW_CYAN);
    cpct_setInterruptHandler(interrupt_4);
}
void interrupt_4(){
    //cpct_setBorder(HW_BLACK);
    cpct_setInterruptHandler(interrupt_5);
}
void interrupt_5(){
    //cpct_setBorder(HW_WHITE);
    cpct_setInterruptHandler(interrupt_6);
}
void interrupt_6(){
    //cpct_setBorder(HW_YELLOW);
    activate_render_signal();
    cpct_setInterruptHandler(interrupt_1);
}

void man_app_init(){
    cpct_disableFirmware();
    cpct_setPalette(g_palette,4);

    

    cpct_clearScreen(0x0);
    cpct_setDrawCharM1(3, 0);
    cpct_drawStringM1("press any key to start", CPCT_VMEM_START+500);
    cpct_setDrawCharM1(3, 1);
    cpct_waitVSYNC();
    cpct_waitHalts(3);
    cpct_waitVSYNC();
    cpct_setInterruptHandler(interrupt_1);
}

void man_app_update(){
    while(1){
        if(cpct_isAnyKeyPressed()){
            man_game_init();

            man_game_play();
            cpct_clearScreen(0x0);
            cpct_drawStringM1("TAS MORIDO", CPCT_VMEM_START+500);
            cpct_drawStringM1("press any key to retry", CPCT_VMEM_START+900);
        }
        cpct_waitHalts(1);
    }
}