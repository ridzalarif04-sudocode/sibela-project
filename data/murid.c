#include "murid.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

Murid findMuridbyPhoneNum(char PhoneNum[], SQLHDBC *dbConn)
{
    Murid foundRecord;
    SQLHSTMT stmt;
    SQLRETURN ret;
    char dateBuff[50];
    SQLUSMALLINT rowStatus[100];
    foundRecord.id_num = -1;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"SELECT * FROM murid WHERE no_hp = ?", SQL_NTS);
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
                       &foundRecord.id_murid, sizeof(foundRecord.id_murid), NULL);
            SQLGetData(stmt, 3, SQL_C_CHAR,
                       &foundRecord.nama, sizeof(foundRecord.nama), NULL);
            SQLGetData(stmt, 4, SQL_C_CHAR,
                       dateBuff, sizeof(dateBuff), NULL);
            foundRecord.tanggal_lahir = parseDate(dateBuff);
            SQLGetData(stmt, 5, SQL_C_LONG,
                       &foundRecord.tingkat, sizeof(foundRecord.tingkat), NULL);
            SQLGetData(stmt, 6, SQL_C_CHAR,
                       dateBuff, sizeof(dateBuff), NULL);
            foundRecord.tanggal_masuk = parseDate(dateBuff);
            SQLGetData(stmt, 7, SQL_C_CHAR,
                       &foundRecord.no_hp, sizeof(foundRecord.no_hp), NULL);
            SQLGetData(stmt, 8, SQL_C_CHAR,
                       &foundRecord.password, sizeof(foundRecord.password), NULL);
            
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);

    return foundRecord;
}


void findAllMurid(data *datas, int *nPage, SQLHDBC *dbConn)
{

    if (datas->nMurid > 0)
        return;

    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLLEN rowsFetched = 0;
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    ret = SQLExecDirect(stmt, (SQLCHAR *)"SELECT COUNT(*) AS row_count FROM murid", SQL_NTS);
    if (SQL_SUCCEEDED(ret))
    {
        if (SQL_SUCCEEDED(SQLFetch(stmt)))
        {
            SQLGetData(stmt, 1, SQL_C_LONG, &count, 0, NULL);
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    *nPage = (int)ceil((float)count / 10);
    printf("awikwok murid %d\n", *nPage);
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    ret = SQLExecDirect(stmt, (SQLCHAR *)"SELECT * FROM murid", SQL_NTS);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        printf("Successfully fetched %lld rows\n", rowsFetched);
        char dateBuff[50];
        int i = (int)rowsFetched;
        printf("awikwok %d\n", i);

        SQLGetData(stmt, 1, SQL_C_LONG,
                   &datas->murids[i].id_num, sizeof(datas->murids[i].id_num), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &datas->murids[i].id_murid, sizeof(datas->murids[i].id_murid), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR,
                   &datas->murids[i].nama, sizeof(datas->murids[i].nama), NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR,
                   dateBuff, sizeof(dateBuff), NULL);
        datas->murids[rowsFetched].tanggal_lahir = parseDate(dateBuff);
        SQLGetData(stmt, 5, SQL_C_CHAR,
                   dateBuff, sizeof(dateBuff), NULL);
        datas->murids[rowsFetched].tanggal_masuk = parseDate(dateBuff);
        SQLGetData(stmt, 6, SQL_C_CHAR,
                   &datas->murids[i].no_hp, sizeof(datas->murids[i].no_hp), NULL);
        SQLGetData(stmt, 7, SQL_C_CHAR,
                   &datas->murids[i].password, sizeof(datas->murids[i].password), NULL);
        rowsFetched++;
    }
    datas->nMurid = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

QUERYSTATUS createMurid(data *datas, int *nPage, SQLHDBC *dbConn, Murid newMurid)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"INSERT INTO murid (nama, tanggal_lahir, no_hp, password) VALUES (?,?,?,?)", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newMurid.nama), 0, newMurid.nama, 0, NULL);
    dateBuff = parseDateToString(newMurid.tanggal_lahir);
    printf("date: %s\n", dateBuff);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_DATE, strlen("2028-10-20"), 0, "2028-10-20", 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newMurid.no_hp), 0, newMurid.no_hp, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newMurid.password), 0, newMurid.password, 0, NULL);
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

QUERYSTATUS updateMurid(data *datas, int *nPage, SQLHDBC *dbConn, Murid updatedMurid)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"UPDATE staff SET nama = ?, tanggal_lahir = ?, no_hp = ?, password = ? WHERE id_murid = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMurid.nama), 0, updatedMurid.nama, 0, NULL);
    dateBuff = parseDateToString(updatedMurid.tanggal_lahir);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_DATE, strlen(dateBuff), 0, dateBuff, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMurid.no_hp), 0, updatedMurid.no_hp, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMurid.password), 0, updatedMurid.password, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMurid.id_murid), 0, updatedMurid.id_murid, 0, NULL);
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

QUERYSTATUS deleteMurid(data *datas, int *nPage, SQLHDBC *dbConn, Murid updatedMurid)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"DELETE FROM murid WHERE id_murid = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMurid.id_murid), 0, updatedMurid.id_murid, 0, NULL);
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