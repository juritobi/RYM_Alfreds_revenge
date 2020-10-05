#include "physics.h"
#include <man/man_ent.h>
#include <man/level.h>
#include <constants.h>

void sys_col_one(ent_t* e){
    u8 tile_x = e->x/2;
    u8 tile_y = e->y/4;
    u8 next_tile_x = tile_x + e->vx*4;
    u8* tilemap = man_level_get_tilemap();

    u8 array_pos= next_tile_x + tile_y*tilemap_W;
    array_pos++;
    if(tilemap[array_pos--] == 7){
        e->x = e->prevx;
    }
}

void sys_col_update(){
    man_ent_forall_type(sys_col_one, e_t_col);
}