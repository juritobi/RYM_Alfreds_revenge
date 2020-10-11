#include "render.h"
#include <constants.h>

u8 next_free_index;
ent_t* ents_to_render[8];
u16 null_at_end;

void sys_ren_draw_tilemap(u8* tilemap){
    cpct_etm_setDrawTilemap4x8_ag(tilemap_W, tilemap_H, tilemap_W, tileset);
    cpct_etm_drawTilemap4x8_ag(CPCT_VMEM_START+240, tilemap);
}

void sys_ren_init(){
    ent_t* ents_to_render[8] = {0,0,0,0,0,0,0,0};
    u16 null_at_end = 0;
    next_free_index = 0;
}

/*UPDATES*/
void sys_ren_one_setup(ent_t* e){
    e->render_mode(e);
}
void sys_ren_setup(){
    clean_array();
    man_ent_forall_type(sys_ren_one_setup, e_t_render);
}
void sys_ren_render(){
    u8 index = 0;
    while(ents_to_render[index]){
        ents_to_render[index]->render(ents_to_render[index]);
        ++index;
    }
    //man_ent_forall_type(sys_ren_one_render, e_t_render);
}



/*PREPARACION*/
void sys_ren_get_pos(ent_t* e){
    e->prev_memory_pos = cpct_getScreenPtr(CPCT_VMEM_START, e->prevx, e->prevy);
    e->memory_pos = cpct_getScreenPtr(CPCT_VMEM_START, e->x, e->y);
}
void add_to_array(ent_t* e){
    ents_to_render[next_free_index] = e;
    next_free_index++;
}
void clean_array(){
    u8 index = 0;
    while(ents_to_render[index]){
        ents_to_render[index] = 0;
        ++index;
    }
    next_free_index = 0;
}

void sys_ren_block_setup(ent_t* e){
    sys_ren_get_pos(e);
    if(e->memory_pos == e->prev_memory_pos){
        e->render = sys_ren_block;
    }
    else{
        e->render = sys_ren_block_erasing;
    }
    add_to_array(e);
}
void sys_ren_blend_setup(ent_t* e){
    sys_ren_get_pos(e);
    if(e->memory_pos != e->prev_memory_pos){
        e->render = sys_ren_blend;
        add_to_array(e);
    }
}
void sys_ren_blend_setup_first(ent_t* e){
    sys_ren_get_pos(e);
    e->render_mode = sys_ren_blend_setup;
    e->render = sys_ren_blend_one;
    add_to_array(e);
}

/*RENDERIZADO*/
void sys_ren_block_erasing(ent_t* e){
    cpct_drawSolidBox (e->prev_memory_pos, 0x00, e->w, e->h);
    cpct_drawSprite (e->sprite, e->memory_pos, e->w, e->h);
}
void sys_ren_block(ent_t* e){
    cpct_drawSprite (e->sprite, e->memory_pos, e->w, e->h);
}

void sys_ren_blend_one(ent_t* e){
    cpct_drawSpriteBlended(e->memory_pos, e->h, e->w, e->sprite);
}
void sys_ren_blend(ent_t* e){
    cpct_drawSpriteBlended(e->prev_memory_pos, e->h, e->w, e->sprite);
    cpct_drawSpriteBlended(e->memory_pos, e->h, e->w, e->sprite);
}

void sys_ren_no_draw(ent_t* e){

}