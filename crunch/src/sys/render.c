#include "render.h"
#include <man/man_ent.h>


void sys_ren_one(ent_t* e){
    if(!(e->type & e_t_dead)){
        u8* pos = cpct_getScreenPtr(CPCT_VMEM_START, e->prevx, e->prevy);
        cpct_drawSolidBox(pos, #0x00, e->w, e->h);

        pos = cpct_getScreenPtr(CPCT_VMEM_START, e->x, e->y);
        cpct_drawSprite(e->sprite, pos, e->w, e->h);
//ineficiente
        e->prevx = e->x;
        e->prevy = e->y;
    }
}

void sys_ren_update(){
    man_ent_forall_type(sys_ren_one, e_t_render);
}