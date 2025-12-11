#ifndef pengajar
#define pengajar

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../model/model.h"
#include "../libs/utils.h"
#include "../types/dbTypes.h"
#include "initDb.h"


Pengajar findPengajarbyPhoneNum(char PhoneNum[], SQLHDBC *dbConn);

QUERYSTATUS createStaff(data *datas, int *nPage, SQLHDBC *dbConn, Staf newStaff);
void findAllStaff(data *datas, int *nPage, SQLHDBC *dbConn);
QUERYSTATUS updateStaff(data *datas, int *nPage, SQLHDBC *dbConn, Staf updatedStaff);
QUERYSTATUS deleteStaff(data *datas, int *nPage, SQLHDBC *dbConn, Staf updatedStaff);

#endif