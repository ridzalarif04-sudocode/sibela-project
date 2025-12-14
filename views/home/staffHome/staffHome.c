#include "staffHome.h"

void drawStaffHome(windowModel *windowM)
{
    Menus opsi[] = {
        (Menus){"Staff", 0},
        (Menus){"Murid", 0},
        (Menus){"Pengajar", 0},
        (Menus){"Ruangan", 0},
        (Menus){"Mata pelajaran", 0},
        (Menus){"Pembayaran", 0},
        (Menus){"Jadwal", 0},
        (Menus){"Log Out", 1},
    };
    int gap = 50;
    int startX = 35;
    int startY = 375;
    DrawRectangle(0, 0, 300, 1080, SECONDARY);
    // DrawTextEx(*windowM->fontStyle.mediumItalic, "SIBELA", (Vector2){50, 64}, 80, 0, SIBELAWHITE);

    // Logo Sibela kiri Atas
    DrawRectangle(0, 0, 300, 200, SIBELAWHITE);
    DrawTextureEx(windowM->images.logo, (Vector2){40, 44}, 0, 0.30, SIBELAWHITE);

    // Logo Robot kiri bawah
    DrawTextureEx(windowM->images.logoRobot, (Vector2){50, 820}, 0, 0.25, SIBELAWHITE);

    for (int i = 0; i < sizeof(opsi) / sizeof(opsi[0]); i++)
    {
        if ((i == windowM->curPos && windowM->cursorEnabled) || (i == windowM->selectedPage && !windowM->cursorEnabled))
            DrawRectangleRounded((Rectangle){.x = startX - 8, .y = startY + i * gap - 7, .width = MeasureTextEx(*windowM->fontStyle.medium, opsi[i].nama, 32, 0).x + 20, .height = 44}, 0.2, 0, SIBELAWHITE);
        DrawTextEx(*windowM->fontStyle.medium, opsi[i].nama, (Vector2){startX, startY + i * gap}, 32, 0, (opsi[i].selected ? DANGER : (i == windowM->curPos && windowM->cursorEnabled) || (i == windowM->selectedPage && !windowM->cursorEnabled) ? SECONDARY
                                                                                                                                                                                                                                                  : SIBELAWHITE));
    }

    if (windowM->activeSubWindow == READ)
    {
        switch (windowM->selectedPage)
        {
        case 0:
            drawStaffRead(windowM);
            break;
        case 2:
            drawPengajarCreate(windowM);
            break;
        case 4:
            drawMapelRead(windowM);
            break;
        default:
            DrawTextEx(*windowM->fontStyle.medium, TextFormat("Halo, %s!", windowM->authUser.nama), (Vector2){300 + 1620 / 2 - MeasureTextEx(*windowM->fontStyle.medium, TextFormat("Halo, %s!", windowM->authUser.nama), 80, 0).x / 2, 90}, 80, 0, SIBELAWHITE);
            break;
        }
    }
    if (windowM->activeSubWindow == CREATE)
    {
        switch (windowM->selectedPage)
        {
        case 0:
            drawStaffCreate(windowM);
            break;
        }
    }
}