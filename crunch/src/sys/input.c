#include "input.h"
#include <man/man_ent.h>

void sys_input_one(ent_t* ent){


}

void sys_input_update(){
    man_ent_forall_type(sys_input_one, e_t_input);
}