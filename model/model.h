#ifndef model
#define model

typedef void *SQLHANDLE;
typedef SQLHANDLE SQLHDBC;
typedef short SQLSMALLINT;
#include "../types/dbTypes.h"

typedef struct
{
    Staf staffs[100];
    SQLSMALLINT nStaf;
    Pengajar pengajars[100];
    SQLSMALLINT nPengajar;
    Murid murids[100];
    SQLSMALLINT nMurid;
    Ruangan ruangans[100];
    SQLSMALLINT nRuangan;
    Mapel Mapels[100];
    SQLSMALLINT nMapel;
    int page;
    int totalPages;
} data;



typedef enum
{
    SUCCESS,
    FAILED
} QUERYSTATUS;

void readDBDsn(char target[]);
void initSQLConn(SQLHDBC *dbConn);
void disconnectDb(SQLHDBC *dbConn);

#endif