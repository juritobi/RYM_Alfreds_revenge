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
#define col_t_powerUp 0x10

//el tipo aumenta en funcion del numero de entidades que tenga la clase es decir char crea 3 entidades, por eso shoot es es el 3 
//y shoot crea 2 entidades por eso el siguiente sera 5
//los dos primero bits indican el numero de entidades que crean
#define e_c_undefined 0x00
#define e_c_char 0x40
#define e_c_tools 0x81
#define e_c_shoot 0x83
#define e_c_zombi 0x45
#define e_c_ghost 0x46
#define e_c_sonic 0x47
#define e_c_powerUp 0x48
#define e_c_boss1_1 0x49
#define e_c_boss_tools 0x0A


#define dir_right 0x00
#define dir_left 0x01

typedef struct et ent_t;

typedef void (*Ptrf_v_ep)(ent_t*);
typedef void (*Ptrf_v_epep)(ent_t*, ent_t*);
typedef union entity_role role_u;

typedef struct entity_default ent_tt;
typedef struct entity_character character_t;
typedef struct entity_object object_t;

typedef struct entity_input input_t;
typedef struct entity_AI AI_t;
typedef struct entity_animation cnimation_t;
typedef struct entity_collisions collisions_t;
typedef struct entity_physics physics_t;


//----------------------------------------------------------------------------------
//DEFAULT ENTITY--------------------------------------------------------------------
//----------------------------------------------------------------------------------

typedef struct entity_character{
   u8 hp;
   u8 invulnerable;
   u8 pup_type;
   i8 knockback;
   i8 dir;
   
};
typedef struct entity_object{
   u8 damage;
   u8 originalx, originaly;
   i8 originalvx, originalvy;
};
union entity_role{
   character_t character;
   object_t    object;
};
typedef struct entity_default{//things that every entity is goun to use
   u8 components;
   u8 x, y;
   u8* memory_pos;
   u8 w, h;
   u8 col_type; 
   const u8* sprite;
   Ptrf_v_ep death;
   role_u role;
};
//----------------------------------------------------------------------------------
//DEFAULT ENTITY--------------------------------------------------------------------
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//COMPONENTS------------------------------------------------------------------------
//----------------------------------------------------------------------------------
typedef struct entity_input{//thing that ONLY the player is going to use
   ent_t* e;
   u8 mp;
   i8 on_ground, jumping;
};
typedef struct entity_AI{//thing that ONLY the AI is going to use
   ent_t* e;
   Ptrf_v_ep act;
   u8 Ai_counter;
   i8 prev_vx, prev_vy;
};
typedef struct entity_animation{
   ent_t* e;
   u8 move_dir;
   u8 anim_timer;
   u8 action;  //action
   spr_frame_t* frame;   
   spr_set_t* sprite_set;  
};
typedef struct entity_physics{
   ent_t* e;
   i8 vx, vy;
};
//----------------------------------------------------------------------------------
//COMPONENTS------------------------------------------------------------------------
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//COMPONENT ARRAYS------------------------------------------------------------------
//----------------------------------------------------------------------------------

extern ent_t* player;
extern ent_t* AI_array [7];
extern ent_t* animation_array[14];
extern ent_t* walls_array[11];
extern ent_t* physics_array[14];
extern ent_t* render_array[14];


//----------------------------------------------------------------------------------
//COMPONENT ARRAYS------------------------------------------------------------------
//----------------------------------------------------------------------------------


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
   u8 Ai_counter;
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
   u8 mp;
}ent_class;





void man_ent_init();
void man_ent_reset();

void man_ent_create_class(u8 type, u8 x, u8 y, u8 mp);

ent_t* man_ent_create_from_template(const ent_t* template);
void man_ent_res_absolute(ent_t* e, u8 displacement);
void man_ent_resurrect(ent_t* e, u8 displacement);
void man_ent_move(ent_t* e, u8 displacement);

void man_ent_forall(Ptrf_v_ep fun);
void man_ent_forall_type(Ptrf_v_ep fun, ent_t** array);

void man_ent_forall_col_type_individual( Ptrf_v_ep fun, u8 types);
void man_ent_forall_col_type(Ptrf_v_epep fun, u8 first_type, u8 second_type);

void man_ent_max_hp(ent_t* ent);
void man_ent_max_mana(ent_t* ent);
void man_ent_max_melee(ent_t* sword);
void man_ent_max_range(ent_t* knife);

void man_ent_update(ent_t* dead_ent);


void man_ent_hit(ent_t* hitted, u8 damage);
void man_ent_char_death(ent_t* dead_ent);
void man_ent_generic_death(ent_t* dead_ent);
void man_ent_boss_death(ent_t* dead_ent);


ent_t* man_ent_get_char();