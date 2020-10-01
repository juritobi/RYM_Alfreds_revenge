#include <cpctelera.h>
#include <man/man_game.h>
#include <sprites/g_palette.h>

void main(void) {

    cpct_disableFirmware();
    cpct_setBorder(HW_BLACK);
    cpct_setPalette(g_palette,4);

    man_game_init();
    man_game_play();
}
