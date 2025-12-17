#include "jadwalPertemuan.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void findAllJadwalPertemuan(data *datas, int *nPage, SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLLEN rowsFetched = 0;
    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    ret = SQLExecDirect(stmt, (SQLCHAR *)"SELECT COUNT(*) AS row_count FROM jadwal_pertemuan", SQL_NTS);
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
    SQLPrepare(stmt, (SQLCHAR *)"SELECT j.id_num, j.id_pertemuan, s.nama AS nama_staff, p.nama AS nama_pengajar,r.lokasi,m.judul_materi, (SELECT COUNT(*) FROM jadwal_murid WHERE jadwal_murid.id_pertemuan = j.id_pertemuan) AS jumlah_murid,j.waktu, s.id_staff, p.id_pengajar, r.id_ruangan, m.id_materi FROM jadwal_pertemuan j, staff s, pengajar p, ruangan r, materi m WHERE s.id_staff = j.id_staff AND p.id_pengajar = j.id_pengajar AND r.id_ruangan = j.id_ruangan AND m.id_materi = j.id_materi ORDER BY j.waktu DESC OFFSET ? ROWS FETCH NEXT ? ROWS ONLY", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &offset, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &limit, 0, NULL);

    ret = SQLExecute(stmt);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        char dateBuff[50];
        int i = (int)rowsFetched;
        datas->jadwalPertemuans[i].jumlah_murid = 0;

        SQLGetData(stmt, 1, SQL_C_LONG,
                   &datas->jadwalPertemuans[i].id_num, sizeof(datas->jadwalPertemuans[i].id_num), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].id_pertemuan, sizeof(datas->jadwalPertemuans[i].id_pertemuan), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].nama_staff, sizeof(datas->jadwalPertemuans[i].nama_staff), NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR,
                   datas->jadwalPertemuans[rowsFetched].nama_pengajar, sizeof(datas->jadwalPertemuans[rowsFetched].nama_pengajar), NULL);
        SQLGetData(stmt, 5, SQL_C_LONG,
                   &datas->jadwalPertemuans[rowsFetched].lokasi, sizeof(datas->jadwalPertemuans[rowsFetched].lokasi), NULL);
        SQLGetData(stmt, 6, SQL_C_CHAR,
                   datas->jadwalPertemuans[rowsFetched].judul_materi, sizeof(datas->jadwalPertemuans[rowsFetched].judul_materi), NULL);
        SQLGetData(stmt, 7, SQL_C_LONG,
                   &datas->jadwalPertemuans[i].jumlah_murid, sizeof(datas->jadwalPertemuans[i].jumlah_murid), NULL);
        SQLGetData(stmt, 8, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].waktu, sizeof(datas->jadwalPertemuans[i].waktu), NULL);
        SQLGetData(stmt, 9, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].id_staff, sizeof(datas->jadwalPertemuans[i].id_staff), NULL);
        SQLGetData(stmt, 10, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].id_pengajar, sizeof(datas->jadwalPertemuans[i].id_pengajar), NULL);
        SQLGetData(stmt, 11, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].id_ruangan, sizeof(datas->jadwalPertemuans[i].id_ruangan), NULL);
        SQLGetData(stmt, 12, SQL_C_CHAR,
                   &datas->jadwalPertemuans[i].id_materi, sizeof(datas->jadwalPertemuans[i].id_materi), NULL);
        rowsFetched++;
    }
    datas->nJadwalPertemuan = rowsFetched;
    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);
}

QUERYSTATUS createJadwalPertemuan(InputField fields[], SQLHDBC *dbConn)
{
    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;
    SQLLEN idind;

    JadwalPertemuan newJadwalPertemuan;

    strcpy(newJadwalPertemuan.id_staff, fields[1].value.text);
    strcpy(newJadwalPertemuan.id_pengajar, fields[2].value.text);
    strcpy(newJadwalPertemuan.id_ruangan, fields[3].value.text);
    strcpy(newJadwalPertemuan.id_materi, fields[4].value.text);
    strcpy(newJadwalPertemuan.waktu, fields[5].value.text);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"INSERT INTO jadwal_pertemuan (id_staff, id_pengajar, id_ruangan,id_materi,waktu) OUTPUT inserted.id_pertemuan VALUES (?,?,?,?,?)", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newJadwalPertemuan.id_staff), 0, newJadwalPertemuan.id_staff, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newJadwalPertemuan.id_pengajar), 0, newJadwalPertemuan.id_pengajar, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newJadwalPertemuan.id_ruangan), 0, newJadwalPertemuan.id_ruangan, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newJadwalPertemuan.id_materi), 0, newJadwalPertemuan.id_materi, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(newJadwalPertemuan.waktu), 0, newJadwalPertemuan.waktu, 0, NULL);
    ret = SQLExecute(stmt);

    SQLBindCol(stmt, 1, SQL_C_CHAR, newJadwalPertemuan.id_pertemuan, sizeof(newJadwalPertemuan.id_pertemuan), &idind);
    if (SQL_SUCCEEDED(ret))
    {
        ret = SQLFetch(stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);

    createJadwalMurid(fields[6].value, newJadwalPertemuan.id_pertemuan, dbConn);

    switch (ret)
    {
    case SQL_SUCCESS:
        return SUCCESS;

    default:
        return FAILED;
    }
}

QUERYSTATUS updateJadwalPertemuan(InputField fields[], SQLHDBC *dbConn)
{
    deleteteJadwalMuridByPertemuanID(fields[0].value.text, dbConn);

    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];
    char *dateBuff;

    JadwalPertemuan updatedJadwalPertemuan;

    strcpy(updatedJadwalPertemuan.id_pertemuan, fields[0].value.text);
    strcpy(updatedJadwalPertemuan.id_staff, fields[1].value.text);
    strcpy(updatedJadwalPertemuan.id_pengajar, fields[2].value.text);
    strcpy(updatedJadwalPertemuan.id_ruangan, fields[3].value.text);
    strcpy(updatedJadwalPertemuan.id_materi, fields[4].value.text);
    strcpy(updatedJadwalPertemuan.waktu, fields[5].value.text);

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"UPDATE jadwal_pertemuan id_staff = ?, id_pengajar = ?, id_ruangan = ?, id_materi = ?, waktu = ? WHERE id_pertemuan = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedJadwalPertemuan.id_staff), 0, updatedJadwalPertemuan.id_staff, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedJadwalPertemuan.id_pengajar), 0, updatedJadwalPertemuan.id_pengajar, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedJadwalPertemuan.id_ruangan), 0, updatedJadwalPertemuan.id_ruangan, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedJadwalPertemuan.id_materi), 0, updatedJadwalPertemuan.id_materi, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedJadwalPertemuan.waktu), 0, updatedJadwalPertemuan.waktu, 0, NULL);
    SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedJadwalPertemuan.id_pertemuan), 0, updatedJadwalPertemuan.id_pertemuan, 0, NULL);
    ret = SQLExecute(stmt);

    if (SQL_SUCCEEDED(ret))
    {
        ret = SQLFetch(stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, *dbConn);

    createJadwalMurid(fields[6].value, updatedJadwalPertemuan.id_pertemuan, dbConn);

    switch (ret)
    {
    case SQL_SUCCESS:
        return SUCCESS;

    default:
        return FAILED;
    }
}

QUERYSTATUS deleteJadwalPertemuan(SQLHDBC *dbConn, JadwalPertemuanWithDetails updatedPertemuan)
{
    deleteteJadwalMuridByPertemuanID(updatedPertemuan.id_pertemuan, dbConn);

    SQLHSTMT stmt;
    SQLRETURN ret;
    int count;
    SQLUSMALLINT rowStatus[100];

    SQLAllocHandle(SQL_HANDLE_STMT, *dbConn, &stmt);
    SQLPrepare(stmt, (SQLCHAR *)"DELETE FROM jadwal_pertemuan WHERE id_pertemuan = ?", SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(updatedPertemuan.id_pertemuan), 0, updatedPertemuan.id_pertemuan, 0, NULL);
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