#include "man_ent.h"
#include <man/man_game.h>
#include <sys/render.h>
#include <sys/AI.h>
#include <sprites/char.h>
#include <sprites/sword.h>
#include <sprites/shooter.h>
#include <sprites/zombi.h>
#include <sprites/proyectile.h>
#include <sprites/sword.h>
/*character-----------------------------------------------------*/
const ent_t init_player = {
   //generic
   e_t_physics | e_t_render | e_t_input | e_t_col,             //u8 type;
   0,0,                                                        //u8 x, y;
   0,0,                                                        //u8 prevx, prevy;
   4,24,                                                       //u8 w, h;
   0,0,                                                        //i8 vx, vy;
   man_ent_char_death,                                         //Ptrf_v_ep death;
   //SONS
   0,0,                                                        //u8 originalx, originaly;
   0,0,                                                        //i8 originalvx, originalvy;
   //CHARACTERS
   5,5,0,                                                       //u8 hp, mp, damage;
   50,                                                          // invulnerable
   //AI
   0,                                                          //Ptrf_v_ep act;
   0,0,                                                        //i8 prev_vx, prev_vy;
   //Input
   0,0,                                                        //i8 on_ground, jumping;        
   //Collisions
   col_t_ally,                                                 //u8 col_type;                  
   //physics
   //render
   spr_char_0,                                                 //u8* sprite;                   
   0,                                                          //u8* memory_pos;               
   0,                                                          //u8* prev_memory_pos;    
   sys_ren_block_setup,                                        //Ptrf_v_ep render_mode;
   sys_ren_no_draw                                             //Ptrf_v_ep render; 
};
const ent_t init_sword = {
   //generic
   e_t_dead|e_t_render,                                        //u8 type;
   0,0,                                                        //u8 x, y;
   0,0,                                                        //u8 prevx, prevy;
   4,24,                                                       //u8 w, h;
   0,0,                                                        //i8 vx, vy;
   man_ent_generic_death,                                       //Ptrf_v_ep death;
   //SONS
   4,0,                                                        //u8 originalx, originaly;
   0,0,                                                        //i8 originalvx, originalvy;
   //CHARACTERS
   1,0,1,                                                       //u8 hp, mp, damage;
   50,                                                          // invulnerable
   //AI
   0,                                                          //Ptrf_v_ep act;
   0,0,                                                        //i8 prev_vx, prev_vy;
   //Input
   0,0,                                                         //i8 on_ground, jumping;        
   //Collisions
   col_t_ally_breaker,                                         //u8 col_type;                  
   //physics
   //render
   spr_sword,                                                  //u8* sprite;                   
   0,                                                          //u8* memory_pos;               
   0,                                                          //u8* prev_memory_pos;
   sys_ren_blend_setup_first,                                  //Ptrf_v_ep render_mode;
   sys_ren_no_draw                                             //Ptrf_v_ep render;
};
const ent_t init_knife = {
   //generic
   e_t_dead | e_t_render | e_t_physics | e_t_col,               //u8 type;
   0,0,                                                        //u8 x, y;
   0,0,                                                        //u8 prevx, prevy;
   4,8,                                                        //u8 w, h;
   1,0,                                                        //i8 vx, vy;
   man_ent_generic_death,                                       //Ptrf_v_ep death;
   //SONS
   4,8,                                                        //u8 originalx, originaly;
   1,0,                                                        //i8 originalvx, originalvy;
   //CHARACTERS
   1,0,1,                                                       //u8 hp, mp, damage;
   50,                                                          // invulnerable
   //AI
   0,                                                          //Ptrf_v_ep act;
   0,0,                                                        //i8 prev_vx, prev_vy;
   //Input
   0,0,                                                         //i8 on_ground, jumping;        
   //Collisions
   col_t_ally_breaker,                                         //u8 col_type;                  
   //physics
   //render
   spr_p_0,                                                //u8* sprite;                   
   0,                                                          //u8* memory_pos;               
   0,                                                          //u8* prev_memory_pos; 
   sys_ren_block_setup,                                        //Ptrf_v_ep render_mode;
   sys_ren_no_draw                                             //Ptrf_v_ep render;
};
/*character-----------------------------------------------------*/
/*shoot-----------------------------------------------------*/
const ent_t init_shoot = {
   //generic
   e_t_AI | e_t_render,                                         //u8 type;
   0,0,                                                        //u8 x, y;
   0,0,                                                        //u8 prevx, prevy;
   4,16,                                                       //u8 w, h;
   0,0,                                                        //i8 vx, vy;
   man_ent_generic_death,                                       //Ptrf_v_ep death;
   //SONS
   0,0,                                                        //u8 originalx, originaly;
   0,0,                                                        //i8 originalvx, originalvy;
   //CHARACTERS
   1,0,1,                                                       //u8 hp, mp, damage;
   50,                                                          // invulnerable
   //AI
   sys_AI_shoot,                                               //Ptrf_v_ep act;
   0,0,                                                        //i8 prev_vx, prev_vy;
   //Input
   0,0,                                                         //i8 on_ground, jumping;        
   //Collisions
   col_t_enemy,                                                //u8 col_type;                  
   //physics
   //render
   spr_shooter_0,                                                //u8* sprite;                   
   0,                                                          //u8* memory_pos;               
   0,                                                          //u8* prev_memory_pos;
   sys_ren_block_setup,                                        //Ptrf_v_ep render_mode;
   sys_ren_no_draw                                             //Ptrf_v_ep render;
};
const ent_t init_shoot_son = {
   //generic
   e_t_dead | e_t_physics | e_t_render | e_t_col,              //u8 type;
   0,0,                                                        //u8 x, y;
   0,0,                                                        //u8 prevx, prevy;
   4,8,                                                        //u8 w, h;
   -1,0,                                                       //i8 vx, vy;
   man_ent_generic_death,                                      //Ptrf_v_ep death;
   //SONS
   -2,4,                                                       //u8 originalx, originaly;
   -1,0,                                                        //i8 originalvx, originalvy;
   //CHARACTERS
   1,0,1,                                                       //u8 hp, mp, damage;
   50,                                                          // invulnerable
   //AI
   0,                                                          //Ptrf_v_ep act;
   0,0,                                                        //i8 prev_vx, prev_vy;
   //Input
   0,0,                                                        //i8 on_ground, jumping;        
   //Collisions
   col_t_enemy_breaker,                                        //u8 col_type;                  
   //physics
   //render
   spr_p_1,                                                    //u8* sprite;                   
   0,                                                          //u8* memory_pos;               
   0,                                                          //u8* prev_memory_pos;  
   sys_ren_block_setup,                                        //Ptrf_v_ep render_mode;
   sys_ren_no_draw                                             //Ptrf_v_ep render; 
};
/*shoot-----------------------------------------------------*/
/*zombi-----------------------------------------------------*/
const ent_t init_zombi = {

   //generic
   e_t_render | e_t_AI | e_t_col | e_t_physics,                //u8 type;
   0,0,                                                        //u8 x, y;
   0,0,                                                        //u8 prevx, prevy;
   2,24,                                                       //u8 w, h;
   0,0,                                                        //i8 vx, vy;
   man_ent_generic_death,                                       //Ptrf_v_ep death;
   //SONS
   0,0,                                                        //u8 originalx, originaly;
   0,0,                                                        //i8 originalvx, originalvy;
   //CHARACTERS
   2,0,1,                                                       //u8 hp, mp, damage;
   50,                                                          // invulnerable
   //AI
   sys_AI_zombi,                                               //Ptrf_v_ep act;
   0,0,                                                        //i8 prev_vx, prev_vy;
   //Input
   0,0,                                                         //i8 on_ground, jumping;        
   //Collisions
   col_t_enemy,                                                //u8 col_type;                  
   //physics
   //render
   spr_zombi_0,                                                //u8* sprite;                   
   0,                                                          //u8* memory_pos;               
   0,                                                          //u8* prev_memory_pos;
   sys_ren_block_setup,                                        //Ptrf_v_ep render_mode;
   sys_ren_no_draw                                             //Ptrf_v_ep render; 
};
/*zombi-----------------------------------------------------*/
ent_t ents[20];
u8 invalid_at_end_of_ents;
ent_t*  next_free_ent;

void man_ent_init(){
   next_free_ent = ents;
   cpct_memset (ents, e_t_invalid, sizeof(ents)+1);
}

void man_ent_reset_pos(ent_t* e){
   e->prevx = e->x;
   e->prevy = e->y;

   if(e->hp == 0){
      e->death(e);
   }
// esta wea se va a descontrolar
   // si enemigo o ally vida = 0 -> procede a cometer sudoku
}

ent_t* man_ent_create(){
   ent_t* res = next_free_ent;
   next_free_ent = res + 1;
   return res;
}
//tipo tiene en los 2 primeros bit el numero de entidades que crea y en los siguientes la entidad en la que empieza a crear
//la inicializacion de datos es para setear en ents el numro de entidades y class_main y class_init el puntero a la primera entidad que tiene que crear
//luego las crea en bucle y cambia la posicion de la entidad principal que sera siempre la primera de las 3
void man_ent_create_class(u8 type, u8 x, u8 y){
   u8 class_ents = (type & 0b11000000);
   ent_t* class_init = &init_player;
   class_init += (type & 0b00111111);
   class_ents = class_ents >> 6;

   while(class_ents){
      ent_t* ent_in_class = man_ent_create_from_template(class_init);
      ent_in_class->x = x;
      ent_in_class->y = y;
      class_init++;
      class_ents--;
   }
}

ent_t* man_ent_create_from_template(ent_t* template){
   ent_t* res = man_ent_create();
   cpct_memcpy(res, template, sizeof(ent_t));
   return res;
}

void man_ent_char_death(ent_t* dead_ent){
   man_game_exit();
}
void man_ent_generic_death(ent_t* dead_ent){
   dead_ent->type |= e_t_dead;
}

void man_ent_forall(Ptrf_v_ep fun){
   ent_t* res = ents;
   while(res->type != e_t_invalid){
      fun(res);
      ++res;
   }
}
void man_ent_forall_type( Ptrf_v_ep fun, u8 types){
   ent_t* res = ents;
   while(res->type != e_t_invalid){
      if(!(res->type & e_t_dead)){
         if((res->type & types) == types){
            fun(res);
         }
      }
      ++res;
   }
}

void man_ent_forall_col_type_individual( Ptrf_v_ep fun, u8 types){
   ent_t* res = ents;
   while(res->type != e_t_invalid){
      if(!(res->type & e_t_dead)){
         if((res->col_type & types) == types){
            fun(res);
         }
      }
      ++res;
   }
}

void man_ent_forall_col_type( Ptrf_v_epep fun, u8 first_type, u8 second_type){
   ent_t* ents1 = ents;
   ent_t* ents2 = ents;
   while(ents1->type != e_t_invalid){
      if((!(ents1->type & e_t_dead)) && (ents1->col_type & first_type)){

         while( ents2->type != e_t_invalid ){
            if(!(ents2->type & e_t_dead) && (ents2->col_type & second_type)) {
               fun(ents1, ents2);
            }
            ++ents2;
         }

      }
      ++ents1;
   }
}


void man_ent_resurrect(ent_t* e, u8 displacement){
   ent_t* e_to_res = e + displacement;
   e_to_res->type &= ~e_t_dead;
   e_to_res->x = e->x + e_to_res->originalx;
   e_to_res->y = e->y + e_to_res->originaly;
   e_to_res->vx = e_to_res->originalvx;
   e_to_res->vy = e_to_res->originalvy;
   
}

void man_ent_move(ent_t* e, u8 displacement){
   ent_t* e_to_move = e + displacement;
   e_to_move->x = e->x + e_to_move->originalx;
   e_to_move->y = e->y + e_to_move->originaly;
   
}
ent_t* man_ent_get_char(){
   return &ents[0];
}