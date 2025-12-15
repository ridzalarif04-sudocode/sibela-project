#ifndef materi
#define materi

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
Staf findStafbyEmail(char email[], SQLHDBC *dbConn);

QUERYSTATUS createStaff(data *datas, int *nPage, SQLHDBC *dbConn, Staf newStaff);
void findAllStaff(data *datas, int *nPage, SQLHDBC *dbConn);
QUERYSTATUS updateStaff(data *datas, int *nPage, SQLHDBC *dbConn, Staf updatedStaff);
QUERYSTATUS deleteStaff(data *datas, int *nPage, SQLHDBC *dbConn, Staf updatedStaff);

#endif