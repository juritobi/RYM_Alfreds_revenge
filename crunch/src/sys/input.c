#include "input.h"
#include <man/man_ent.h>

<<<<<<< HEAD
const i8 jumptable[] = {-2, -2, -2, -2, 0, 0};
=======
const i8 jumptable[] = {-2, -2, -2, -2, -2, 0,0};
i8 contador_de_mierda = 5;

>>>>>>> 315a3e8b7ddc6e25a95427afff5c992434d57315

void sys_input_one(ent_t* ent){
    if (ent->type & e_t_input)
    {
        cpct_scanKeyboard_f();
        
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
        
        if(cpct_isKeyPressed(Key_W) && ent->jumping == 0){
            ent->jumping = 1;
        }

        if(ent->jumping != -1){
            if(ent->jumping < sizeof(jumptable)){
                ent->jumping++;
                ent->vy = jumptable[ent->jumping]*4;
            }
            else{
                ent->jumping = -1;
            }

        else if(cpct_isKeyPressed(Key_W) && ent->on_ground){
            ent->jumping++;
            ent->vy = jumptable[ent->jumping]*4;
        }

        

    }
}

void sys_input_update(){
    man_ent_forall_type(sys_input_one, e_t_input);
}