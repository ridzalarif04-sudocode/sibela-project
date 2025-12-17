#include "materi.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void findAllMateri(data *datas, int *nPage, SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLLEN rowsFetched = 0;
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    ret = SQLExecDirect(stmt, (SQLCHAR *)"SELECT COUNT(*) AS row_count FROM materi", SQL_NTS);
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
    SQLPrepare(stmt, (SQLCHAR *)"SELECT m.id_num, id_materi, m.id_mapel, map.nama_mapel, judul_materi, isi_materi  FROM materi m, mapel map WHERE map.id_mapel = m.id_mapel ORDER BY id_materi DESC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &limit, 0, NULL);

    ret = SQLExecute(stmt);

    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        char dateBuff[50];
        int i = (int)rowsFetched;

        SQLGetData(stmt, 1, SQL_C_LONG,
                   &datas->Materis[i].id_num, sizeof(datas->Materis[i].id_num), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &datas->Materis[i].id_materi, sizeof(datas->Materis[i].id_materi), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR,
                   &datas->Materis[i].id_mapel, sizeof(datas->Materis[i].id_mapel), NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR,
                   &datas->Materis[i].nama_mapel, sizeof(datas->Materis[i].nama_mapel), NULL);
        SQLGetData(stmt, 5, SQL_C_CHAR,
                   &datas->Materis[i].judul_materi, sizeof(datas->Materis[i].judul_materi), NULL);
        SQLGetData(stmt, 6, SQL_C_CHAR,
                   &datas->Materis[i].isi_materi, sizeof(datas->Materis[i].isi_materi), NULL);
        rowsFetched++;
    }
    datas->nMateri = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

void findAllMateriSelect(Select *selectObject, SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char query[50];

    SQLLEN rowsFetched = 0;
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    ret = SQLExecDirect(stmt, (SQLCHAR *)"SELECT COUNT(*) AS row_count FROM materi", SQL_NTS);
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
    SQLPrepare(stmt, (SQLCHAR *)"SELECT * FROM materi ORDER BY judul_materi ASC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    // SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(query), 0, query, 0, NULL);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &limit, 0, NULL);

    ret = SQLExecute(stmt);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        char dateBuff[50];
        int i = (int)rowsFetched;

        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &selectObject->Options[i].value, sizeof(selectObject->Options[i].value), NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR,
                   &selectObject->Options[i].label, sizeof(selectObject->Options[i].label), NULL);
        rowsFetched++;
    }
    selectObject->nOptions = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

QUERYSTATUS createMateri(InputField fields[], SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    Materi newMateri;

    strcpy(newMateri.id_mapel, fields[1].value.text);
    strcpy(newMateri.judul_materi, fields[2].value.text);
    strcpy(newMateri.isi_materi, fields[3].value.text);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"INSERT INTO materi (id_mapel, judul_materi, isi_materi) VALUES (?,?,?)", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newMateri.id_mapel), 0, newMateri.id_mapel, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newMateri.judul_materi), 0, newMateri.judul_materi, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newMateri.isi_materi), 0, newMateri.isi_materi, 0, NULL);
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

QUERYSTATUS updateMateri(InputField fields[], SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    Materi updatedMateri;

    strcpy(updatedMateri.id_materi, fields[0].value.text);
    strcpy(updatedMateri.id_mapel, fields[1].value.text);
    strcpy(updatedMateri.judul_materi, fields[2].value.text);
    strcpy(updatedMateri.isi_materi, fields[3].value.text);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"UPDATE materi SET judul_materi = ?, isi_materi = ?, id_mapel = ? WHERE id_materi = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMateri.judul_materi), 0, updatedMateri.judul_materi, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMateri.isi_materi), 0, updatedMateri.isi_materi, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMateri.id_mapel), 0, updatedMateri.id_mapel, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMateri.id_materi), 0, updatedMateri.id_materi, 0, NULL);
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

QUERYSTATUS deleteMateri(SQLHDBC *dbConn, Materi updatedMateri)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"DELETE FROM materi WHERE id_materi = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedMateri.id_materi), 0, updatedMateri.id_materi, 0, NULL);
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