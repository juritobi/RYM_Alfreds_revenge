#include "man_ent.h"
#include <sys/render.h>
#include <sys/AI.h>
#include <sprites/char.h>
#include <sprites/shooter.h>
#include <sprites/proyectile.h>
/*character-----------------------------------------------------*/
const ent_t init_player = {
    e_t_physics | e_t_render | e_t_input | e_t_col,  //tipo
    col_t_ally,                           //tipo de colision cada entidad puede tener un solo tipo
    0,0,                                  //x,y
    0,0,                                  //prevx, prevy
    0,0,                                  //originalx, originaly
    4,24,                                   //w,h
    0,0,                                    //vx,vy
    0,-1,                                     //on ground and jumping
    spr_char_0,                             //sprite
    0,                                   //AI function
    sys_ren_blend_first                  //render function
};
const ent_t init_sword = {
    e_t_dead | e_t_son | e_t_render,            //tipo
    col_t_ally_breaker,                           //tipo de colision
    4,0,                                  //parent displacement for sons
    4,0,                                    //prevx, prevy
    4,0,                                    //originalx, originaly
    4,24,                                   //w,h
    0,0,                                    //vx,vy
    0,-1,                                     //on ground and jumping
    spr_char_1,                             //sprite
    0,                                  //AI function
    sys_ren_blend_first
};
const ent_t init_knife = {
    e_t_dead | e_t_son | e_t_render | e_t_physics,           //tipo
    col_t_ally_breaker,                           //tipo de colision
    4,8,                                  //parent displacement for sons
    4,8,                                   //prevx, prevy
    4,8,                                  //parent displacement for sons
    4,8,                                   //w,h
    0,0,                                    //vx,vy
    0,-1,                                     //on ground and jumping
    spr_char_2,                             //sprite
    0,                                  //AI function
    sys_ren_blend_first
};
/*character-----------------------------------------------------*/
/*shoot-----------------------------------------------------*/
const ent_t init_shoot = {
    e_t_render | e_t_AI,
    col_t_enemy,                           //tipo de colision
    0,0,
    0,0,    
    0,0,                              
    4,16,
    0,-1,
    0,0,                                     //on ground and jumping
    spr_shooter_0,
    sys_AI_shoot,
    sys_ren_blend_first
};
const ent_t init_shoot_son = {
    e_t_dead | e_t_son | e_t_physics | e_t_render,
    col_t_enemy_breaker,                           //tipo de colision
    -2,4,
    -2,4,
    -2,4,
    4,8,
    -1,0,
    0,-1,                                     //on ground and jumping
    spr_p_1,
    0,
    sys_ren_blend_first
};
/*shoot-----------------------------------------------------*/

ent_t ents[20];
u8 invalid_at_end_of_ents;
ent_t*  next_free_ent;

void man_ent_init(){
   next_free_ent = ents;
   cpct_memset (ents, e_t_invalid, sizeof(ents)+1);
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
void man_ent_setdead(ent_t* dead_ent){
   ent_t* de = dead_ent;
   de->type |= e_t_dead;
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
}
ent_t* man_ent_get_char(){
   return &ents[0];
}