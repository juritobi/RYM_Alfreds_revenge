#pragma once
#include <cpctelera.h>


#define e_t_invalid 0x00
#define e_t_render 0x01
#define e_t_physics 0x02
#define e_t_input 0x04
#define e_t_AI 0x08
#define e_t_son 0x10
#define e_t_col 0x20
#define e_t_undefined3 0x40
#define e_t_dead 0x80

//el tipo aumenta en funcion del numero de entidades que tenga la clase es decir char crea 3 entidades, por eso shoot es es el 3 
//y shoot crea 2 entidades por eso el siguiente sera 5
//los dos primero bits indican el numero de entidades que crean
#define e_c_undefined 0x00
#define e_c_char 0xC0
#define e_c_shoot 0x83

typedef struct et ent_t;
typedef void (*Ptrf_v_ep)(ent_t*);
typedef struct et{
   u8 type;
   u8 x, y;
   u8 prevx, prevy;
   u8 originalx, originaly;
   u8 w, h;
   i8 vx, vy;
   u8 originalvx, originalvy;
   u8 on_ground; 
   i8 jumping;    //jump stage
   u8* sprite;
   Ptrf_v_ep act;
   Ptrf_v_ep render;
};
typedef struct entity_class{
   u8 type;
   u8 x, y;
}ent_class;


void man_ent_init();

void man_ent_create_class(u8 type, u8 x, u8 y);

ent_t* man_ent_create_from_template(ent_t* template);
void man_ent_setdead(ent_t* dead_ent);
void man_ent_resurrect(ent_t* e, u8 displacement);
void man_ent_move(ent_t* e, u8 displacement);

void man_ent_forall(Ptrf_v_ep fun);
void man_ent_forall_type(Ptrf_v_ep fun, u8 types);



ent_t* man_ent_get_char();