#include "man_game.h"
#include <sys/physics.h>
#include <sys/render.h>
#include <sys/input.h>
#include <sys/AI.h>
#include <sys/col.h>
#include <man/level.h>
#include <man/man_ent.h>

#include <constants.h>
void man_game_check_level_change();
extern const lvl_t i_lvl0;
extern const lvl_t i_lvl1;
extern const lvl_t i_lvl2;
extern const lvl_t i_lvl3;
extern const lvl_t i_lvl4;
extern const lvl_t i_lvl5;

const lvl_t i_lvl0 = {
    lvl0_pack_end,      //this
    0,                  //top
    &i_lvl2,      //right
    &i_lvl5,                  //bot
    &i_lvl1,                  //left
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl1 = {
    lvl1_pack_end,      //this
    0,                  //top
    &i_lvl0,      //right
    &i_lvl0,                  //bot
    0,                  //left
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl2 = {
    lvl2_pack_end,      //this
    0,                  //top
    0,      //right
    &i_lvl0,                  //bot
    &i_lvl0,                  //left
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl3 = {
    lvl3_pack_end,      //this
    &i_lvl0,                  //top
    &i_lvl5,      //right
    0,                  //bot
    0,                  //left
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl4 = {
    lvl4_pack_end,      //this
    &i_lvl0,                  //top
    0,      //right
    0,                  //bot
    &i_lvl5,                  //left
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};
const lvl_t i_lvl5 = {
    lvl5_pack_end,      //this
    &i_lvl0,                  //top
    &i_lvl4,      //right
    0,                  //bot
    &i_lvl3,                  //left
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};

lvl_t* actual_level;
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
    actual_level = &i_lvl0;
    in_game = 1;
    render_signal=0;
    waiting_render_signal=0;

    man_level_load(actual_level, 16,168);
    
    sys_UI_init();
    sys_AI_init();
    //sys_Input_init();
    //sys_col_init();
    //sys_phy_init();
    sys_ren_init();
}

void man_game_load_level(lvl_t* level_to_load){
    ent_t* player = man_ent_get_char();
    actual_level = level_to_load;
    man_level_load(actual_level, player->x, player->y);
}

void man_game_check_level_change(){
    ent_t* player = man_ent_get_char();
    if(player->x == 0){
        player->x = 72;
        man_game_load_level(actual_level->left);
    }
    else if(player->x == 76){
        player->x = 4;
        man_game_load_level(actual_level->right);
    }
    else if(player->y == 24){
        player->y = 168;
        man_game_load_level(actual_level->top);
    }
    else if(player->y == 176){
        player->y = 32;
        man_game_load_level(actual_level->bot);
    }
}

void man_game_exit(){
    in_game=0;
}

void man_game_play(){
    while (in_game){

        
        //cpct_setBorder(HW_RED);
        man_ent_forall_type(man_ent_reset_pos,e_t_render);
        sys_UI_update();
        //cpct_setBorder(HW_BLUE);
        sys_AI_update();
        //cpct_setBorder(HW_WHITE);
        sys_input_update();
        //cpct_setBorder(HW_CYAN);
        sys_col_update();
        //cpct_setBorder(HW_PINK);
        sys_phy_update();
        //cpct_setBorder(HW_YELLOW);
        man_game_check_level_change();
        //cpct_setBorder(HW_MAGENTA);
        sys_ren_setup();
        //cpct_setBorder(HW_BLACK);
        
        wait_render_signal();
        //cpct_setBorder(HW_GREEN);
        sys_ren_render();
        cpct_setBorder(HW_BLACK);
    }
}