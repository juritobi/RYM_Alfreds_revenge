#include "anim.h"
#include <sprites/char.h>
#include <man/man_ent.h>

const spr_tile_t character_spriteset [4] = {
    {1, spr_char_0},
    {2, spr_char_0},
    {1, spr_char_2},
    {1, spr_char_3}
};

void sys_anim_one(ent_t* e){
    u8 action = e->action & 0x0F;
    u8 prev_action = e->action >> 4;
    const spr_tile_t * tile = &character_spriteset[action];
    u8 step = e->anim_step;
    u8 timer = e->anim_timer;

    if(action != prev_action){
        step = 0;
        timer = anim_frame_time;
    }

    timer --;
    if(timer == 0){
        timer = anim_frame_time;
        step ++;
        if(step >= tile->length){
            step=0;
        }
    }

    e->sprite = tile->first_frame + step * char_sprite_size + e->move_dir * char_sprsheet_line;
    e->action = action<<4;
    e->anim_timer = timer;
    e->anim_step = step;
}
void sys_anim_update(){
    man_ent_forall_type(sys_anim_one, e_t_anim);
}

