#ifndef MURID_H
#define MURID_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../model/model.h"
#include "../libs/utils.h"
#include "../types/dbTypes.h"
#include "../types/form.h"

Murid findMuridbyPhoneNum(char PhoneNum[], SQLHDBC *dbConn);

// CRUD
QUERYSTATUS createMurid(InputField fields[], SQLHDBC *dbConn);
void findAllMurid(data *datas, int *nPage, SQLHDBC *dbConn);
void findAllMuridSelect(Select *selectObject, SQLHDBC *dbConn);
QUERYSTATUS updateMurid(InputField fields[], SQLHDBC *dbConn);
QUERYSTATUS deleteMurid(SQLHDBC *dbConn, Murid updatedMurid);

#endif