#include "libs/utils.h"
#include "model/model.h"
#include "model/window.h"
#include "update/update.h"
#include "views/drawView.h"
#include "views/Loading.h"

int main()
{
    InitWindow(1920, 1080, "Sibela");

    ToggleFullscreen();

    SQLHDBC dbConn;
    initSQLConn(&dbConn);
    windowModel defaultWindow;
    initWindow(&defaultWindow);

    defaultWindow.dbConn = &dbConn;

    SetTargetFPS(120);

    while (!WindowShouldClose() && !defaultWindow.shouldClose)
    {
        updateView(&defaultWindow);
        BeginDrawing();
        drawRootView(&defaultWindow);
        EndDrawing();
    }

    disconnectDb(&dbConn);
    unloadAssets(&defaultWindow);
    CloseWindow();

    return 0;
}
