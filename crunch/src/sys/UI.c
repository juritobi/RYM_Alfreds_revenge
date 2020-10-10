#include "UI.h"
#include <man/man_ent.h>

void sys_UI_init(){
    u8* pos;
    cpct_drawSolidBox (CPCT_VMEM_START, 0xF0, 40, 16);
    cpct_drawSolidBox (CPCT_VMEM_START+40, 0xF0, 40, 16);

    cpct_drawSolidBox (CPCT_VMEM_START+10, 0xFF, 20, 6);
    pos = cpct_getScreenPtr (CPCT_VMEM_START,10, 7);
    cpct_drawSolidBox (pos, 0xFF, 20, 6);

    pos = cpct_getScreenPtr (CPCT_VMEM_START,10, 1);
    cpct_drawSolidBox (pos, 0x1F, 20, 4);
    pos = cpct_getScreenPtr (CPCT_VMEM_START,10, 8);
    cpct_drawSolidBox (pos, 0x11, 20, 4);

    
    pos = cpct_getScreenPtr (CPCT_VMEM_START,48, 3);
    cpct_waitHalts(1);
    cpct_drawStringM1 ("socore: ", pos);
    pos = cpct_getScreenPtr (CPCT_VMEM_START,64, 3);
    cpct_waitHalts(1);
    cpct_drawStringM1 ("0000", pos);

}
/*void sys_UI_update(){
    cpct_drawSolidBox (CPCT_VMEM_START, 0, 80, 16);
}*/