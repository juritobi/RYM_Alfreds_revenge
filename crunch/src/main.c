#include <cpctelera.h>
#include <man/man_game.h>
#include <sprites/g_palette.h>
#include <sprites/tileset.h>
#include <tilemaps/lvl0.h>
#include <tilemaps/lvl0_pack.h> 

u8 tset[lvl0_pack_size];

void main(void) {

    
    u8* tset_end= &tset[lvl0_pack_size-1];

    cpct_disableFirmware();
    cpct_setBorder(HW_BLACK);
    cpct_setPalette(g_palette,4);

    man_game_init();

    
    cpct_zx7b_decrunch_s(tset_end, lvl0_pack_end);
    cpct_etm_setDrawTilemap4x8_ag (lvl0_W, lvl0_H, lvl0_W, tileset_00);
    cpct_etm_drawTilemap4x8_ag(CPCT_VMEM_START, tset);

    man_game_play();
}
