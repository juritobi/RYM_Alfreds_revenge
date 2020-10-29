#include "physics.h"
#include <man/man_ent.h>
#include <man/man_game.h>
#include <man/level.h>
#include <sys/render.h>
#include <sys/input.h>
#include <constants.h>

const i8 knocknackX[] = {  1,  1, 1, 1, 1,1,1,1};
const i8 knocknackY[] = { -8, -8, -8, 0, 0, 8 ,8, 8};

#define solid 0x06
#define half  0x08
#define spikes 0x0c


u16 get_tile_pointer(u8 x, u8 y){
    return y * tilemap_W + x;
}

u8 get_tile_type(u8 width, u8 height, u16 tile_pointer){

    u8 actual = 0x0F;
    u8 most_relevant = 0x0F;

    while(width){
        --width;
        actual = tilemap_start[tile_pointer+width] ;
        if(actual < most_relevant){
            most_relevant = actual;
        }
    }

    while(height){
        --height;
        actual = tilemap_start[tile_pointer+height*tilemap_W ];
        if(actual < most_relevant){
            most_relevant = actual;
        }
    }

    return most_relevant;
}
void sys_col_x_actions(ent_t* e, u8 tile_type, u8 tile_x_r){
    if(      tile_type < solid) e->vx = tile_x_r;
    else if( tile_type < half ){}
    else if( tile_type < spikes){
        e->vx = tile_x_r;
        man_ent_hit(e,1);
    }
}
void sys_col_y_actions(ent_t* e, u8 tile_type, u8 tile_y_r){
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
        if(e->vy>0){
            e->on_ground = 1;
        }
        e->vy = 0;
        man_ent_hit(e, 1);
    }
}


void sys_col_one(ent_t* e){
    u8 tile_x = e->tile_x;
    u8 tile_y = e->tile_y;
    u8 tile_x_r = e->tile_x_r;
    u8 tile_y_r = e->tile_y_r;
    u8 tile_w = e->tile_w;
    u8 tile_h = e->tile_h;
    
    u8 right_tile;
    u8 left_tile;
    u8 bot_tile;
    u8 top_tile; 
    u16 tile_pointer;

    u8 changed_x = 0;
    u8 changed_y = 0;

    right_tile = tile_x + tile_w;
    if(tile_x_r) ++right_tile;
    left_tile = tile_x - 1;

    bot_tile = tile_y + tile_h;
    if(tile_y_r) ++bot_tile;
    top_tile = tile_y - 1; 

    if(e->vx){
        u8 height = tile_h;
        u8 tile_type;
        if(tile_y_r){
            ++height;
        }

        if(e->vx > 0){
            if( (tile_x_r - e->vx) < 0){
                tile_pointer = get_tile_pointer(right_tile, tile_y);
                tile_type = get_tile_type(0, height, tile_pointer);
                changed_x = 1;
                sys_col_x_actions(e, tile_type, tile_x_r);
            }
        }
        else{
            if( (tile_x_r + e->vx) < 0){
                tile_pointer = get_tile_pointer(left_tile, tile_y);
                tile_type = get_tile_type(0, height, tile_pointer);
                changed_x = 1;
                sys_col_x_actions(e,tile_type, -tile_x_r);
            }
        }
    }
    if(e->vy){
        u8 hit_taken=0;
        u8 width = tile_w;
        u8 tile_type;
        if(tile_x_r){
            ++width;
        }

        if(e->vy>0){
            if( (tile_y_r - e->vy) < 0){
                tile_pointer = get_tile_pointer(tile_x, bot_tile);
                tile_type = get_tile_type(width, 0, tile_pointer);
                changed_y = 1;
                sys_col_y_actions(e,tile_type, tile_pointer);
            }
        }
        else{
            if( (tile_y_r + e->vy) < 0){
                tile_pointer = get_tile_pointer(tile_x, top_tile);
                tile_type = get_tile_type(width, 0, tile_pointer);
                changed_y = 1;
                sys_col_y_actions(e,tile_type, tile_pointer);
            }
        }
    }


    if(e->vx && e->vy){
        if(changed_x && changed_y){
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
            tile_type = tilemap_start[tile_pointer];
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
            if(ally->x < enemy->x){
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
            if(enemy->x < breaker->x){
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
        e->on_ground = 1;
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
}