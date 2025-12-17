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
                       foundRecord.tanggal_lahir, sizeof(foundRecord.tanggal_lahir), NULL);
            SQLGetData(stmt, 5, SQL_C_LONG,
                       &foundRecord.tingkat, sizeof(foundRecord.tingkat), NULL);
            SQLGetData(stmt, 6, SQL_C_CHAR,
                       foundRecord.tanggal_masuk, sizeof(foundRecord.tanggal_masuk), NULL);
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
    int limit = 10;
    int offset = (datas->page - 1) * limit;
    *nPage = (int)ceil((float)count / limit);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"SELECT * FROM murid ORDER BY tanggal_masuk DESC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &limit, 0, NULL);

    ret = SQLExecute(stmt);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        char dateBuff[50];
        int i = (int)rowsFetched;

        SQLGetData(stmt, 1, SQL_C_LONG,
                   &datas->murids[i].id_num, sizeof(datas->murids[i].id_num), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &datas->murids[i].id_murid, sizeof(datas->murids[i].id_murid), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR,
                   &datas->murids[i].nama, sizeof(datas->murids[i].nama), NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR,
                   datas->murids[rowsFetched].tanggal_lahir, sizeof(datas->murids[rowsFetched].tanggal_lahir), NULL);
        SQLGetData(stmt, 5, SQL_C_LONG,
                   &datas->murids[rowsFetched].tingkat, sizeof(datas->murids[rowsFetched].tingkat), NULL);
        SQLGetData(stmt, 6, SQL_C_CHAR,
                   datas->murids[rowsFetched].tanggal_masuk, sizeof(datas->murids[rowsFetched].tanggal_masuk), NULL);
        SQLGetData(stmt, 7, SQL_C_CHAR,
                   &datas->murids[i].no_hp, sizeof(datas->murids[i].no_hp), NULL);
        SQLGetData(stmt, 8, SQL_C_CHAR,
                   &datas->murids[i].password, sizeof(datas->murids[i].password), NULL);
        rowsFetched++;
    }
    datas->nMurid = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

void findAllMuridSelect(Select *selectObject, SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char query[50];

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
    int limit = 10;
    int offset = (selectObject->page - 1) * limit;
    selectObject->nPage = (int)ceil((float)count / limit);
    sprintf(query, "%%%s%%", selectObject->searchQuery);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"SELECT * FROM murid ORDER BY nama ASC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    // SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(query), 0, query, 0, NULL);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &limit, 0, NULL);

    ret = SQLExecute(stmt);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        int i = (int)rowsFetched;

        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &selectObject->Options[i].value, sizeof(selectObject->Options[i].value), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR,
                   &selectObject->Options[i].label, sizeof(selectObject->Options[i].label), NULL);
        rowsFetched++;
    }
    selectObject->nOptions = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

QUERYSTATUS createMurid(InputField fields[], SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    Murid newMurid;

    strcpy(newMurid.nama, fields[1].value.text);
    strcpy(newMurid.tanggal_lahir, fields[2].value.text);
    strcpy(newMurid.no_hp, fields[3].value.text);
    strcpy(newMurid.password, fields[4].value.text);
    newMurid.tingkat = atoi(fields[5].value.text);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"INSERT INTO murid (nama, tanggal_lahir, no_hp, password,  tingkat) VALUES (?,?,?,?,?)", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newMurid.nama), 0, newMurid.nama, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_DATE, strlen(newMurid.tanggal_lahir), 0, newMurid.tanggal_lahir, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newMurid.no_hp), 0, newMurid.no_hp, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newMurid.password), 0, newMurid.password, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &newMurid.tingkat, 0, NULL);
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

QUERYSTATUS updateMurid(InputField fields[], SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    Murid updatedMurid;
    strcpy(updatedMurid.id_murid, fields[0].value.text);
    strcpy(updatedMurid.nama, fields[1].value.text);
    strcpy(updatedMurid.tanggal_lahir, fields[2].value.text);
    strcpy(updatedMurid.no_hp, fields[3].value.text);
    strcpy(updatedMurid.password, fields[4].value.text);
    updatedMurid.tingkat = atoi(fields[5].value.text);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"UPDATE staff SET nama = ?, tanggal_lahir = ?, no_hp = ?, password = ?, tingkat = ? WHERE id_murid = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMurid.nama), 0, updatedMurid.nama, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_DATE, strlen(updatedMurid.tanggal_lahir), 0, updatedMurid.tanggal_lahir, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMurid.no_hp), 0, updatedMurid.no_hp, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMurid.password), 0, updatedMurid.password, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &updatedMurid.tingkat, 0, NULL);
    SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMurid.id_murid), 0, updatedMurid.id_murid, 0, NULL);
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

QUERYSTATUS deleteMurid(SQLHDBC *dbConn, Murid updatedMurid)
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