#include "physics.h"
#include <man/man_ent.h>
#include <man/level.h>
#include <sys/input.h>
#include <sys/render.h>
#include <constants.h>


void sys_phy_one(ent_t* e){

    u8 x = e->tile_x;//modded
    u8 moded_x;
    u8 y = e->tile_y;
    u8 rx = e->tile_x_r;
    u8 ry = e->tile_y_r;
    u8 w = e->tile_w;
    u8 h = e->tile_h;//modded
    i8 vx = e->vx;//modded
    i8 vy = e->vy;

    if(e == player){
        if(swordUp){
            ++w;
            if(e->move_dir == dir_left) --x;
        }
    }
    moded_x = x;
    if(vx){
        if(vx<0){
            x+=w;
            if(!rx) --x;
        }
        if(ry) ++h;

        while (h){
            --h;
            sys_ren_set_tile( tilemap_start[x+(y+h)*tilemap_W], x*4, (y+3+h)*8);
        }
    }

    h = e->tile_h;
    if(vy){
        if(vy<0){
            y+=h;
            if(!ry) --y;
        }
        if(rx) ++w;

        while (w){
            --w;
            sys_ren_set_tile( tilemap_start[moded_x+w+y*tilemap_W], (moded_x+w)*4, (y+3)*8);
        }
    }

    e->x += vx;
    e->y += vy;
}

void sys_phy_update(){
    man_ent_forall_type(sys_phy_one, e_t_physics);
}