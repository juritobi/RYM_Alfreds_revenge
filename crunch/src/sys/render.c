#include "render.h"
#include <constants.h>

u8 next_free_index;
ent_t* ents_to_render[8];
u16 null_at_end;

void sys_ren_draw_tilemap(u8* tilemap){
    cpct_etm_setDrawTilemap4x8_ag(tilemap_W, tilemap_H, tilemap_W, tileset);
    cpct_etm_drawTilemap4x8_ag(CPCT_VMEM_START+240, tilemap);
}
void sys_ren_draw_tile(u8 tile_index, u8 x, u8 y){
    void* tile = tileset + tile_index*tileset_length;
    u8* pos = cpct_getScreenPtr(CPCT_VMEM_START, x, y);
    cpct_drawTileZigZagGrayCode4x8_af (pos, tile);
}


void sys_ren_init(){
    ent_t* ents_to_render[8] = {0,0,0,0,0,0,0,0};
    u16 null_at_end = 0;
    next_free_index = 0;
}




void sys_ren_one(ent_t* e){
    cpct_drawSprite (e->sprite, e->memory_pos, e->w, e->h);
}
void sys_ren_setup_one(ent_t* e){
    e->memory_pos = cpct_getScreenPtr(CPCT_VMEM_START, e->x, e->y);
}
void sys_ren_setup(){
    man_ent_forall_type(sys_ren_setup_one, e_t_render);
}
void sys_ren_render(){
    man_ent_forall_type(sys_ren_one, e_t_render);
}


//runthroug array
/*u8 index = 0;
while(ents_to_render[index]){
    ent_t* e = ents_to_render[index];
    cpct_drawSprite (e->sprite, e->memory_pos, e->w, e->h);
    ++index;
}*/
//cpct_memset(ents_to_render, 0, sizeof(ents_to_render));
/*void add_to_array(ent_t* e){
ents_to_render[next_free_index] = e;
next_free_index++;
}*/