#include "AI.h"

#define rate_of_fire 40
#define zombi_rate 15
#define ghost_rate 3
#define dasher_rate 4
#define move_rate 5

const attack_t horizontal = {
    30,
    att_hor
};
const attack_t rain = {
    40,
    att_rain
};
const attack_t pilar = {
    30,
    att_pilar
};
const attack_t none = {
    20,
    att_none
};



u8 boss_timer;
u8 boss_attack_timer;
u8 boss_inter_attack_time;
u8 boss_attack_index;
attack_t const *  attacks[3];
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
        if(e->prev_vx <0 ){
            e->prev_vx = 2;
            e->move_dir = dir_right;
        }
        else {
            e->prev_vx = -2;
            e->move_dir = dir_left;
        }
    }
    e->vy = 4;
    e->vx = 0;
    e->Ai_counter++;
    if(e->Ai_counter == zombi_rate){
        e->Ai_counter = 0;
        e->vx = e->prev_vx;
    }
}

void sys_AI_ghost(ent_t* e){
    
    e->vy = 0;
    e->vx = 0;
    if(e->Ai_counter == 0){
        if(e->x!=player->x){
            if(e->x < player->x){
                e->vx = 1;
                e->move_dir = dir_right;
            }
            else{
                e->vx = -1;
                e->move_dir = dir_left;
            }
        }
        if(e->y!=player->y){
            if(e->y < player->y){
                e->vy = 4;
            }
            else{
                e->vy = -4;
            }
        }
        e->Ai_counter = ghost_rate;
    }
    e->Ai_counter--;
}

void sys_AI_sonic(ent_t* e){
    e->vy = 4;
    e->vx = 0;
    e->Ai_counter--;
    if(!e->Ai_counter){
        if(e->vx){
            e->vx = e->prev_vx;
            e->action |= 1
        }
        else if(e->prev_vx){
            e->prev_vx = 0;
        }
        else if(!(player->y+player->h <= e->y  ||  player->y >= e->y+e->h) ){
            e->action |= 2;
            e->prev_vy = 1;
        }
        if(e->prev_y){
            if(e->x > player->x){
                e->vx = -1;
                e->perv_vx = -1;
                e->move_dir = dir_left;
            }
            else{
                e->vx = 1;
                e->perv_vx = 1;
                e->move_dir = dir_right;
            }
            e->action |= 1;
            e->prev_vy = 0;
        }
    }
}

void sys_AI_boss(ent_t* e){

    if(!boss_timer){
        u8 rand = cpct_getRandom_lcg_u8(player->x);
        rand = rand%4;
        if(rand==boss_attack_index){
            if(rand==0) rand++;
            else rand--;
        }
        boss_attack_index = rand;
        boss_attack_timer = attacks[rand]->total_time;
        boss_timer = boss_inter_attack_time;
        attack = attacks[rand];
    }
//going tio use original x careful for breaks
    e->vy = 0;
    e->vx = 0;
    e->Ai_counter--;
    if(!e->Ai_counter){
        e->Ai_counter = move_rate;
        if(e->x == 32 && e->y == 72){
            e->originalvx = 1;
            e->originalvy = 0;
        }
        else if(e->x == 36 && e->y == 72){
            e->originalvx = 1;
            e->originalvy = 4;
        }
        else if(e->x == 40 && e->y == 88){
            e->originalvx = -1;
            e->originalvy = 4;
        }
        else if(e->x == 36 && e->y == 104){
            e->originalvx = -1;
            e->originalvy = 0;
        }
        else if(e->x == 32 && e->y == 104){
            e->originalvx = -1;
            e->originalvy = -4;
        }
        else if(e->x == 28 && e->y == 88){
            e->originalvx = 1;
            e->originalvy = -4;
        }
        e->vx = e->originalvx;
        e->vy = e->originalvy;
    }

    boss_timer--;
    attack->funct(e);// attack_function();
}
void att_none(ent_t* e){
    ent_t* en = e;
}

void att_hor(ent_t* e){
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

        else if(boss_attack_timer==3){
            (e+1)->death(e+1);
        }
        else if(boss_attack_timer==2){
            (e+2)->death(e+2);
        }
        else if(boss_attack_timer==1){
            (e+3)->death(e+3);
        }

        else if(boss_attack_timer==0){
            attack = &none;
        }
    }
    boss_attack_timer--;
}

void att_rain(ent_t* e){

    if(boss_attack_timer==attack->total_time-1){//set entities to hit
        u8 i = 6;
        u8 xpos = player->x%3;
        xpos = xpos*4 + 4;
        while(i){
            (e + 3 + i)->originaly = 24;
            (e + 3 + i)->originalx = xpos;
            (e + 3 + i)->originalvy = 8;
            xpos+=12;
            i--;
        }
    }
    e->action |= 0x01;
    if(boss_attack_timer==28){
        man_ent_res_absolute(e, 3+1);
    }
    if(boss_attack_timer==27){
        man_ent_res_absolute(e, 3+2);
    }
    if(boss_attack_timer==26){
        man_ent_res_absolute(e, 3+3);
    }
    if(boss_attack_timer==25){
        man_ent_res_absolute(e, 3+4);
    }
    if(boss_attack_timer==24){
        man_ent_res_absolute(e, 3+5);
    }
    if(boss_attack_timer==23){
        man_ent_res_absolute(e, 3+6);
    }

    else if(boss_attack_timer==7){
        (e+3+1)->death(e+3+1);
    }
    else if(boss_attack_timer==6){
        (e+3+2)->death(e+3+2);
    }
    else if(boss_attack_timer==5){
        (e+3+3)->death(e+3+3);
    }
    else if(boss_attack_timer==4){
        (e+3+4)->death(e+3+4);
    }
    else if(boss_attack_timer==3){
        (e+3+5)->death(e+3+5);
    }
    else if(boss_attack_timer==2){
        (e+3+6)->death(e+3+6);
    }
    else if(boss_attack_timer==0){
        attack = &none;
    }

    boss_attack_timer--;
}

void att_pilar(ent_t* e){

    if(boss_attack_timer==attack->total_time-1){//set entities to hit
        (e + 3 + 6 + 1)->originalx = player->x - 4;  
    }
    if(boss_attack_timer>6){
        e->action |= 0x01;
    }
    else if(boss_attack_timer==6){
        man_ent_res_absolute(e, 3+6+1);
    }
    else if(boss_attack_timer==1){
        (e+3+6+1)->death(e+3+6+1);
    }
    else if(boss_attack_timer==0){
        attack = &none;
    }

    boss_attack_timer--;
}

void sys_AI_one(ent_t* e){
    e->act(e);
}

void sys_AI_init(){

    boss_inter_attack_time = 100;
    boss_attack_timer = 0;
    boss_timer = boss_inter_attack_time;
    boss_attack_index = 0xFF;

    attacks[0] = &horizontal;
    attacks[1] = &rain;
    attacks[2] = &pilar;
    attack = &none;

}
void sys_AI_update(){
    man_ent_forall_type(sys_AI_one, e_t_AI);
}