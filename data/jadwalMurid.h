#ifndef JADWALMURID_H
#define JADWALMURID_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>

#include "../model/model.h"
// #include "../libs/utils.h"
#include "../types/dbTypes.h"
#include "../types/form.h"

QUERYSTATUS createJadwalMurid(InputParams input, char id_pert[], SQLHDBC *dbConn);
QUERYSTATUS deleteteJadwalMuridByPertemuanID(char id_pert[], SQLHDBC *dbConn);

#endif