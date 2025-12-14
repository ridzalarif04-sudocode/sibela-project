#ifndef Loading
#define Loading

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../libs/headers/raylib.h"
#include "../model/window.h"
#include "../libs/utils.h"
#include "../components/header.h"
#include "../constants/color.h"

void LoadingScreen(windowModel *windowM, float progress);

#endif