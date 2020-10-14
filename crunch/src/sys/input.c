#include "input.h"
#include <man/man_ent.h>

#define swordCD 15
#define swordDuration 10
#define jumpCD 10
#define PiumPiumCD  25//las constantes si son un numero hay que hacerlas con #define no const, si utilizas const utilizan espacio en mememoria del amstrad, con define es una variable del compilador

const i8 jumptable[] = {-2, -2, -2, -2, -2, 0, 0}; //si lo ponemos en bytes sirectamente cons ahorramos un operacion del procesador

i8 swordUp = 0;
i8 swordTime = 0;
i8 swordCount = 15;

i8 jumpCont = 10;

i8 PiumPiumCont = 25;

void sys_input_one(ent_t* ent){
    
    ent->vx = 0;
    ent->vy = 8;

    // MONYECO

    if(cpct_isKeyPressed(Key_D)){
        ent->vx = 1;
    }
    else if(cpct_isKeyPressed(Key_A)){
        ent->vx = -1;
    }

    //SALTO Y SUS MIERDAS
    if(cpct_isKeyPressed(Key_W) && ent->on_ground && ent->jumping == -1 && jumpCont == swordCD){
        ent->jumping = 0;
    }
    ent->on_ground = 0;
    if(cpct_isKeyPressed(Key_S)){
        ent->on_ground=2;
    }

    if(jumpCont < swordCD){
        jumpCont++;
    }

    if(ent->jumping != -1){
        ent->vy = jumptable[ent->jumping]*4;
        if(ent->jumping < sizeof(jumptable)-1){
            ent->on_ground=2;
            ent->jumping++;
        }
        else{
            ent->jumping = -1;
            jumpCont=0;
        }
    }
    // PROYECTIL

    if(cpct_isKeyPressed(Key_P) && PiumPiumCont == PiumPiumCD ){
        man_ent_resurrect(ent, 2);
        PiumPiumCont = 0;
    }

    if(PiumPiumCont < PiumPiumCD){
        PiumPiumCont++;
    }
    
    // ESPADA
    //no lo tengo del todo claro pero parece que se puede hacer con menos variables
    if(cpct_isKeyPressed(Key_O) && !swordUp && swordCount == swordCD){
        man_ent_resurrect(ent, 1);
        swordUp = 1;
        ent->w = 8;
    }

    if(swordCount < swordCD){
        swordCount++;
    }

    if(swordUp && swordTime < swordDuration){
        man_ent_move(ent, 1);
        swordTime++;
        ent->w = 8;
    }

    if(swordTime == swordDuration){
        swordUp = 0;
        swordTime = 0;
        swordCount = 0;
        ent->w = 4;
    }
}

void sys_input_update(){
    ent_t* player = man_ent_get_char();
    sys_input_one(player);
}