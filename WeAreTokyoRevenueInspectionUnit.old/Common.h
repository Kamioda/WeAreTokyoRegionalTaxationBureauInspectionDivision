#pragma once
#include "Graphic.h"
#include "KeyConfig.h"
bool check_pcsp();
bool loop();
void print_cursole(const int x, const int y, const int width, const int height, const Color cursole_color);
int move_cursole(int &cursole, const int cursole_max, Key &key);
