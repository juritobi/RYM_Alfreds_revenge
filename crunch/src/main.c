#include <cpctelera.h>
#include <sprites/g_palette.h>
#include <man/app.h>

void main(void) {

    cpct_disableFirmware();
    cpct_setBorder(HW_BLACK);
    cpct_setPalette(g_palette,4);

    man_app_init();
    man_app_update();
    while(1);

}
