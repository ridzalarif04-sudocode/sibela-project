#ifndef dbTypes
#define dbTypes

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <time.h>
// #include "../model/model.h"

typedef enum
{
    X,
    XI,
    XII
} tingkat_enum;
typedef enum
{
    MANAJER,
    FRONTDESK
} staf_role_enum;

typedef struct
{
    int id_num;
    char id_murid[7];
    char nama[101];
    char tanggal_lahir[20];
    int tingkat;
    char tanggal_masuk[20];
    char no_hp[16];
    char password[101];
} Murid;

typedef struct
{
    int id_num;
    char id_pengajar[8];
    char nama[101];
    char tanggal_lahir[20];
    char tanggal_masuk[20];
    char no_hp[16];
    char password[101];
} Pengajar;

typedef struct
{
    int id_num;
    char id_staff[30];
    char role[20];
    char nama[255];
    char tanggal_lahir[20];
    char tanggal_masuk[20];
    char no_hp[20];
    char password[100];
    char email[100];
} Staf;

typedef struct
{
    int id_num;
    char id_ruangan[7];
    char lokasi[101];
    char deskripsi[101];
} Ruangan;

typedef struct
{
    int id_num;
    char id_mapel[7];
    char nama_mapel[101];
} Mapel;

// typedef struct
//     {
//         SQLINTEGER id_num;
//         SQLVARCHAR id_staff;
//         SQLVARCHAR role;
//         SQLVARCHAR nama;
//         SQLDATE tanggal_lahir;
//         SQLINTEGER tingat;
//         SQLDATE tanggal_masuk;
//         SQLVARCHAR no_hp;
//         SQLVARCHAR password;
//     } stafSQL;

#endif