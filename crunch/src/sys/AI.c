#include "AI.h"

#define rate_of_fire 100
#define move_rate 4
u8 shoot_timer;
u8 move_counter;


const attack_t move = {
    20,
    att_move
};
const attack_t horizontal = {
    20,
    att_hor
};
const attack_t none = {
    20,
    att_none
};



u8 boss_timer;
u8 boss_attack_timer;
u8 boss_inter_attack_time;
u8 boss_attack_index;
attack_t const *  attacks[2];
attack_t const *  attack;

void sys_AI_shoot(ent_t* e){
    e->Ai_counter--;
    if(e->Ai_counter == 0){
        e->Ai_counter = rate_of_fire;
        man_ent_resurrect(e, 1);
    }
}
void sys_AI_zombi(ent_t* e){
    
    if(e->Ai_counter == 0 && e->vx == 0){
        if(e->prev_vx == -1)
            e->prev_vx = 1;
        else 
            e->prev_vx = -1;
    }
    e->vy = 4;
    e->vx = 0;
    e->Ai_counter++;
    if(e->Ai_counter == move_rate){
        e->Ai_counter = 0;
        e->vx = e->prev_vx;
    }
}

void sys_AI_ghost(ent_t* e){
    
    if(e->x < man_ent_get_char()->x){
        e->prev_vx = 1;
    }
    else if (e->x > man_ent_get_char()->x){
        e->prev_vx = -1;
    }
    else{
        e->prev_vx = 0;
    }

    if(e->y < man_ent_get_char()->y){
        e->prev_vy = 4;
    }
    else if (e->y > man_ent_get_char()->y){
        e->prev_vy = -4;
    }
    else{
        e->prev_vy = 0;
    }
    e->vy = 0;
    e->vx = 0;
    e->Ai_counter++;
    if(e->Ai_counter == move_rate){
        e->Ai_counter = 0;
        e->vx = e->prev_vx;
        e->vy = e->prev_vy;
    }

}

void sys_AI_sonic(ent_t* e){
    if(e->Ai_counter == 0 && e->vx == 0){
        if(e->prev_vx == -1)
            e->prev_vx = 1;
        else 
            e->prev_vx = -1;
    }
    e->vy = 4;
    e->vx = 0;
    e->Ai_counter++;
    if(e->Ai_counter%move_rate == 0 || e->Ai_counter > 28){
        e->vx = e->prev_vx;

        if(e->Ai_counter == 20 || e->Ai_counter == 24){
            e->vx = 0;
        }

        else if(e->Ai_counter > 28 && e->Ai_counter < 36){
            e->action |= 1;
        }

        else if (e->Ai_counter == 36){
            e->Ai_counter = 0;
        }

    }
}

void sys_AI_boss(ent_t* e){

    if(!boss_timer){
        ent_t* player = man_ent_get_char();
        u8 rand = cpct_getRandom_lcg_u8(player->x);
        rand = rand%2;
        if(rand==boss_attack_index){
            if(rand==0) rand++;
            else rand--;
        }
        boss_attack_index = rand;
        boss_attack_timer = attacks[rand]->total_time;
        boss_timer = boss_inter_attack_time;
        attack = attacks[rand];
    }
    boss_timer--;
    attack->funct(e);// attack_function();
}
void att_move(ent_t* e){
    e->vx = 0;
    if(boss_attack_timer>10){
        e->action |= 0x01;
    }
    else{
        if(boss_attack_timer==10){
            e->vx = 8;
        }
        else if(boss_attack_timer==8){
            e->vx = -8;
        }
        else if(boss_attack_timer==7){
            e->vx = -8;
        }
        else if(boss_attack_timer==5){
            e->vx = 8;
        }
        else if(boss_attack_timer==0){
            attack = &none;
        }
    }

    boss_attack_timer--;
}
void att_none(ent_t* e){
    ent_t* en = e;
}

void att_hor(ent_t* e){
    ent_t* player = man_ent_get_char();

    if(boss_attack_timer==attack->total_time){// si no le voy a dar cambio de ataque
        if(player->y+player->h <= e->y  ||  player->y >= e->y+e->h){
            boss_timer = 0;
        }
        boss_attack_timer--;
        return;
    }

    if(boss_attack_timer==attack->total_time-1){//set entities to hit
        u8 i = 3;
        u8 xpos;
        if(player->x < 40){
            xpos = -(e + i)->w;
        }
        else{
            xpos = e->w;
        }
        while(i){
            (e + i)->originalx = xpos;
            i--;
        }
    }

    if(boss_attack_timer>10){
        e->action |= 0x01;
    }
    else{
        if(boss_attack_timer == 10){
            man_ent_resurrect(e, 1);
        }
        else if(boss_attack_timer == 9){
            man_ent_resurrect(e, 2);
        }
        else if(boss_attack_timer == 8){
            man_ent_resurrect(e, 3);
        }
        else if(boss_attack_timer==0){
            attack = &none;
        }
    }
    boss_attack_timer--;
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
    boss_attack_index = 0xFF;

    attacks[0] = &move;
    attacks[1] = &horizontal;
    attack = &none;

}
void sys_AI_update(){
    man_ent_forall_type(sys_AI_one, e_t_AI);
}