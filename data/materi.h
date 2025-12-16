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

QUERYSTATUS createMateri(data *datas, int *nPage, SQLHDBC *dbConn, Materi newMateri);
void findAllMateri(data *datas, int *nPage, SQLHDBC *dbConn);
QUERYSTATUS updateMateri(data *datas, int *nPage, SQLHDBC *dbConn, Materi updatedMateri);
QUERYSTATUS deleteMateri(data *datas, int *nPage, SQLHDBC *dbConn, Materi updatedMateri);

#endif