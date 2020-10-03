#include "physics.h"
#include <man/man_ent.h>

void sys_phy_one(ent_t* ent){
    ent->x += ent->vx;
    ent->y += ent->vy;
}

void sys_phy_update(){
    man_ent_forall_type(sys_phy_one, e_t_physics);
}