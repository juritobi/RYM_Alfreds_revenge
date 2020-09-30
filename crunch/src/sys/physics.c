#include "physics.h"
#include <man/man_ent.h>

void sys_phy_one(ent_t* ent){
    u8 newx = ent->x + ent->vx;
    if(newx > ent->x)
        man_ent_setdead(ent);
    else
        ent->x = newx;
}

void sys_phy_update(){
    man_ent_forall(sys_phy_one);
}