#pragma once

#include "types.h"

Window* createWindow(unsigned width,unsigned height,const char* name);
void draw(Array* array,Context* context);
void destroyWindow();

