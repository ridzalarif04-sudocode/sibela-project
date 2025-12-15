#ifndef RUANGAN_H
#define RUANGAN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include "initDb.h"
#include "../model/model.h"
// #include "../libs/utils.h"
#include "../types/dbTypes.h"
// #include "../components/header.h"
#include "../types/form.h"

// void createStaf(int lastIndex);
//Staf findStafbyEmail(char email[], SQLHDBC *dbConn);

QUERYSTATUS createRuangan(InputField fields[],SQLHDBC *dbConn);
void findAllRuangan(data *datas, int *nPage, SQLHDBC *dbConn);
QUERYSTATUS updateRuangan(data *datas, int *nPage, SQLHDBC *dbConn, Ruangan updatedRuangan);
QUERYSTATUS deleteRuangan(SQLHDBC *dbConn, Ruangan updatedRuangan);

#endif