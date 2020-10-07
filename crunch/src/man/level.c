#include "level.h"
#include <man/man_ent.h>
#include <sys/render.h>
#include <constants.h>

u8 tilemap_start[tilemap_size];
#define tilemap_end  (tilemap_start + tilemap_size - 1)

void man_level_load(u8* map){
    ent_t* e;
    cpct_zx7b_decrunch_s(tilemap_end, map);
    sys_ren_draw_tilemap(tilemap_start);
    
    man_ent_init();
    man_ent_create_class(e_c_char, 8,168);
    man_ent_create_class(e_c_shoot, 70, 176);
}

u8* man_level_get_tilemap(){
    return tilemap_start;
}