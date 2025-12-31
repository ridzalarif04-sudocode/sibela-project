#ifndef window
#define window

#include "model.h"
#include "../types/dbTypes.h"
#include "../types/form.h"
#include "../libs/headers/raylib.h"
#include "../data/staf.h"
#include "../data/mapel.h"
#include "../data/ruangan.h"
#include "../data/murid.h"
#include "../data/pengajar.h"
#include "../data/materi.h"
#include "../data/jadwalPertemuan.h"
#define MAX_LEGEND 10

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

typedef struct {
    const char *key;
    const char *desc;
} LegendItem;

typedef struct
{
    InputParams email;
    InputParams phoneNumber;
    InputParams password;
    int activeInput;
} LoginScreen;

typedef struct
{
    Font regular;
    Font medium;
    Font mediumItalic;
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

typedef void (*authFetcher)(data *datas, int *nPage, SQLHDBC *dbConn, user authUser);
typedef void (*fetcherFunc)(data *datas, int *nPage, SQLHDBC *dbConn);

typedef struct
{
    fetcherFunc staffPage[10];
    fetcherFunc pengajarPage[10];
    authFetcher muridPage[10];
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
    Select pengajarPage[10];
    Select (*staffPage)[6];
} SelectByPage;

typedef struct
{
    Staf staff;
    Murid murid;
    Pengajar pengajar;
    Mapel mapel;
    Ruangan ruangan;
    Materi materi;
    JadwalPertemuanWithDetails jadwal;
} FocusedData;

typedef struct
{
    FORM staffPage[10];
    FORM pengajarPage[10];
} FORMBYPAGE;

typedef struct
{
    SelectByPage selectByPage;
    WINDOWS currWindow;
    int shouldClose;
    int curPos;
    int isModalShown;
    int activeSubWindow;
    int selectedPage;
    int cursorEnabled;
    SQLHDBC *dbConn;
    FocusedData focusedData;
    FontStyles fontStyle;
    ascii asciis;
    image images;
    Member members[5];
    data datas;
    int page;
    FORMBYPAGE forms;
    PageNav navigation;
    user authUser;
    fetcher dataFetchers;
    LoginScreen loginData;
    bool isLoading;
    float loadingTime;
    float progress;
    LegendItem legends[MAX_LEGEND];
} windowModel;

void initForm(windowModel *windowM);
void initAssets(windowModel *windowM);
void initWindow(windowModel *windowM);
void unloadAssets(windowModel *windowM);

#endif