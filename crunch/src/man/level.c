#include "level.h"
#include <man/man_ent.h>
#include <sys/render.h>
#include <sys/AI.h>
#include <sprites/char.h>
#include <sprites/shooter.h>
#include <sprites/proyectile.h>
#include <constants.h>

u8 tilemap_start[tilemap_size];
#define tilemap_end  (tilemap_start + tilemap_size - 1)

const ent_t init_player = {
    e_t_physics | e_t_render | e_t_input,
    4,168,
    4,168,
    4,24,
    0,0,
    0,0,
    spr_char_0,
    0x0000//behaviour function
};
const ent_t init_shoot = {
    e_t_render | e_t_AI,
    74,176,
    74,176,
    4,16,
    -1,0,
    0,0,
    spr_shooter_0,
    sys_AI_follow//behaviour function
};
const ent_t init_shoot_p = {
    e_t_physics | e_t_render,
    72,180,
    72,180,
    4,8,
    -1,0,
    -1,0,
    spr_p_1,
    0x0000//behaviour function
};

void man_level_load(u8* map){
    ent_t* e;
    cpct_zx7b_decrunch_s(tilemap_end, map);
    sys_ren_draw_tilemap(tilemap_start);
    
    man_ent_init();
    e = man_ent_create_from_template(&init_player);
    e = man_ent_create_from_template(&init_shoot);
    e = man_ent_create_from_template(&init_shoot_p);
}