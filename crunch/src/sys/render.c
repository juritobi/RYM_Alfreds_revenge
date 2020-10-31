#include "render.h"
#include <constants.h>

tile* tiles_pointer;
tile tiles[60];

ent_t** ren_ents_pointer;
ent_t* ren_ents[12];


void sys_ren_draw_tilemap(u8* tilemap){
    cpct_etm_setDrawTilemap4x8_ag(tilemap_W, tilemap_H, tilemap_W, tileset);
    cpct_etm_drawTilemap4x8_ag(CPCT_VMEM_START+240, tilemap);
}
void sys_ren_set_tile(u8 tile_index, u8 x, u8 y){
    if(x>=0 && x<=76 && y>=24 && y<=192){
        tile to_ren;
        to_ren.sprite = tileset + tile_index*tileset_length;
        to_ren.pos = cpct_getScreenPtr(CPCT_VMEM_START, x, y);
        tiles_pointer->sprite = to_ren.sprite;
        tiles_pointer->pos = to_ren.pos;
        ++tiles_pointer;
    }
}
void sys_ren_tile(u8 tile_index, u8 x, u8 y){
    tile to_ren;
    to_ren.sprite = tileset + tile_index*tileset_length;
    to_ren.pos = cpct_getScreenPtr(CPCT_VMEM_START, x, y);
    cpct_drawTileZigZagGrayCode4x8_af (to_ren.pos, to_ren.sprite);
}

void sys_ren_init(){
    tiles_pointer = tiles;
    ren_ents_pointer = ren_ents;
}

void sys_ren_one(ent_t* e){
    cpct_drawSprite (e->sprite, e->memory_pos, e->w, e->h);
}

void sys_ren_setup_one(ent_t* e){
    if(e->x>=0 && e->x+e->w<=80 && e->y>=24 && e->y+e->h<=200){
        e->memory_pos = cpct_getScreenPtr(CPCT_VMEM_START, e->x, e->y);
        *ren_ents_pointer = e;
        ++ren_ents_pointer;
    }
}
void sys_ren_setup(){
    man_ent_forall_type(sys_ren_setup_one, e_t_render);
}


void sys_ren_render(){
    tiles_pointer->pos = 0;
    tiles_pointer = tiles;
    *ren_ents_pointer = 0;
    ren_ents_pointer = ren_ents;
    while(tiles_pointer->pos){
        cpct_drawTileZigZagGrayCode4x8_af (tiles_pointer->pos, tiles_pointer->sprite);
        ++tiles_pointer;
    }
    while(*ren_ents_pointer){
        sys_ren_one(*ren_ents_pointer);
        ++ren_ents_pointer;
    }
    ren_ents_pointer = ren_ents;
    tiles_pointer = tiles;
}