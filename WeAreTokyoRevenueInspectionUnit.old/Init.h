#pragma once
#include "PowerState.h"
int init(PowerState power, ApplicationDirectory directory, int &string_size);
int end(const int ret_num);
int end(const char* error_message);
