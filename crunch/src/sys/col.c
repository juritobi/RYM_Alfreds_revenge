#include "physics.h"
#include <man/man_ent.h>
#include <man/level.h>
#include <constants.h>

void sys_col_one(ent_t* e){
    u8 tile_x = e->x/4;
    u8 tile_y = e->y/8;
    u8 next_tile_x = tile_x + e->vx;
    u8* tilemap = man_level_get_tilemap();

    u16 array_pos= tile_y*tilemap_W + next_tile_x;

    if(e->x/4 != (e->x-1)/4){
        if(tilemap[array_pos] == 7){
            e->vx = 0;
        }
    }
    
}

void sys_col_update(){
    man_ent_forall_type(sys_col_one, e_t_col);
}