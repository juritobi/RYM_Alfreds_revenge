#include "render.h"
#include <constants.h>

u8 next_free_index;
tile tiles[20];
u16 null_end_tiles;


void sys_ren_draw_tilemap(u8* tilemap){
    cpct_etm_setDrawTilemap4x8_ag(tilemap_W, tilemap_H, tilemap_W, tileset);
    cpct_etm_drawTilemap4x8_ag(CPCT_VMEM_START+240, tilemap);
}
void sys_ren_set_tile(u8 tile_index, u8 x, u8 y){
    tile to_ren;
    to_ren.sprite = tileset + tile_index*tileset_length;
    to_ren.pos = cpct_getScreenPtr(CPCT_VMEM_START, x, y);
    tiles[next_free_index].sprite = to_ren.sprite;
    tiles[next_free_index].pos = to_ren.pos;
    next_free_index++;
}
void sys_ren_tile(u8 tile_index, u8 x, u8 y){
    tile to_ren;
    to_ren.sprite = tileset + tile_index*tileset_length;
    to_ren.pos = cpct_getScreenPtr(CPCT_VMEM_START, x, y);
    cpct_drawTileZigZagGrayCode4x8_af (to_ren.pos, to_ren.sprite);
}

void sys_ren_init(){
    cpct_memset(tiles, 0, sizeof(tiles));
    null_end_tiles = 0;
    next_free_index= 0;
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
    u8 index = 0;
    while(tiles[index]){
        cpct_drawTileZigZagGrayCode4x8_af (tiles[index].pos, tiles[index].sprite);
        ++index;
    }
    man_ent_forall_type(sys_ren_one, e_t_render);
    cpct_memset(tiles, 0, sizeof(tiles));
    next_free_index= 0;
}