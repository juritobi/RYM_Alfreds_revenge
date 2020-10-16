#include "man_game.h"
#include <sys/physics.h>
#include <sys/render.h>
#include <sys/input.h>
#include <sys/AI.h>
#include <sys/UI.h>
#include <sys/col.h>
#include <sys/anim.h>
#include <man/level.h>
#include <man/man_ent.h>

#include <constants.h>


u8 in_game;
u8 render_signal;
u8 waiting_render_signal;

void activate_render_signal(){
    if(waiting_render_signal){
        render_signal=1;
    }
}
void wait_render_signal(){
    waiting_render_signal = 1;
    while(1){
        if(render_signal){
            render_signal=0;
            break;
        }
    }
    waiting_render_signal = 0;
}
void man_game_init(){
    in_game = 1;
    render_signal=0;
    waiting_render_signal=0;

    man_level_init();
    sys_UI_init();
    sys_AI_init();
    //sys_Input_init();
    //sys_col_init();
    //sys_phy_init();
    sys_ren_init();
}

void man_game_exit(){
    in_game=0;
}

void man_game_play(){
    while (in_game){
        
        cpct_setBorder(HW_RED);
        man_ent_forall_type(man_ent_update,e_t_render);
        sys_UI_update();

        cpct_setBorder(HW_BLUE);
        sys_AI_update();
        
        cpct_setBorder(HW_WHITE);
        sys_input_update();

        cpct_setBorder(HW_CYAN);
        sys_anim_update();

        cpct_setBorder(HW_BRIGHT_RED);
        sys_col_update();

        cpct_setBorder(HW_PINK);
        sys_phy_update();
        sys_input_sword_move();

        cpct_setBorder(HW_YELLOW);
        man_level_update();

        cpct_setBorder(HW_MAGENTA);
        sys_ren_setup();
        cpct_setBorder(HW_BLACK);
        
        cpct_waitVSYNC();
        
        wait_render_signal();
        cpct_setBorder(HW_GREEN);
        sys_ren_render();
        cpct_setBorder(HW_BLACK);

        /*cpct_waitVSYNC();
        cpct_waitHalts(2);
        cpct_waitVSYNC();
        cpct_waitVSYNC();
        cpct_waitHalts(2);
        cpct_waitVSYNC();
        cpct_waitVSYNC();
        cpct_waitHalts(2);
        cpct_waitVSYNC();
        cpct_waitVSYNC();
        cpct_waitHalts(2);
        cpct_waitVSYNC();
        cpct_waitVSYNC();
        cpct_waitHalts(2);
        cpct_waitVSYNC();
        cpct_waitVSYNC();
        cpct_waitHalts(2);
        cpct_waitVSYNC();
*/
    }
}