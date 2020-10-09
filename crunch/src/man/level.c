#include "level.h"
#include <man/man_ent.h>
#include <sys/render.h>
#include <constants.h>

u8 tilemap_start[tilemap_size];
#define tilemap_end  (tilemap_start + tilemap_size - 1)

void man_level_load(lvl_t* map, u8 x, u8 y){
    u8 it = 0;
    ent_class* class = &map->entities[it];
    
    cpct_zx7b_decrunch_s(tilemap_end, map->self);
    sys_ren_draw_tilemap(tilemap_start);
    
    man_ent_init();
    man_ent_create_class(e_c_char, x, y);

    while(class->type != e_c_undefined){
        man_ent_create_class(class->type, class->x, class->y);
        it++;
        class = &map->entities[it];
    }
}

u8* man_level_get_tilemap(){
    return tilemap_start;
}