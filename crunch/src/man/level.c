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
    e_t_physics | e_t_render | e_t_input,  //tipo
    4,168,                                  //x,y
    4,168,                                  //prevx, prevy
    4,24,                                   //w,h
    0,0,                                    //vx,vy
    0,0,                                    //prevvx, prevvx
    -1,
    spr_char_0,                             //sprite
    0x0000                                  //AI function
};
const ent_t init_sword = {
    e_t_dead | e_t_son | e_t_render,            //tipo
    4,0,                                  //parent displacement for sons
    0,0,                                    //prevx, prevy
    4,24,                                   //w,h
    0,0,                                    //vx,vy
    0,0,                                    //prevvx, prevvx
    -1,
    spr_char_1,                             //sprite
    0x0000                                  //AI function
};
const ent_t init_knife = {
    e_t_dead | e_t_son | e_t_render | e_t_physics,           //tipo
    4,8,                                  //parent displacement for sons
    0,0,                                    //prevx, prevy
    4,8,                                   //w,h
    0,0,                                    //vx,vy
    0,0,                                    //prevvx, prevvx
    -1,
    spr_char_2,                             //sprite
    0x0000                                  //AI function
};
const ent_t init_shoot = {
    e_t_render | e_t_AI,
    74,176,
    74,176,                                 
    4,16,
    -1,0,
    0,0,
    -1,
    spr_shooter_0,
    sys_AI_shoot
};
const ent_t init_shoot_son = {
    e_t_dead | e_t_son | e_t_physics | e_t_render,
    4,4,
    0,0,
    4,8,
    -1,0,
    -1,0,
    -1,
    spr_p_1,
    0x0000
};

void man_level_load(u8* map){
    ent_t* e;
    cpct_zx7b_decrunch_s(tilemap_end, map);
    sys_ren_draw_tilemap(tilemap_start);
    
    man_ent_init();
    e = man_ent_create_from_template(&init_player);
    e = man_ent_create_from_template(&init_sword);
    e = man_ent_create_from_template(&init_knife);
    e = man_ent_create_from_template(&init_shoot);
    e = man_ent_create_from_template(&init_shoot_son);
}