#include "physics.h"
#include <man/man_ent.h>
#include <man/level.h>
#include <sys/input.h>
#include <sys/render.h>
#include <constants.h>

#define x_div 4
#define y_div 8

void sys_phy_one(ent_t* e){

    u8 tile_x = e->tile_x;
    u8 tile_y = e->tile_y;
    u8 tile_x_r = e->tile_x_r;
    u8 tile_y_r = e->tile_y_r;
    u8 tile_w = e->tile_w;
    u8 tile_h = e->tile_h;

    u8 right_tile;
    u8 bot_tile;
    u16 tile_pointer;

    right_tile = tile_x + tile_w;
    bot_tile = tile_y + tile_h;

    if((e->type & e_t_input) == e_t_input){
        u8 swordUp = sys_input_get_sword_up();
        if(swordUp){
            if(e->move_dir == dir_right){
                tile_w++;
                right_tile++;
            }
            else{
                tile_w++;
                tile_x--;
            }
        }
    }
    //redibujado de tiles
    if(e->vx){
        u8 y_tile_num = tile_h;
        u8 byte_tile_x;
        u8 byte_tile_y;

        if(e->vx<0){
            if(tile_x_r){
                tile_pointer = tile_y * tilemap_W + right_tile;
                byte_tile_x = right_tile;
            }
            else{
                tile_pointer = tile_y * tilemap_W + right_tile-1;
                byte_tile_x = right_tile-1;
            }
        }
        else{
            tile_pointer = tile_y * tilemap_W + tile_x;
            byte_tile_x = tile_x;
        }

        if(tile_y_r){
            ++y_tile_num;
        }

        byte_tile_x = byte_tile_x * x_div;
        while(y_tile_num){
            --y_tile_num;
            byte_tile_y = (tile_y + 3 + y_tile_num)*y_div;
            sys_ren_set_tile( tilemap_start[tile_pointer+y_tile_num*tilemap_W], byte_tile_x, byte_tile_y);
        }
    }
    //redibujado de tiles
    if(e->vy){
        u8 x_tile_num = tile_w;
        u8 byte_tile_x;
        u8 byte_tile_y;
        
        if(e->vy<0){
            if(tile_y_r){
                tile_pointer =  bot_tile * tilemap_W + tile_x;
                byte_tile_y = bot_tile;
            }
            else{
                tile_pointer = (bot_tile-1) * tilemap_W + tile_x;
                byte_tile_y = bot_tile-1;
            }
        }
        else{
            tile_pointer = tile_y * tilemap_W + tile_x;
            byte_tile_y = tile_y;
        }

        if(tile_x_r){
            ++x_tile_num;
        }
        byte_tile_y = (byte_tile_y + 3) * y_div;
        while(x_tile_num){
            --x_tile_num;
            byte_tile_x = (tile_x + x_tile_num)*x_div;
            sys_ren_set_tile( tilemap_start[tile_pointer+x_tile_num], byte_tile_x, byte_tile_y);
        }
    }

    e->x += e->vx;
    e->y += e->vy;
}

void sys_phy_update(){
    man_ent_forall_type(sys_phy_one, e_t_physics);
}