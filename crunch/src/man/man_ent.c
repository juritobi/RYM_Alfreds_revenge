#include "man_ent.h"

ent_t ents[10];
u8 invalid_at_end_of_ents;
ent_t*  next_free_ent;
u8    num_ents;

void man_ent_destroy(ent_t* dead_ent){
   ent_t* de = dead_ent;
   ent_t* last = next_free_ent;
   u8 num = num_ents;

   --last;
   --num;
   if(de == last){
      de->type = e_t_invalid;
   }
   else{
      cpct_memcpy(de, last, sizeof(ent_t));
      last->type = e_t_invalid;
  }

  next_free_ent = last;
  num_ents = num;
}

void man_ent_init(){
   //cpct_memset(ents, 0, sizeof(ents));
   next_free_ent = ents;
   num_ents = 0;
   invalid_at_end_of_ents = e_t_invalid;
}

ent_t* man_ent_create(){
   ent_t* res = next_free_ent;
   u8 num = num_ents;
   next_free_ent = res + 1;
   num_ents = num +1;
   return res;
}

void man_ent_setdead(ent_t* dead_ent){
   ent_t* de = dead_ent;
   de->type |= e_t_dead;
}

void man_ent_update(){
   ent_t* e = ents;

   while(e->type != e_t_invalid){
      if(e->type & e_t_dead){
         man_ent_destroy(e);
      }
      else{
         e++;
      }
   }
}

void man_ent_forall( void (*ptrfunc)(ent_t*)){
   ent_t* res = ents;
   while(res->type != e_t_invalid){
      ptrfunc(res);
      ++res;
   }
}
void man_ent_forall_type( void (*ptrfunc)(ent_t*), u8 types){
   ent_t* res = ents;
   while(res->type != e_t_invalid){
      if((res->type & types) == types){
         ptrfunc(res);
      }
      ++res;
   }
}
