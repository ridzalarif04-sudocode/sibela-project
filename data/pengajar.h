#ifndef PENGAJAR_H
#define PENGAJAR_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../model/model.h"
#include "../libs/utils.h"
#include "../types/dbTypes.h"
#include "../types/form.h"
#include "initDb.h"


Pengajar findPengajarbyPhoneNum(char PhoneNum[], SQLHDBC *dbConn);

QUERYSTATUS createPengajar(InputField fields[], SQLHDBC *dbConn);
void findAllPengajar(data *datas, int *nPage, SQLHDBC *dbConn);
QUERYSTATUS updatedPengajar(data *datas, int *nPage, SQLHDBC *dbConn, Pengajar updatedPengajar);
QUERYSTATUS deletePengajar(SQLHDBC *dbConn, Pengajar updatedPengajar);

#endif