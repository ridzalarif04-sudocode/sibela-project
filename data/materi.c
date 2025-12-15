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

    if (datas->nMateri > 0)
        return;

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
    printf("awikwok %d\n", *nPage);
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    ret = SQLExecDirect(stmt, (SQLCHAR *)"SELECT * FROM materi WHERE id_materi", SQL_NTS);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        printf("Successfully fetched %lld rows\n", rowsFetched);
        char dateBuff[50];
        int i = (int)rowsFetched;
        printf("awikwok %d\n", i);

        SQLGetData(stmt, 1, SQL_C_LONG,
                   &datas->materis[i].id_num, sizeof(datas->materis[i].id_num), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &datas->materis[i].id_materi, sizeof(datas->materis[i].id_materi), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR,
                   &datas->materis[i].id_mapel, sizeof(datas->materis[i].id_mapel), NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR,
                   &datas->materis[i].judul_materi, sizeof(datas->materis[i].judul_materi), NULL);
        SQLGetData(stmt, 5, SQL_C_CHAR,
                   &datas->materis[i].isi_materi, sizeof(datas->materis[i].isi_materi), NULL);
        printf("materi %d: %s\n", i, datas->materis[i].isi_materi);
        rowsFetched++;
    }
    datas->nStaf = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

QUERYSTATUS createStaff(data *datas, int *nPage, SQLHDBC *dbConn, Staf newStaff)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"INSERT INTO staff (isi_materi, tanggal_lahir, no_hp, password, email) VALUES (?,?,?,?,?)", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newStaff.isi_materi), 0, newStaff.isi_materi, 0, NULL);
    dateBuff = parseDateToString(newStaff.tanggal_lahir);
    printf("date: %s\n", dateBuff);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_DATE, strlen("2028-10-20"), 0, "2028-10-20", 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newStaff.no_hp), 0, newStaff.no_hp, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newStaff.password), 0, newStaff.password, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newStaff.email), 0, newStaff.email, 0, NULL);
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

QUERYSTATUS updateStaff(data *datas, int *nPage, SQLHDBC *dbConn, Staf updatedStaff)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"UPDATE staff SET isi_materi = ?, tanggal_lahir = ?, no_hp = ?, password = ?, email = ? WHERE id_materi = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedStaff.isi_materi), 0, updatedStaff.isi_materi, 0, NULL);
    dateBuff = parseDateToString(updatedStaff.tanggal_lahir);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_DATE, strlen(dateBuff), 0, dateBuff, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedStaff.no_hp), 0, updatedStaff.no_hp, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedStaff.password), 0, updatedStaff.password, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedStaff.email), 0, updatedStaff.email, 0, NULL);
    SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedStaff.id_materi), 0, updatedStaff.id_materi, 0, NULL);
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

QUERYSTATUS deleteStaff(data *datas, int *nPage, SQLHDBC *dbConn, Staf updatedStaff)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"DELETE FROM staff WHERE id_materi = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedStaff.id_materi), 0, updatedStaff.id_materi, 0, NULL);
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