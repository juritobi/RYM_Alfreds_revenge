#include "physics.h"
#include <man/man_ent.h>

#define att_move_id 0
#define att_move_num 0
#define att_hor_id 1
#define att_hor_num 3
typedef void (*Ptrf_v_v)();

#define rate_of_fire 100
#define move_rate 4
u8 shoot_timer;
u8 move_counter;

u8 boss_timer;
u8 boss_inter_attack_time;
u8 (*attacks[2])();//array de punteros a funcion
u8 attack_function;//indece a array de punteros a funcion

void sys_AI_shoot(ent_t* e){
    shoot_timer--;
    if(shoot_timer == 0){
        shoot_timer = rate_of_fire;
        man_ent_resurrect(e, 1);
    }
}
void sys_AI_zombi(ent_t* e){
    
    if(move_counter == 0 && e->vx == 0){
        if(e->prev_vx == -1)
            e->prev_vx = 1;
        else 
            e->prev_vx = -1;
    }
    e->vy = 4;
    e->vx = 0;
    move_counter++;
    if(move_counter == move_rate){
        move_counter = 0;
        e->vx = e->prev_vx;
    }
}

void sys_AI_boss(ent_t* e){

    if(!boss_timer){
        ent_t* player = man_ent_get_char();
        u8 rand = cpct_getRandom_lcg_u8(player->x);
        rand = (rand%2);
        boss_timer= 100;
        attack_function = (*attacks[rand])();
    }else{
        attack_function = (*attacks[attack_function])();
    }
    boss_timer--;
}
u8 att_move(){
    ent_t* player = man_ent_get_char();
    player->x=4;
    return 0;
}
u8 att_hor(){
    ent_t* player = man_ent_get_char();
    player->x=60;
    return 1;
}


void sys_AI_one(ent_t* e){
    e->act(e);
}

void sys_AI_init(){
    shoot_timer=rate_of_fire;
    move_counter = 0;

    boss_inter_attack_time = 100;
    boss_timer = boss_inter_attack_time;
    attack_function = 0x00;

    attacks[0] = att_move;
    attacks[1] = att_hor;

}
void sys_AI_update(){
    man_ent_forall_type(sys_AI_one, e_t_AI);
}