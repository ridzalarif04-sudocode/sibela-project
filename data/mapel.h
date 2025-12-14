#ifndef mapel
#define mapel

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include "initDb.h"
#include "../model/model.h"
// #include "../libs/utils.h"
#include "../types/dbTypes.h"
// #include "../components/header.h"

// void createStaf(int lastIndex);

QUERYSTATUS createMapel(data *datas, int *nPage, SQLHDBC *dbConn, Mapel newMapel);
void findAllMapel(data *datas, int *nPage, SQLHDBC *dbConn);
QUERYSTATUS updateMapel(data *datas, int *nPage, SQLHDBC *dbConn, Mapel updatedMapel);
QUERYSTATUS deleteMapel(data *datas, int *nPage, SQLHDBC *dbConn, Mapel updatedMapel);

#endif