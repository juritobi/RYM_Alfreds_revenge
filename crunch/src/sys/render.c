#include "render.h"
#include <constants.h>
#include <man/man_ent.h>


void sys_ren_draw_tilemap(u8* tilemap){
    cpct_etm_setDrawTilemap4x8_ag(tilemap_W, tilemap_H, tilemap_W, tileset);
    cpct_etm_drawTilemap4x8_ag(CPCT_VMEM_START, tilemap);
}

void sys_ren_one(ent_t* e){
    if(!(e->type & e_t_dead)){
        u8* prev_pos = cpct_getScreenPtr(CPCT_VMEM_START, e->prevx, e->prevy);
        u8* pos = cpct_getScreenPtr(CPCT_VMEM_START, e->x, e->y);
        cpct_drawSolidBox (prev_pos, 0xf0, e->w, e->h);
        cpct_drawSprite(e->sprite, pos, e->w, e->h);
        e->prevx=e->x;
        e->prevy=e->y;
    }
}

void sys_ren_update(){
    man_ent_forall_type(sys_ren_one, e_t_render);
}