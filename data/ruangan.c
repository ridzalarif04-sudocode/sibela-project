#include "ruangan.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void findAllRuangan(data *datas, int *nPage, SQLHDBC *dbConn)
{


    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLLEN rowsFetched = 0;
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    ret = SQLExecDirect(stmt, (SQLCHAR *)"SELECT COUNT(*) AS row_count FROM ruangan", SQL_NTS);
    if (SQL_SUCCEEDED(ret))
    {
        if (SQL_SUCCEEDED(SQLFetch(stmt)))
        {
            SQLGetData(stmt, 1, SQL_C_LONG, &count, 0, NULL);
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    *nPage = (int)ceil((float)count / 10);
    printf("awikwok %d\n", *nPage);
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    int limit = 10;
    int offset = (datas->page - 1) * limit;
    *nPage = (int)ceil((float)count / limit);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"SELECT id_num, id_ruangan, lokasi, SUBSTRING(deskripsi, 1, 20) + IIF(LEN(deskripsi) >= 20,'...','') AS deskripsi FROM ruangan ORDER BY id_ruangan DESC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &limit, 0, NULL);
    ret = SQLExecute(stmt);

    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        printf("Successfully fetched %lld rows\n", rowsFetched);
        char dateBuff[50];
        int i = (int)rowsFetched;
        printf("awikwok %d\n", i);

        SQLGetData(stmt, 1, SQL_C_LONG,
                   &datas->ruangans[i].id_num, sizeof(datas->ruangans[i].id_num), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &datas->ruangans[i].id_ruangan, sizeof(datas->ruangans[i].id_ruangan), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR,
                   &datas->ruangans[i].lokasi, sizeof(datas->ruangans[i].lokasi), NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR,
                   &datas->ruangans[i].deskripsi, sizeof(datas->ruangans[i].deskripsi), NULL);
        printf("ruangan %d: %s\n", i, datas->ruangans[i].deskripsi);
        rowsFetched++;
    }
    datas->nRuangan = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

QUERYSTATUS createRuangan(InputField fields[],SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;

    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    Ruangan newRuangan;

    strcpy(newRuangan.lokasi, fields[1].value.text);
    strcpy(newRuangan.deskripsi, fields[2].value.text);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"INSERT INTO ruangan (lokasi, deskripsi) VALUES (?,?)", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newRuangan.lokasi), 0, newRuangan.lokasi, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newRuangan.deskripsi), 0, newRuangan.deskripsi, 0, NULL);
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

QUERYSTATUS updateRuangan(data *datas, int *nPage, SQLHDBC *dbConn, Ruangan updatedRuangan)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"UPDATE ruangan SET lokasi = ?, deskripsi = ? WHERE id_ruangan = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedRuangan.lokasi), 0, updatedRuangan.lokasi, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedRuangan.deskripsi), 0, updatedRuangan.deskripsi, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedRuangan.id_ruangan), 0, updatedRuangan.id_ruangan, 0, NULL);

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

QUERYSTATUS deleteRuangan (SQLHDBC *dbConn, Ruangan uptadeRuangan)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"DELETE FROM ruangan WHERE id_ruangan = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(uptadeRuangan.id_ruangan), 0, uptadeRuangan.id_ruangan, 0, NULL);
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