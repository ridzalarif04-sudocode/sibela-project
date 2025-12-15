#ifndef STAFFHOME_H
#define STAFFHOME_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../../../libs/headers/raylib.h"
#include "../../../model/window.h"
#include "../../../libs/utils.h"
#include "../../../components/header.h"
#include "../../../data/staf.h"
#include "../../../constants/color.h"
#include "components/staff/read.h"
#include "components/staff/create.h"
#include "components/staff/update.h"
#include "components/pengajar/read.h"
#include "components/pengajar/create.h"
#include "components/pengajar/update.h"
#include "components/mapel/read.h"
#include "components/mapel/create.h"
#include "components/mapel/update.h"
#include "components/ruangan/read.h"
#include "components/ruangan/create.h"
// #include "components/ruangan/update.h"

void drawStaffHome(windowModel *windowM);

#endif