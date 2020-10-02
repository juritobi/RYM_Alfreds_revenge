#include "level.h"
#include <man/man_ent.h>
#include <sys/render.h>
#include <sys/AI.h>
#include <sprites/char.h>
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
const ent_t init_follow = {
    e_t_physics | e_t_render | e_t_AI,
    74,168,
    74,168,
    4,24,
    -1,0,
    0,0,
    spr_char_1,
    sys_AI_follow//behaviour function
};

void man_level_load(u8* map){
    ent_t* e;
    cpct_zx7b_decrunch_s(tilemap_end, map);
    sys_ren_draw_tilemap(tilemap_start);
    
    e = man_ent_create();
    cpct_memcpy(e, &init_player, sizeof(ent_t));
    e = man_ent_create();
    cpct_memcpy(e, &init_follow, sizeof(ent_t));
}