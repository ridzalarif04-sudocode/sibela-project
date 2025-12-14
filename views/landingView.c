#include "landingView.h"

void drawLandingPage(windowModel *windowM)
{
    Rectangle box = {.height = 250, .width = 300, .x = 1920 / 2 - 300 / 2, .y = 1080 - 450};
    int gap = 54;
    windowM->navigation.landingPage[0] = (NavMenus){.nama = "Masuk Staff", .targetPage = LOGINSTAFF};
    windowM->navigation.landingPage[1] = (NavMenus){.nama = "Masuk Murid", .targetPage = LOGINMURID};
    windowM->navigation.landingPage[2] = (NavMenus){.nama = "Masuk Pengajar", .targetPage = LOGINPENGAJAR};
    windowM->navigation.landingPage[3] = (NavMenus){.nama = "Pembuat", .targetPage = CONTRIBPAGE};

    DrawRectangleLinesEx(box, 2, SIBELAWHITE);

    for (int i = 0; i < 4; i++)
    {
        Vector2 TextSize = MeasureTextEx(*windowM->fontStyle.regular, windowM->navigation.landingPage[i].nama, 40, 0);
        Vector2 Position = {.x = box.x + box.width / 2 - TextSize.x / 2, .y = box.y + 24 + i * gap};
        Rectangle highlightBox = {.height = TextSize.y + 8, .width = TextSize.x + 10, .x = Position.x - 5, .y = Position.y - 4};
        if (windowM->curPos == i)
        {
            DrawRectangleRounded(highlightBox, 0.35, 0, PRIMARY);
        }
        DrawTextEx(*windowM->fontStyle.regular, windowM->navigation.landingPage[i].nama, Position, 40, 0, SIBELAWHITE);
    }
}