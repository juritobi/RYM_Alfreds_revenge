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


u8 next_screen;
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

void man_game_create_player(player_t* stats){
    man_ent_init();
    man_ent_create_class(e_c_char, 32, 32, stats->mp);
    man_ent_create_class(e_c_tools, 0, 0, 0);
    player->hp = stats->hp;
    player->prev_vx = stats->hp;
    player->prev_vy = stats->mp;
    (player+1)->damage = stats->ad;
    (player+2)->damage = stats->ap;
}

void man_game_init(){
    next_screen = 0;
    render_signal=0;
    waiting_render_signal=0;
    cpct_setDrawCharM1(3, 1);

    man_level_init();
    sys_UI_init();
    sys_AI_init();
    sys_anim_init();
    sys_Input_init();
    sys_col_init();
    //sys_phy_init();
    sys_ren_init();
}

void man_game_exit(u8 next){
    next_screen=next;
}

u8 man_game_play(){
    while (!next_screen){
        
        man_ent_forall_type(man_ent_update,e_t_render);
        sys_UI_update();
        sys_AI_update();
        sys_input_update();
        sys_anim_update();
        sys_col_update();
        sys_phy_update();
        sys_input_sword_move();
        man_level_update();
        sys_ren_setup();

        wait_render_signal();
        sys_ren_render();

        if(cpct_isKeyPressed(Key_Esc)){
            next_screen=50;
        }
        if(next_screen == 50){
            cpct_setBorder(HW_WHITE);
            cpct_waitHalts(32);
            while(next_screen == 50){
                if(cpct_isKeyPressed(Key_Esc)){
                    next_screen=0;
                }
            }
            cpct_setBorder(HW_BLACK);
            cpct_waitHalts(32);
        }
    }


    return next_screen;
}