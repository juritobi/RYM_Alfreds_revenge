#pragma once
#include <cpctelera.h>


#define e_t_invalid 0x00
#define e_t_render 0x01
#define e_t_physics 0x02
#define e_t_input 0x04
#define e_t_AI 0x08
#define e_t_son 0x10
#define e_t_undefined2 0x20
#define e_t_undefined3 0x40
#define e_t_dead 0x80

typedef struct et ent_t;
typedef void (*Ptrf_v_ep)(ent_t*);
typedef struct et{
   u8 type;
   u8 x, y;
   u8 prevx, prevy;
   u8 w, h;
   i8 vx, vy;
   i8 prevvx, prevvy;
   u8* sprite;
   Ptrf_v_ep act;
};

void man_ent_init();
void man_ent_update();

ent_t* man_ent_create();
ent_t* man_ent_create_from_template(ent_t* template);
void man_ent_setdead(ent_t* dead_ent);

void man_ent_forall(Ptrf_v_ep fun);
void man_ent_forall_type(Ptrf_v_ep fun, u8 types);