#ifndef drawView
#define drawView

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../model/window.h"
#include "../libs/utils.h"
#include "../components/header.h"
#include "home/staffHome/staffHome.h"
#include "home/pengajarHome/pengajarHome.h"
#include "home/muridHome/muridHome.h"
#include "../constants/color.h"
#include "loginView.h"
#include "landingView.h"
#include "memberView.h"

void drawRootView(windowModel *windowM);

#endif