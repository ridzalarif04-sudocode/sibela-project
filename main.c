#include "libs/utils.h"
#include "model/model.h"
#include "model/window.h"
#include "update/update.h"
#include "views/drawView.h"
#include "data/staf.h"

int main()
{
    InitWindow(1920, 1080, "Sibela");

    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    ToggleFullscreen();

    Font poppinsMedium = LoadFontEx("assets/fonts/Poppins-Medium.ttf", 224, 0, 250);
    Font poppinsRegular = LoadFontEx("assets/fonts/Poppins-Regular.ttf", 224, 0, 250);
    Font poppinsMediumItalic = LoadFontEx("assets/fonts/Poppins-MediumItalic.ttf", 224, 0, 250);

    SQLHDBC dbConn;
    initSQLConn(&dbConn);
    windowModel defaultWindow = (windowModel){
        .currWindow = LANDINGPAGE,
        .shouldClose = 0,
        .curPos = 0,
        .page = 1,
        .cursorEnabled = 1,
        .selectedPage = -1,
        .dbConn = &dbConn,
        .loginData = {.email = {.charLen = 0, .text = "\0"}, .activeInput = 0}};
    defaultWindow.fontStyle.medium = &poppinsMedium;
    defaultWindow.fontStyle.regular = &poppinsRegular;
    defaultWindow.fontStyle.mediumItalic = &poppinsMediumItalic;
    defaultWindow.datas.page = 1;
    // Image Member
    defaultWindow.members[0].image = LoadTexture("assets/images/member/rayyan.png");
    defaultWindow.members[1].image = LoadTexture("assets/images/member/rasya.png");
    defaultWindow.members[2].image = LoadTexture("assets/images/member/bayu.png");
    defaultWindow.members[3].image = LoadTexture("assets/images/member/rijal.png");
    defaultWindow.members[4].image = LoadTexture("assets/images/member/nabilah.png");
    defaultWindow.dataFetchers.admin[0] = findAllStaff;

    // Logo Sibela
    defaultWindow.images.logo = LoadTexture("assets/images/sibela_Versi2.png");
    // Logo Robot Sibela
    defaultWindow.images.logoRobot = LoadTexture("assets/images/Robot_Sibela.png");

    // findAllStaff(&defaultWindow.datas, defaultWindow.dbConn);
    SetTargetFPS(120);

    while (!WindowShouldClose() && !defaultWindow.shouldClose)
    {
        updateView(&defaultWindow);
        BeginDrawing();
        drawRootView(&defaultWindow);
        EndDrawing();
    }

    disconnectDb(&dbConn);
    UnloadFont(poppinsMedium);
    UnloadFont(poppinsRegular);
    UnloadFont(poppinsMediumItalic);
    UnloadTexture(defaultWindow.images.logo);
    UnloadTexture(defaultWindow.images.logoRobot);
    UnloadTexture(defaultWindow.members[0].image);
    UnloadTexture(defaultWindow.members[1].image);
    UnloadTexture(defaultWindow.members[2].image);
    UnloadTexture(defaultWindow.members[3].image);
    UnloadTexture(defaultWindow.members[4].image);
    CloseWindow();

    return 0;
}
