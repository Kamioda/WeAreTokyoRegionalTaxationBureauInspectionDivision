#pragma once
#ifdef RIDAISAI
#include "ApplicationDirectory.hpp"
void AddErrorLog(const char* ErrorMessage, const ApplicationDirectory& App);
#else
void AddErrorLog(const char* ErrorMessage);
#endif
