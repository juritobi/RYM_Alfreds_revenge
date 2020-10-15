#pragma once
#include <cpctelera.h>

typedef struct anFr anim_frame_t;
typedef union next_frame_pointer next_fr;

union next_frame_pointer{
    u8* spr;
    anim_frame_t* next;
};

struct anFr{
    u8 time;
    next_fr value;
};

extern const anim_frame_t char_walk_right [];


void sys_anim_init();
void sys_anim_update();