#ifndef MATERI_H
#define MATERI_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>

#include "../model/model.h"
// #include "../libs/utils.h"
#include "../types/dbTypes.h"
// #include "../components/header.h"
#include "../types/form.h"

QUERYSTATUS createMateri(InputField fields[], SQLHDBC *dbConn);
void findAllMateri(data *datas, int *nPage, SQLHDBC *dbConn);
void findAllMateriSelect(Select *selectObject, SQLHDBC *dbConn);
QUERYSTATUS updateMateri(InputField fields[], SQLHDBC *dbConn);
QUERYSTATUS deleteMateri(SQLHDBC *dbConn, Materi updatedMateri);

#endif