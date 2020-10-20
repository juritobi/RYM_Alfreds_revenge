#include "AI.h"

#define rate_of_fire 100
#define move_rate 4
u8 shoot_timer;
u8 move_counter;


const attack_t move = {
    10,
    att_move
};
const attack_t horizontal = {
    10,
    att_hor
};



u8 boss_timer;
u8 boss_attack_timer;
u8 boss_inter_attack_time;
attack_t* attacks[2];
attack_t* attack;

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
        boss_timer= attacks[rand]->total_time;
        attack = attacks[rand];
    }
    attack->funct();// attack_function();
    boss_timer--;
}
void att_move(){
    ent_t* player = man_ent_get_char();
    player->x=4;
}
void att_hor(){
    ent_t* player = man_ent_get_char();
    player->x=60;
}


void sys_AI_one(ent_t* e){
    e->act(e);
}

void sys_AI_init(){
    shoot_timer=rate_of_fire;
    move_counter = 0;

    boss_inter_attack_time = 100;
    boss_attack_timer = 0;
    boss_timer = boss_inter_attack_time;

    attacks[0] = &move;
    attacks[1] = &horizontal;
    attack = attacks[0];

}
void sys_AI_update(){
    man_ent_forall_type(sys_AI_one, e_t_AI);
}