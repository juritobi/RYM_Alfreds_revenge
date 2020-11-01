#include "physics.h"
#include <man/man_ent.h>
#include <man/man_game.h>
#include <man/level.h>
#include <sys/render.h>
#include <sys/input.h>
#include <constants.h>
#include <sys/UI>

const i8 knocknackX[] = {  1,  1, 1, 1, 1,1,1,1};
const i8 knocknackY[] = { -8, -8, -8, 0, 0, 8 ,8, 8};

ent_t * col_breaker[8];
u8 col_breaker_next;

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



void sys_col_reduceTimeInvulnerable(ent_t* e){
    i8 dire = e->dir;
    if(e->knockback > -1 && e->knockback < sizeof(knocknackX)){ 
        e->vx = knocknackX[e->knockback]*dire;
        e->vy = knocknackY[e->knockback];
        if(e->vy + e->y < 24){
            e->vy = 0;
        }
        e->knockback++;
        e->on_ground = 2;//esto es pa que atraviese los bloques semi-solidos
    }
    if(e->knockback == sizeof(knocknackX)){
        e->knockback = -1;
        e->on_ground = 1;
    }

    if(e->invulnerable&0x7f > 0){
        e->invulnerable ^= 0x80;
        e->invulnerable--;
    }
}

void sys_col_a_e(ent_t* e1, ent_t* e2){
    man_ent_hit(e1, e2->damage);
    if(e1->x < e2->x) e1->dir = -1;
    else e1->dir = 1;
}
void sys_col_p_pu(ent_t* p, ent_t* pu){
    if(pu->mp == 1){
        man_ent_max_hp(p);
    }
    else if(pu->mp == 2){
        man_ent_max_mana(p);
    }
    else if(pu->mp == 3){
        man_ent_max_melee(p+1);
    }
    else if(pu->mp == 4){
        man_ent_max_range(p+2);
    }
    score+=250;
    score_draw = 1;
    pu->death(pu);
}

void sys_col_e_s(ent_t* e1, ent_t* e2){//la segunda es la espada
    man_ent_hit(e1, e2->damage);
    if(e1->x < player->x) e1->dir = -1;
    else e1->dir = 1;
}
void sys_col_e_k(ent_t* e1, ent_t* e2){//la segunda es el cuchillo
    sys_col_a_e(e1, e2);
    e2->death(e2);
}

void sys_col_check(ent_t* e1, ent_t* e2, void(*fun)(ent_t*, ent_t*) ){
    if( !(e1->x+e1->w <= e2->x  ||  e1->x >= e2->x+e2->w) ){
        if(!(e1->y+e1->h <= e2->y  ||  e1->y >= e2->y+e2->h) ) {
            fun(e1,e2);
        }
    }
}

void man_col_player(ent_t* e1, ent_t* e2){
    if(e2->col_type & (col_t_enemy|col_t_enemy_breaker)){
        col_breaker[col_breaker_next] = e2;
        ++col_breaker_next;
        sys_col_check(e1,e2,sys_col_a_e);
    }
    else{
        sys_col_check(e1,e2,sys_col_p_pu);
    }
}

void sys_col_update(){

    man_ent_do_for_all(man_col_player);
    if(!((player+1)->type & e_t_dead )){
        u8 l =  col_breaker_next;
        while(l){
            --l;
            sys_col_check(col_breaker[l], player+1, sys_col_e_s);
        }
    }
    if(!((player+2)->type & e_t_dead) ){
        u8 l =  col_breaker_next;
        while(l){
            --l;
            sys_col_check(col_breaker[l], player+2, sys_col_e_k);
        }
    }
    col_breaker_next = 0;
    man_ent_forall_col_type_individual(sys_col_reduceTimeInvulnerable, col_t_ally|col_t_enemy);//puede que se pueda hacer con componente de fisica
    man_ent_forall_type(sys_col_one, e_t_col); //colisiones con tiles
    
}

void sys_col_init(){
    col_breaker_next = 0;
}