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

QUERYSTATUS createPengajar(data *datas, int *nPage, SQLHDBC *dbConn, Pengajar newPengajar);
void findAllPengajar(data *datas, int *nPage, SQLHDBC *dbConn);
QUERYSTATUS updatedPengajar(data *datas, int *nPage, SQLHDBC *dbConn, Pengajar updatedPengajar);
QUERYSTATUS deletePengajar(data *datas, int *nPage, SQLHDBC *dbConn, Pengajar updatedPengajar);

#endif