#pragma once
#include <cpctelera.h>

#define anim_frame_time 8

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

extern const anim_frame_t char_walking_right [];
extern const anim_frame_t char_standing_right [];
extern const anim_frame_t char_jumping_right [];
extern const anim_frame_t char_hitting_right [];

void sys_anim_init();
void sys_anim_update();