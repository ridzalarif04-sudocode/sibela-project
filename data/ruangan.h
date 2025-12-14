#ifndef ruangan
#define ruangan

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
//Staf findStafbyEmail(char email[], SQLHDBC *dbConn);

QUERYSTATUS createRuangan(data *datas, int *nPage, SQLHDBC *dbConn, Ruangan newRuangan);
void findAllRuangan(data *datas, int *nPage, SQLHDBC *dbConn);
QUERYSTATUS updateRuangan(data *datas, int *nPage, SQLHDBC *dbConn, Ruangan updatedRuangan);
QUERYSTATUS deleteRuangan(data *datas, int *nPage, SQLHDBC *dbConn, Ruangan updatedRuangan);

#endif