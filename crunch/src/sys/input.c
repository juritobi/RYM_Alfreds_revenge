#include "input.h"
#include <man/man_ent.h>

void sys_input_one(ent_t* ent){
    if (ent->type & e_t_input)
    {
        cpct_scanKeyboard_f();
        
        ent->vx = 0;

        if(cpct_isKeyPressed(Key_D))
            ent->vx = 1;

        else if(cpct_isKeyPressed(Key_A))
            ent->vx = -1;

    }
    

}

void sys_input_update(){
    man_ent_forall_type(sys_input_one, e_t_input);
}