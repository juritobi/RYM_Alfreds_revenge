#pragma once
#include <cpctelera.h>

#define win 1
#define lose 2

void man_game_exit(u8 next);
void activate_render_signal();
void man_game_init();
u8 man_game_play();