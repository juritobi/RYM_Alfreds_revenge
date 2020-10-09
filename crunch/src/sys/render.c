#include "render.h"
#include <constants.h>


void sys_ren_draw_tilemap(u8* tilemap){
    cpct_etm_setDrawTilemap4x8_ag(tilemap_W, tilemap_H, tilemap_W, tileset);
    cpct_etm_drawTilemap4x8_ag(CPCT_VMEM_START, tilemap);
}

void sys_ren_one(ent_t* e){
    e->render(e);
}
void sys_ren_update(){
    man_ent_forall_type(sys_ren_one, e_t_render);
}

void sys_ren_get_pos(ent_t* e){
    e->prev_memory_pos = cpct_getScreenPtr(CPCT_VMEM_START, e->prevx, e->prevy);
    e->memory_pos = cpct_getScreenPtr(CPCT_VMEM_START, e->x, e->y);
    /*if(e->memory_pos == e->prev_memory_pos){
        e->type = e->type ^ e_t_render;
    }*/
}

void sys_ren_block(ent_t* e){
    cpct_drawSolidBox (e->prev_memory_pos, 0x00, e->w, e->h);
    cpct_drawSprite (e->sprite, e->memory_pos, e->w, e->h);
}
void sys_ren_blend_first(ent_t* e){
    cpct_drawSpriteBlended(e->memory_pos, e->h, e->w, e->sprite);
    e->render = sys_ren_blend;
}
void sys_ren_blend(ent_t* e){
    cpct_drawSpriteBlended(e->prev_memory_pos, e->h, e->w, e->sprite);
    cpct_drawSpriteBlended(e->memory_pos, e->h, e->w, e->sprite);
}

void sys_ren_kill(ent_t* e){
    u8* pos = cpct_getScreenPtr(CPCT_VMEM_START, e->x, e->y);
    cpct_drawSpriteBlended(pos, e->h, e->w, e->sprite);
}