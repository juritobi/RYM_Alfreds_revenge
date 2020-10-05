#include "input.h"
#include <man/man_ent.h>

const i8 jumptable[10] = {-3, -2, -1, -1 -1, 0, 1, 2, 2, 3};

void sys_input_one(ent_t* ent){
    if (ent->type & e_t_input)
    {
        cpct_scanKeyboard_f();
        
        ent->vx = 0;
        ent->vy = 0;


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

        if(ent->jumping != -1){
            if(ent->jumping < 9){
                ent->jumping++;
                ent->vy = jumptable[ent->jumping]*4;
            }
            else{
                ent->jumping= -1;
            }
        }

        else if(cpct_isKeyPressed(Key_W) && ent->jumping == -1){
            ent->jumping++;
            ent->vy = jumptable[ent->jumping]*4;
        }

    }
}

void sys_input_update(){
    man_ent_forall_type(sys_input_one, e_t_input);
}