#include "jadwalMurid.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

QUERYSTATUS createJadwalMurid(InputParams input, char id_pert[], SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;
    JadwalMurid newJamur;
    strcpy(newJamur.id_pertemuan, id_pert);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    for (int i = 0; i < input.charLen; i++)
    {
        strcpy(newJamur.id_murid, input.multiValue[i]);
        printf("Murid %d: %s\n", i + 1, newJamur.id_murid);
        SQLPrepare(stmt, (SQLCHAR *)"INSERT INTO jadwal_murid (id_pertemuan, id_murid) VALUES (?,?)", SQL_NTS);
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newJamur.id_pertemuan), 0, newJamur.id_pertemuan, 0, NULL);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newJamur.id_murid), 0, newJamur.id_murid, 0, NULL);
        ret = SQLExecute(stmt);

        if (SQL_SUCCEEDED(ret))
        {
            ret = SQLFetch(stmt);
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);

    switch (ret)
    {
    case SQL_SUCCESS:
        return SUCCESS;

    default:
        return FAILED;
    }
}

void findAllSelectedSiswaByPertemuanID(char id_pert[], Select *fields, SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char query[50];

    SQLLEN rowsFetched = 0;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"SELECT m.id_murid, m.nama FROM jadwal_murid jm, murid m WHERE jm.id_pertemuan = ? AND m.id_murid = jm.id_murid ORDER BY m.id_murid ASC", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(id_pert), 0, id_pert, 0, NULL);

    ret = SQLExecute(stmt);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        char dateBuff[50];
        int i = (int)rowsFetched;

        SQLGetData(stmt, 1, SQL_C_CHAR,
                   &fields->MultiSelected[i].value, sizeof(fields->MultiSelected[i].value), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &fields->MultiSelected[i].label, sizeof(fields->MultiSelected[i].label), NULL);

        rowsFetched++;
    }
    fields->nMultiSelected = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

QUERYSTATUS deleteteJadwalMuridByPertemuanID(char id_pert[], SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;
    JadwalMurid newJamur;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"DELETE FROM jadwal_murid WHERE id_pertemuan = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(id_pert), 0, id_pert, 0, NULL);
    ret = SQLExecute(stmt);

    if (SQL_SUCCEEDED(ret))
    {
        ret = SQLFetch(stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);

    switch (ret)
    {
    case SQL_SUCCESS:
        return SUCCESS;

    default:
        return FAILED;
    }
}