#pragma once
#include <cpctelera.h>
#include <sys/anim.h>

#define e_t_invalid 0x00
#define e_t_render 0x01
#define e_t_physics 0x02
#define e_t_input 0x04
#define e_t_AI 0x08
#define e_t_anim 0x10
#define e_t_col 0x20
#define e_t_undefined3 0x40
#define e_t_dead 0x80

#define col_t_undefined 0x00
#define col_t_ally 0x01
#define col_t_ally_breaker 0x02
#define col_t_enemy 0x04
#define col_t_enemy_breaker 0x08

//el tipo aumenta en funcion del numero de entidades que tenga la clase es decir char crea 3 entidades, por eso shoot es es el 3 
//y shoot crea 2 entidades por eso el siguiente sera 5
//los dos primero bits indican el numero de entidades que crean
#define e_c_undefined 0x00
#define e_c_char 0x40
#define e_c_tools 0x81
#define e_c_shoot 0x83
#define e_c_zombi 0x45

#define dir_right 0x00
#define dir_left 0x01

typedef struct et ent_t;
typedef void (*Ptrf_v_ep)(ent_t*);
typedef void (*Ptrf_v_epep)(ent_t*, ent_t*);
typedef struct et{
   //generic
   u8 type;
   u8 x, y;
   u8 prevx, prevy;
   u8 w, h;
   i8 vx, vy;
   u8 move_dir;
   Ptrf_v_ep death;
   //SONS
   u8 originalx, originaly;
   i8 originalvx, originalvy;
   //CHARACTERS
   u8 hp, mp, damage;
   u8 invulnerable;
   i8 knockback;
   i8 dir;
   //AI
   Ptrf_v_ep act;
   i8 prev_vx, prev_vy;
   //Input
   i8 on_ground, jumping;
   //Animation
   u8 anim_timer;
   u8 action;  //action
   spr_frame_t* frame;   
   spr_set_t* sprite_set;     
   //Collisions
   u8 col_type;                  
   //physics
   //render
   const u8* sprite;                   
   u8* memory_pos;       
};
typedef struct entity_class{
   u8 type;
   u8 x, y;
}ent_class;


void man_ent_init();
void man_ent_reset();

void man_ent_create_class(u8 type, u8 x, u8 y);

ent_t* man_ent_create_from_template(const ent_t* template);
void man_ent_resurrect(ent_t* e, u8 displacement);
void man_ent_move(ent_t* e, u8 displacement);

void man_ent_forall(Ptrf_v_ep fun);
void man_ent_forall_type(Ptrf_v_ep fun, u8 types);

void man_ent_forall_col_type_individual( Ptrf_v_ep fun, u8 types);
void man_ent_forall_col_type(Ptrf_v_epep fun, u8 first_type, u8 second_type);

void man_ent_update(ent_t* dead_ent);


void man_ent_hit(ent_t* hitted);
void man_ent_char_death(ent_t* dead_ent);
void man_ent_generic_death(ent_t* dead_ent);


ent_t* man_ent_get_char();