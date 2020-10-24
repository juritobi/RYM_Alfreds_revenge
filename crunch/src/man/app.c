#include "app.h"
#include <man/man_game.h>
#include <sys/UI.h>
#include <sprites/g_palette.h>
#include <sprites/UI.h>

u8 render_count;

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
    render_count--;
    if(!render_count){
        activate_render_signal();
        render_count = 2;
    }
    
    cpct_setInterruptHandler(interrupt_1);
}

const player_t character_sets[] = {
    {10 ,5  ,1  ,1},
    {20 ,1  ,1  ,1},
    {5  ,10 ,1  ,2},
    {5  ,2  ,3  ,1},
    {2  ,10 ,2  ,2},
};

typedef void (*Ptrf_v_v)(void);
Ptrf_v_v executing_state;

cpct_keyID left_value;
cpct_keyID right_value;
cpct_keyID up_value;
cpct_keyID down_value;
cpct_keyID fire1_value;
cpct_keyID fire2_value;

const cpct_keyID* left  = &left_value;
const cpct_keyID* right = &right_value;
const cpct_keyID* up    = &up_value;
const cpct_keyID* down  = &down_value;
const cpct_keyID* fire1 = &fire1_value;
const cpct_keyID* fire2 = &fire2_value;

void man_app_draw_stats(u8 x, u8 y, player_t* stats){
    sys_UI_hp_mp_bars(x+12, y, spr_UI_00, stats->hp);
    sys_UI_hp_mp_bars(x+12, y+10, spr_UI_05, stats->mp);
    sys_UI_draw_damage(x, y, spr_UI_04, stats->ad);
    sys_UI_draw_damage(x, y+10, spr_UI_09, stats->ap);
}



//MENU
void man_app_main(){
    u8 x,y;
    u8* pos;
    cpct_clearScreen(0x0);
    x = 20;
    y = 100;
    pos = cpct_getScreenPtr (CPCT_VMEM_START, x, y);
    cpct_drawStringM1("[esc]  Set controls", pos);
    x = x-2;
    y = y+16;
    pos = cpct_getScreenPtr (CPCT_VMEM_START, x, y);
    cpct_drawStringM1("[enter] Play", pos);
    executing_state = man_app_main_update;
}
void man_app_main_update(){
    if(cpct_isKeyPressed(Key_Esc)){
        executing_state = man_app_controls;
    }
    if(cpct_isKeyPressed(Key_Space)){
        executing_state = man_app_sel;
    }
}
//MENU
//CONTROLS
void man_app_controls(){
    u8 x,y;
    u8* pos;
    cpct_clearScreen(0x0);
    x = 20;
    y = 100;
    pos = cpct_getScreenPtr (CPCT_VMEM_START, x, y);
    cpct_drawStringM1("aqui van los controles", pos);
    executing_state = man_app_controls_update;
}
void man_app_controls_update(){
    executing_state = man_app_main;
}
//CONTROLS

//CHARACTER SELECT
void man_app_sel(){
    u8 x,y;
    u8* pos;
    cpct_clearScreen(0x0);
    x = 20;
    y = 8;
    pos = cpct_getScreenPtr (CPCT_VMEM_START, x, y);
    cpct_drawStringM1("Select your stats: ", pos);

    x = 6;
    y = 60;
    pos = cpct_getScreenPtr (CPCT_VMEM_START, x, y);
    cpct_drawStringM1("[1]", pos);
    x = 6;
    y = 116;
    pos = cpct_getScreenPtr (CPCT_VMEM_START, x, y);
    cpct_drawStringM1("[2]", pos);
    x = 6;
    y = 172;
    pos = cpct_getScreenPtr (CPCT_VMEM_START, x, y);
    cpct_drawStringM1("[3]", pos);

    man_app_draw_stats(14, 55, character_sets);
    man_app_draw_stats(14, 111, character_sets+1);
    man_app_draw_stats(14, 167, character_sets+2);

    executing_state = man_app_sel_update;
}
void man_app_sel_update(){
    if(cpct_isKeyPressed(Key_1)){
        man_game_create_player(character_sets);
        executing_state = man_app_game;
    }
    else if(cpct_isKeyPressed(Key_2)){
        man_game_create_player(character_sets+1);
        executing_state = man_app_game;
    }
    else if(cpct_isKeyPressed(Key_3)){
        man_game_create_player(character_sets+2);
        executing_state = man_app_game;
    }
}
//CHARACTER SELECT

//GAME
void man_app_game(){
    man_game_init();
    executing_state = man_app_game_update;
}
void man_app_game_update(){
    u8 next = man_game_play();
    if(next == win){
        executing_state = man_app_main;
    }
    else if(next== lose){
        executing_state = man_app_main;
    }
}
//GAME


void man_app_init(){
    cpct_disableFirmware();
    cpct_setPalette(g_palette,4);
    cpct_setDrawCharM1(3, 0);

    render_count = 2;

    left_value  = Key_A;
    right_value = Key_D;
    up_value    = Key_W;
    down_value  = Key_S;
    fire1_value = Key_O;
    fire2_value = Key_P;

    sys_UI_pre_init();

    executing_state = man_app_main;
}

void man_app_update(){
    cpct_waitVSYNC();
    cpct_waitHalts(3);
    cpct_waitVSYNC();
    cpct_setInterruptHandler(interrupt_1);

    while(1){
        executing_state();
        cpct_waitHalts(3);
    }
}

/*cpct_clearScreen(0x0);
            cpct_drawStringM1("TAS MORIDO", CPCT_VMEM_START+500);
            cpct_drawStringM1("press any key to retry", CPCT_VMEM_START+900);*/
