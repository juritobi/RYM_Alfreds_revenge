#include "physics.h"
#include <man/man_ent.h>
#include <man/man_game.h>
#include <man/level.h>
#include <sys/render.h>
#include <sys/input.h>
#include <constants.h>

const i8 knocknackX[] = {  1,  1, 1, 1, 1,1,1,1};
const i8 knocknackY[] = { -8, -8, -8, 0, 0, 8 ,8, 8};
u8* tilemap;

#define x_div 4
#define y_div 8

#define solid 0x08
#define half  0x0a
#define spikes 0x0c


u16 get_tile_pointer(u8 x, u8 y){
    return y * tilemap_W + x;
}

u8 get_tile_type(u8 width, u8 height, u16 tile_pointer){

    u8 actual = 0x0F;
    u8 most_relevant = 0x0F;

    while(width){
        --width;
        actual = tilemap[tile_pointer+width] ;
        if(actual < most_relevant){
            most_relevant = actual;
        }
    }

    while(height){
        --height;
        actual = tilemap[tile_pointer+height*tilemap_W ];
        if(actual < most_relevant){
            most_relevant = actual;
        }
    }

    return most_relevant;
}


void sys_col_one(ent_t* e){
    u8 tile_x = e->x/x_div;
    u8 tile_y = e->y/y_div - 3;// -3 para por que el hud son 3 tiles
    u8 tile_w = e->w/x_div;
    u8 tile_h = e->h/y_div;
    u8 not_exact_tile_x = e->x%x_div;
    u8 not_exact_tile_y = e->y%y_div;

    u8 right_tile;
    u8 left_tile;
    u8 bot_tile;
    u8 top_tile; 
    u16 tile_pointer;

    right_tile = tile_x + tile_w;
    left_tile = tile_x - 1;
    bot_tile = tile_y + tile_h;
    top_tile = tile_y - 1; 

    if(e->vx){
        if(!not_exact_tile_x){
            u8 height = tile_h;
            u8 tile_type;
            if(not_exact_tile_y){
                ++height;
            }

            if(e->vx > 0){
                tile_pointer = get_tile_pointer(right_tile, tile_y);
            }
            else{
                tile_pointer = get_tile_pointer(left_tile, tile_y);
            }
            
            tile_type = get_tile_type(0, height, tile_pointer);

            if(      tile_type < solid) e->vx = 0;
            else if( tile_type < half ){}
            else if( tile_type < spikes){
                e->vx = 0;
                man_ent_hit(e,1);
            }
        }
    }
    if(e->vy){
        if(!not_exact_tile_y){
            u8 hit_taken=0;
            u8 width = tile_w;
            u8 tile_type;
            if(not_exact_tile_x){
                ++width;
            }

            if(e->vy>0){
                tile_pointer = get_tile_pointer(tile_x, bot_tile);
            }
            else{
                tile_pointer = get_tile_pointer(tile_x, top_tile);
            }
            
            tile_type = get_tile_type(width, 0, tile_pointer);

            if(tile_type < solid){
                if(e->vy>0){
                    e->on_ground = 1;
                }
                e->vy = 0;
            }
            else if(tile_type < half){
                if(!e->on_ground){
                    e->on_ground = 1;
                    e->vy = 0;
                }
            }
            else if(tile_type < spikes){
                e->vy = 0;
                man_ent_hit(e, 1);
            }
        }
    }


     if(e->vx && e->vy){
        if(!not_exact_tile_x && !not_exact_tile_y){
            u8 x_wins = 0;
            u8 tile_type;
            if(e->vx > 0 && e->vy < 0){
                tile_pointer = get_tile_pointer(right_tile, top_tile);
            }
            else if(e->vx > 0 && e->vy > 0){
                tile_pointer = get_tile_pointer(right_tile, bot_tile);
                x_wins = 1;
            }
            else if(e->vx < 0 && e->vy > 0){
                tile_pointer = get_tile_pointer(left_tile, bot_tile);
                x_wins = 1;
            }
            else{
                tile_pointer = get_tile_pointer(left_tile, top_tile);
            }

            tile_type = tilemap[tile_pointer];
            if(tile_type < solid){
                if(x_wins){
                    e->vy = 0;
                    e->on_ground = 1;
                }
                else{
                    e->vx = 0;
                }
            }
            else if(tile_type < half){
                if(!e->on_ground){
                    e->on_ground = 1;
                    e->vy = 0;
                }
            }
        }
    }

}

void sys_col_ally_enemy(ent_t* ally, ent_t* enemy){
    if( !(ally->x+ally->w <= enemy->x  ||  ally->x >= enemy->x+enemy->w) ){
        if(!(ally->y+ally->h <= enemy->y  ||  ally->y >= enemy->y+enemy->h) ) {
            man_ent_hit(ally, enemy->damage);
            if(ally->prevx < enemy->prevx){
                ally->dir = -1;
            }
            else{
                ally->dir = 1;
            }
        }
    }

}
void sys_col_allybreaker_enemy(ent_t* breaker, ent_t* enemy){
    if( !(breaker->x+breaker->w <= enemy->x  ||  breaker->x >= enemy->x+enemy->w) ){
        if(!(breaker->y+breaker->h <= enemy->y  ||  breaker->y >= enemy->y+enemy->h) ) {
            man_ent_hit(enemy, breaker->damage);
            if(enemy->prevx < breaker->prevx){
                enemy->dir = -1;
            }
            else{
                enemy->dir = 1;
            }
        }
    }
}

void sys_col_ally_PowerUp(ent_t* ally, ent_t* PowerUp){
    if( !(ally->x+ally->w <= PowerUp->x  ||  ally->x >= PowerUp->x+PowerUp->w) ){
        if(!(ally->y+ally->h <= PowerUp->y  ||  ally->y >= PowerUp->y+PowerUp->h) ) {
            if(PowerUp->mp == 1){
                man_ent_max_hp(ally);
            }
            else if(PowerUp->mp == 2){
                man_ent_max_mana(ally);
            }
            else if(PowerUp->mp == 3){
                man_ent_max_melee(ally+1);
            }
            else if(PowerUp->mp == 4){
                man_ent_max_range(ally+2);
            }

            PowerUp->death(PowerUp);

        }
    }
}

void sys_col_reduceTimeInvulnerable(ent_t* e){
    i8 dire = e->dir;
    if(e->knockback > -1 && e->knockback < sizeof(knocknackX)){ 
        e->vx = knocknackX[e->knockback]*dire;
        e->vy = knocknackY[e->knockback];
        e->knockback++;
        e->on_ground = 2;//esto es pa que atraviese los bloques semi-solidos
    }
    if(e->knockback == sizeof(knocknackX)){
        e->knockback = -1;
        e->on_ground = 0;
    }
}

void sys_col_update(){
    man_ent_forall_col_type(sys_col_ally_PowerUp, col_t_ally, col_t_powerUp);
    man_ent_forall_col_type(sys_col_allybreaker_enemy, col_t_ally_breaker, col_t_enemy);
    man_ent_forall_col_type(sys_col_ally_enemy, col_t_ally, col_t_enemy|col_t_enemy_breaker);
    man_ent_forall_col_type_individual(sys_col_reduceTimeInvulnerable, col_t_ally|col_t_enemy);//puede que se pueda hacer con componente de fisica
    man_ent_forall_type(sys_col_one, e_t_col); //colisiones con tiles
    
}

void sys_col_init(){
    tilemap = man_level_get_tilemap();
}