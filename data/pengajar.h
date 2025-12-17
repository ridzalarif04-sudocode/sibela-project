#ifndef PENGAJAR_H
#define PENGAJAR_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../model/model.h"
#include "../libs/utils.h"
#include "../types/dbTypes.h"
#include "../types/form.h"

Pengajar findPengajarbyPhoneNum(char PhoneNum[], SQLHDBC *dbConn);

QUERYSTATUS createPengajar(InputField fields[], SQLHDBC *dbConn);
void findAllPengajar(data *datas, int *nPage, SQLHDBC *dbConn);
void findAllPengajarSelect(Select *selectObject, SQLHDBC *dbConn);
QUERYSTATUS updatePengajar(InputField fields[], SQLHDBC *dbConn);
QUERYSTATUS deletePengajar(SQLHDBC *dbConn, Pengajar updatedPengajar);

#endif