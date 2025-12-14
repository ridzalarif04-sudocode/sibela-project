#ifndef window
#define window

#include "model.h"
#include "../types/dbTypes.h"
#include "../types/form.h"
#include "../libs/headers/raylib.h"

typedef enum
{
    STAFHOME,
    MURIDHOME,
    PENGAJARHOME,
    LOGINSTAFF,
    LOGINMURID,
    LOGINPENGAJAR,
    ADMINSTUDENT,
    LANDINGPAGE,
    CONTRIBPAGE
} WINDOWS;

typedef enum
{
    READ,
    CREATE,
    UPDATE,
} SUBWINDOW;

typedef struct
{
    char nama[50];
    int selected;
} Menus;

typedef struct
{
    char nama[50];
    int targetPage;
} NavMenus;

typedef struct
{
    InputParams email;
    InputParams phoneNumber;
    InputParams password;
    int activeInput;
} LoginScreen;

typedef struct
{
    Font *regular;
    Font *medium;
    Font *mediumItalic;
} FontStyles;

typedef struct
{
    char logo[1024];
} ascii;
typedef struct
{
    Texture2D logo;
    Texture2D logoRobot;
} image;

typedef struct
{
    char id[20];
    char nama[100];
    char role[20];
} user;

typedef void (*fetcherAdmin)(data *datas, int *nPage, SQLHDBC *dbConn);

typedef struct
{
    fetcherAdmin admin[10];
} fetcher;

typedef struct
{
    NavMenus landingPage[10];
} PageNav;

typedef struct
{
    char nama[50];
    Texture2D image;
    char nim[20];
    char tanggalLahir[20];
    char domisili[15];
    char julukan[50];
} Member;

typedef struct
{
    WINDOWS currWindow;
    int shouldClose;
    int curPos;
    int isModalShown;
    int activeSubWindow;
    int selectedPage;
    int cursorEnabled;
    SQLHDBC *dbConn;
    FontStyles fontStyle;
    ascii asciis;
    image images;
    Member members[5];
    data datas;
    int page;
    FORM forms[10];
    PageNav navigation;
    user authUser;
    fetcher dataFetchers;
    LoginScreen loginData;
    bool isLoading;
    float loadingTime;
    float progress;
} windowModel;

#endif