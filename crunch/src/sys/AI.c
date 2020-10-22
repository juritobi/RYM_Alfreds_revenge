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
const attack_t rain = {
    30,
    att_rain
};
const attack_t pilar = {
    20,
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
        rand = rand%4;
        if(rand==boss_attack_index){
            if(rand==0) rand++;
            else rand--;
        }
        rand = 3;
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
        if(boss_attack_timer<10 && boss_attack_timer>8){
            e->vx = 2;
        }
        else if(boss_attack_timer<8 && boss_attack_timer>4){
            e->vx = -2;
        }
        else if(boss_attack_timer==4){
            e->vx = 2;
        }
        else if(boss_attack_timer==3){
            e->vx = 2;
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
    ent_t* player = man_ent_get_char();

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
    if(boss_attack_timer==attack->total_time-2){
        man_ent_res_absolute(e, 3+1);
    }
    if(boss_attack_timer==attack->total_time-3){
        man_ent_res_absolute(e, 3+2);
    }
    if(boss_attack_timer==attack->total_time-4){
        man_ent_res_absolute(e, 3+3);
    }
    if(boss_attack_timer==attack->total_time-5){
        man_ent_res_absolute(e, 3+4);
    }
    if(boss_attack_timer==attack->total_time-6){
        man_ent_res_absolute(e, 3+5);
    }
    if(boss_attack_timer==attack->total_time-7){
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
    ent_t* player = man_ent_get_char();

    if(boss_attack_timer==attack->total_time-1){//set entities to hit
        (e + 3 + 6 + 1)->originalx = player->x - 4;  
    }
    if(boss_attack_timer>6){
        e->action |= 0x01;
    }
    if(boss_attack_timer==6){
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
    shoot_timer=rate_of_fire;
    move_counter = 0;

    boss_inter_attack_time = 100;
    boss_attack_timer = 0;
    boss_timer = boss_inter_attack_time;
    boss_attack_index = 0xFF;

    attacks[0] = &move;
    attacks[1] = &horizontal;
    attacks[2] = &rain;
    attacks[3] = &pilar;
    attack = &none;

}
void sys_AI_update(){
    man_ent_forall_type(sys_AI_one, e_t_AI);
}