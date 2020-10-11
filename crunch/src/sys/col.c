#include "physics.h"
#include <man/man_ent.h>
#include <man/man_game.h>
#include <man/level.h>
#include <constants.h>


#define x_div 4
#define y_div 8


void sys_col_one(ent_t* e){

    u8* tilemap = man_level_get_tilemap();
    u8 tile_x = e->x/x_div;
    u8 tile_y = e->y/y_div - 3;// -3 para por que el hud son 3 tiles

    u8 right_tile;
    u8 left_tile;
    u8 top_tile;
    u8 bot_tile; 
    u16 tile_pointer;

    if(e->vx){
        if(tile_x != (e->x-1)/x_div){
            u8 counter = 0;
            u8 y_tile_num = e->h/y_div;
            right_tile = tile_x + e->w/x_div;
            left_tile = tile_x - 1;
            
            if(e->vx > 0){
                tile_pointer = tile_y*tilemap_W + right_tile;
            }
            else{
                tile_pointer = tile_y*tilemap_W + left_tile;
            }
            if(tile_y == (e->y-1)/y_div){
                ++y_tile_num;
            }
            
            while(counter!= y_tile_num){
                if(tilemap[tile_pointer+counter*tilemap_W] !=3){
                    e->vx = 0;
                    break;
                }
                ++counter;
            }
        }
    }
    if(e->vy){
        if(tile_y != (e->y-1)/y_div){//si voy a cambiar de tile
            u8 counter = 0;
            u8 x_tile_num = e->w/x_div;
            bot_tile = tile_y + e->h/y_div;
            top_tile = tile_y - 1;
            

            if(e->vy>0){
                tile_pointer = bot_tile*tilemap_W + tile_x;
            }
            else{
                tile_pointer = top_tile*tilemap_W + tile_x;
                
            }
            if(tile_x == (e->x-1)/x_div){
                ++x_tile_num;
            }
            
            while(counter!= x_tile_num){
                if(tilemap[tile_pointer+counter] !=3){
                    if(e->vy>0){
                        e->on_ground = 1;
                    }
                    else{
                        e->on_ground = 0;
                    }
                    e->vy = 0;
                    break;
                }
                ++counter;
            }
        }
    }

    if(e->vx && e->vy){
        if(tile_x != (e->x-1)/x_div && tile_y != (e->y-1)/y_div){
            u8 x_wins = 0;
            if(e->vx > 0 && e->vy < 0){
                tile_pointer = top_tile*tilemap_W + right_tile;
            }
            else if(e->vx > 0 && e->vy > 0){
                tile_pointer = bot_tile*tilemap_W + right_tile;
                x_wins = 1;
            }
            else if(e->vx < 0 && e->vy > 0){
                tile_pointer = bot_tile*tilemap_W + left_tile;
                x_wins = 1;
            }
            else{
                tile_pointer = top_tile*tilemap_W + left_tile;
            }

            if(tilemap[tile_pointer] !=3){
                if(x_wins){
                    e->vy = 0;
                    e->on_ground = 1;
                }
                else{
                    e->vx = 0;
                }
            }
        }
    }
}

void sys_col_ally_enemy(ent_t* ally, ent_t* enemy){
    if(ally->invulnerable == 0){
        if( !(ally->x+ally->w <= enemy->x  ||  ally->x >= enemy->x+enemy->w) ){
            if(!(ally->y+ally->h <= enemy->y  ||  ally->y >= enemy->y+enemy->h) ) {
                //probablemente lo ideal seria haer esto en una funcion man_ent_hit() y comprobar y hacer todo lo que se tenga que hacer ahi ademas nos quitariamos una de estas dos funcions que hacen casi lo mismo
                ally->hp--;
                ally->invulnerable = 50;
            }
        }
    }
}

void sys_col_enemy_ally(ent_t* ally, ent_t* enemy){
    if(enemy->invulnerable == 0){
        if( !(ally->x+ally->w <= enemy->x  ||  ally->x >= enemy->x+enemy->w) ){
            if(!(ally->y+ally->h <= enemy->y  ||  ally->y >= enemy->y+enemy->h) ) {
                //probablemente lo ideal seria haer esto en una funcion man_ent_hit() y comprobar y hacer todo lo que se tenga que hacer ahi ademas nos quitariamos una de estas dos funcions que hacen casi lo mismo
                enemy->hp--;
                enemy->invulnerable = 50;
            }
        }
    }
}

void sys_col_reduceTimeInvulnerable(ent_t* e){
    if(e->invulnerable > 0){
        e->invulnerable--;
    }
}

void sys_col_update(){
    man_ent_forall_type(sys_col_one, e_t_col); //colisiones con tiles
    man_ent_forall_col_type_individual(sys_col_reduceTimeInvulnerable, col_t_ally); //esto tiene que ir en el update del manejdor de entidades y esta malgastando tiempo recorriendo 2 veces el array de entidades
    man_ent_forall_col_type_individual(sys_col_reduceTimeInvulnerable, col_t_enemy);//esto tiene que ir en el update del manejdor de entidades y esta malgastando tiempo recorriendo 2 veces el array de entidades
    man_ent_forall_col_type(sys_col_ally_enemy, col_t_ally, col_t_enemy|col_t_enemy_breaker);
    man_ent_forall_col_type(sys_col_enemy_ally, col_t_ally_breaker, col_t_enemy);
}

/*
casos:

saltamos debajo de un bloque blanco -> no poder saltar directamente
saltar pero en medio del salto haya un bloque blanco -> cancelar el salto y caer al suelo
saltar y caer en una plataforma -> cancelar el salto y caer en la plataforma SIN QUEDARSE DENTRO DE ELLA POR FAVOR
saltar de una plataforma al suelo -> acabar el salto y caer hasta el suelo
andar fuera de una plataforma -> caer hasta el
*/