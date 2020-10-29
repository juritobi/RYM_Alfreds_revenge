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


u16 get_tp_x(u8 x, u8 y){
    return y * tilemap_W + x;
}
u16 get_tp_y(u8 y, u8 x){
    return y * tilemap_W + x;
}
u8 get_tile_type(u8 l, u8 st, u8 var, u16(*get_tile_pointer)(u8 first, u8 second)){
    u8 actual = 0x0F;
    u8 most_relevant = 0x0F;
    while(l){
        --l;
        actual = tilemap_start[get_tile_pointer(st, var+l)];
        if(actual < most_relevant){
            most_relevant = actual;
        }
    }
    return most_relevant;
}

void sys_col_x_actions(ent_t* e, u8 tile_type, i8 remaining_movement){
    if(      tile_type < solid) e->vx = remaining_movement;
    else if( tile_type < half ){}
    else if( tile_type < spikes){
        e->vx = remaining_movement;
        man_ent_hit(e,1);
    }
}
void sys_col_y_actions(ent_t* e, u8 tile_type, i8 remaining_movement){
    if(tile_type < solid){
        if(e->vy>0){
            e->on_ground = 1;
        }
        e->vy = remaining_movement;
    }
    else if(tile_type < half){
        if(e->on_ground != 2){
            e->on_ground = 1;
            e->vy = remaining_movement;
        }
    }
    else if(tile_type < spikes){
        if(e->vy>0){
            e->on_ground = 1;
        }
        e->vy = remaining_movement;
        man_ent_hit(e, 1);
    }
}
void sys_col_diag_actions(ent_t* e, u8 tile_type){
    if(tile_type < solid){
        e->vx = 0;
    }
}

u8 sys_col_get_next_tile(u8* p, u8 l, u8 r, i8* v){//returns next tile
    u8 to_collide = r;
    if(*v>0){
        *p = *p + l;
        if(r){
            ++*p;
        }
        *v = -*v;
    }
    else if(*v<0){
        *p = *p -1;
        to_collide = -to_collide;
    }
    return to_collide;
}

void sys_col_one(ent_t* e){
    u8 x = e->tile_x;
    u8 moded_x =x;
    u8 y = e->tile_y;
    u8 moded_y =y;
    u8 rx = e->tile_x_r;
    u8 ry = e->tile_y_r;
    u8 w = e->tile_w;
    u8 h = e->tile_h;//modded
    i8 vx = e->vx;//modded
    i8 vy = e->vy;

    i8 to_collide = 0;
    u8 tile_type = 0;

    if(vx){
        to_collide = sys_col_get_next_tile(&moded_x, w, rx, &vx);
        if(ry) ++h;
        if(rx + vx < 0){
            tile_type = get_tile_type(h, moded_x, y, get_tp_x);
            sys_col_x_actions(e, tile_type, to_collide);
        }
    }
    h = e->tile_h;//modded
    to_collide = 0;
    if(vy){
        to_collide = sys_col_get_next_tile(&moded_y, h, ry, &vy);
        if(rx) ++w;
        if(ry + vy < 0){
            tile_type = get_tile_type(w, moded_y, x, get_tp_y);
            sys_col_y_actions(e, tile_type, to_collide);
        }
    }
    
    if(e->vx && e->vy && !rx && !ry){
        tile_type = get_tile_type(1, moded_x, moded_y, get_tp_x);
        sys_col_diag_actions(e, tile_type);
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
}