#pragma once
#include "Ini.h"
#include <chrono>
extern bool pcsp_end;
void easily_pcsp(Ini ini, const std::chrono::time_point<std::chrono::system_clock> start, const bool gm_mode);
