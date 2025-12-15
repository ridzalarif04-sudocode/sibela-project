#include "pengajar.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

Pengajar findPengajarbyPhoneNum(char PhoneNum[], SQLHDBC *dbConn)
{
    Pengajar foundRecord;
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLUSMALLINT rowStatus[100];
    foundRecord.id_num = -1;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"SELECT * FROM pengajar WHERE no_hp = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(PhoneNum), 0, PhoneNum, 0, NULL);
    ret = SQLExecute(stmt);

    if (SQL_SUCCEEDED(ret))
    {
        ret = SQLFetch(stmt);

        switch (ret)
        {
        case SQL_NO_DATA:
            foundRecord.id_num = -1;
            break;

        default:
            SQLGetData(stmt, 1, SQL_C_LONG,
                       &foundRecord.id_num, sizeof(foundRecord.id_num), NULL);
            SQLGetData(stmt, 2, SQL_C_CHAR,
                       &foundRecord.id_pengajar, sizeof(foundRecord.id_pengajar), NULL);
            SQLGetData(stmt, 3, SQL_C_CHAR,
                       &foundRecord.nama, sizeof(foundRecord.nama), NULL);
            SQLGetData(stmt, 4, SQL_C_CHAR,
                       foundRecord.tanggal_lahir, sizeof(foundRecord.tanggal_lahir), NULL);
            SQLGetData(stmt, 5, SQL_C_CHAR,
                        foundRecord.tanggal_masuk, sizeof( foundRecord.tanggal_masuk), NULL);
            SQLGetData(stmt, 6, SQL_C_CHAR,
                       &foundRecord.no_hp, sizeof(foundRecord.no_hp), NULL);
            SQLGetData(stmt, 7, SQL_C_CHAR,
                       &foundRecord.password, sizeof(foundRecord.password), NULL);
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);

    return foundRecord;
}

void findAllPengajar(data *datas, int *nPage, SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLLEN rowsFetched = 0;
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    ret = SQLExecDirect(stmt, (SQLCHAR *)"SELECT COUNT(*) AS row_count FROM pengajar", SQL_NTS);
    if (SQL_SUCCEEDED(ret))
    {
        if (SQL_SUCCEEDED(SQLFetch(stmt)))
        {
            SQLGetData(stmt, 1, SQL_C_LONG, &count, 0, NULL);
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    int limit = 10;
    int offset = (datas->page - 1) * limit;
    *nPage = (int)ceil((float)count / limit);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"SELECT * FROM pengajar ORDER BY tanggal_masuk DESC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &limit, 0, NULL);

    ret = SQLExecute(stmt);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        printf("Successfully fetched %lld rows\n", rowsFetched);
        int i = (int)rowsFetched;
        printf("awikwok %d\n", i);

        SQLGetData(stmt, 1, SQL_C_LONG,
                   &datas->pengajars[i].id_num, sizeof(datas->pengajars[i].id_num), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &datas->pengajars[i].id_pengajar, sizeof(datas->pengajars[i].id_pengajar), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR,
                   &datas->pengajars[i].nama, sizeof(datas->pengajars[i].nama), NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR,
                   datas->pengajars[rowsFetched].tanggal_lahir, sizeof(datas->pengajars[rowsFetched].tanggal_lahir), NULL);
        SQLGetData(stmt, 5, SQL_C_CHAR,
                   datas->pengajars[rowsFetched].tanggal_masuk, sizeof(datas->pengajars[rowsFetched].tanggal_masuk), NULL);
        SQLGetData(stmt, 6, SQL_C_CHAR,
                   &datas->pengajars[i].no_hp, sizeof(datas->pengajars[i].no_hp), NULL);
        SQLGetData(stmt, 7, SQL_C_CHAR,
                   &datas->pengajars[i].password, sizeof(datas->pengajars[i].password), NULL);
        rowsFetched++;
    }
    datas->nPengajar = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

QUERYSTATUS createPengajar(InputField fields[], SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    Pengajar newPengajar;
    strcpy(newPengajar.nama,fields[1].value.text);
    strcpy(newPengajar.tanggal_lahir,fields[2].value.text);
    strcpy(newPengajar.no_hp,fields[3].value.text);
    strcpy(newPengajar.password,fields[4].value.text);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"INSERT INTO pengajar (nama, tanggal_lahir, no_hp, password) VALUES (?,?,?,?)", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newPengajar.nama), 0, newPengajar.nama, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_DATE, strlen(newPengajar.tanggal_lahir), 0, newPengajar.tanggal_lahir, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newPengajar.no_hp), 0, newPengajar.no_hp, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newPengajar.password), 0, newPengajar.password, 0, NULL);
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

QUERYSTATUS updatedPengajar(data *datas, int *nPage, SQLHDBC *dbConn, Pengajar updatedPengajar)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"UPDATE pengajar SET nama = ?, tanggal_lahir = ?, no_hp = ?, password = ? WHERE id_pengajar = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedPengajar.nama), 0, updatedPengajar.nama, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_DATE, strlen(dateBuff), 0, dateBuff, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedPengajar.no_hp), 0, updatedPengajar.no_hp, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedPengajar.password), 0, updatedPengajar.password, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedPengajar.id_pengajar), 0, updatedPengajar.id_pengajar, 0, NULL);
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

QUERYSTATUS deletePengajar(SQLHDBC *dbConn, Pengajar updatedPengajar)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"DELETE FROM pengajar WHERE id_pengajar = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedPengajar.id_pengajar), 0, updatedPengajar.id_pengajar, 0, NULL);
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