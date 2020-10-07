#include "man_ent.h"
#include "sys/render.h"

ent_t ents[10];
u8 invalid_at_end_of_ents;
ent_t*  next_free_ent;

void man_ent_init(){
   next_free_ent = ents;
   cpct_memset (ents, e_t_invalid, sizeof(ents)+1);
}
void man_ent_update(){
}


ent_t* man_ent_create(){
   ent_t* res = next_free_ent;
   next_free_ent = res + 1;
   return res;
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


void man_ent_resurrect(ent_t* e, u8 displacement){
   ent_t* e_to_res = e + displacement;
   e_to_res->type &= ~e_t_dead;
   e_to_res->x = e->x + e_to_res->originalx;
   e_to_res->y = e->y + e_to_res->originaly;
   e_to_res->vx = e_to_res->originalvx;
   e_to_res->vy = e_to_res->originalvy;
   
}