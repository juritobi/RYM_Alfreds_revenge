#include "physics.h"
#include <man/man_ent.h>
#include <man/man_game.h>
#include <man/level.h>
#include <constants.h>


void sys_col_one(ent_t* e){
    u8* tilemap = man_level_get_tilemap();
    u8 tile_x = e->x/4;
    u8 tile_y = e->y/8;
    u8 next_tile = tile_x + e->vx;
    u8 up_tile = tile_y - 1;
    u8 down_tile = tile_y + 3;
    
    u16 array_pos= tile_y*tilemap_W + next_tile;
    if(tile_x != (e->x-1)/4){//si voy a cambiar de tile
        if(tilemap[array_pos] !=3 || tilemap[array_pos + tilemap_W] !=3 || tilemap[array_pos + tilemap_W +tilemap_W] !=3){
            e->vx = 0;
        }
    }

    array_pos = up_tile*tilemap_W + tile_x;
    if(tile_y != (e->y-1)/8){//si voy a cambiar de tile
        if(e->vy<0){
            if(tilemap[array_pos] !=3 || (!(tile_x != (e->x-1)/4) && tilemap[array_pos+ 1] !=3 )){
                e->vy = 0;
            }
        }
        else{
            array_pos = down_tile*tilemap_W + tile_x;
            if(tilemap[array_pos] !=3 || (!(tile_x != (e->x-1)/4) && tilemap[array_pos+ 1] !=3 )){
                e->on_ground = 1;
            }
            else{
                e->on_ground = 0;
            }

            if(e->on_ground && e->vy>0){
                e->vy=0;
            }
        }
    }
}

void sys_col_ally_enemy(ent_t* ally, ent_t* enemy){
    if( !(ally->x+ally->w < enemy->x  ||  ally->x > enemy->x+enemy->w) ){
        if(!(ally->y+ally->h < enemy->y  ||  ally->y > enemy->y+enemy->y) ) {
            man_ent_setdead(ally);
        }
    }
}

void sys_col_update(){
    man_ent_forall_type(sys_col_one, e_t_col); //colisiones con tiles
    man_ent_forall_col_type(sys_col_ally_enemy, col_t_ally, col_t_enemy|col_t_enemy_breaker);
}

/*
casos:

saltamos debajo de un bloque blanco -> no poder saltar directamente
saltar pero en medio del salto haya un bloque blanco -> cancelar el salto y caer al suelo
saltar y caer en una plataforma -> cancelar el salto y caer en la plataforma SIN QUEDARSE DENTRO DE ELLA POR FAVOR
saltar de una plataforma al suelo -> acabar el salto y caer hasta el suelo
andar fuera de una plataforma -> caer hasta el
*/