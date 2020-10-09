#include "input.h"
#include <man/man_ent.h>

const i8 jumptable[] = {-2, -2, -2, -2, -2, 0, 0};

void sys_input_one(ent_t* ent){
    if (ent->type & e_t_input)
    {
        ent->vx = 0;
        ent->vy = 8;


        if(cpct_isKeyPressed(Key_D)){
            if(ent->x < 76){
                ent->vx = 1;
            }
        }

        else if(cpct_isKeyPressed(Key_A)){
            if(ent->x > 0){
                ent->vx = -1;
            }
        }
        
        if(cpct_isKeyPressed(Key_W) && ent->on_ground && ent->jumping == -1){
            ent->jumping = 0;
        }
        if(ent->jumping != -1){
            ent->vy = jumptable[ent->jumping]*4;
            if(ent->jumping < sizeof(jumptable)-1)
                ent->jumping++;
            else
                ent->jumping = -1;
        }
    }
}

void sys_input_update(){
    man_ent_forall_type(sys_input_one, e_t_input);
}