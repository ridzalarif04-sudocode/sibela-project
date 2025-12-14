#include "pengajarHome.h"

void drawPengajarHome(windowModel *windowM)
{
    Menus opsi[] = {
        (Menus){"Absensi", 0},
        (Menus){"Pertemuan", 0},
        (Menus){"Materi", 0},
        (Menus){"Log out", 1},
    };
    int gap = 50;
    int startX = 35;
    int startY = 375;
    DrawRectangle(0, 0, 300, 1080, SECONDARY);

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

    int cell_width = 250;
    int cell_height = 50;
    int start_x = 1920 / 2 - 600 + 100;
    int start_y = 1080 / 2 - 300;
    int padding = 5;
    int font_size = 32;
    switch (windowM->selectedPage)
    {
    case 0:

        DrawTextEx(*windowM->fontStyle.regular, "Absensi",
                   (Vector2){start_x + 390,
                             start_y - 120},
                   64, 0,
                   SIBELAWHITE);
        for (int col = 0; col < 4; col++)
        {
            Rectangle cellRect = {
                start_x + col * cell_width,
                start_y - cell_height,
                cell_width,
                cell_height};
            DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
            DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
        }
        DrawTextEx(*windowM->fontStyle.regular, "Kelas",
                   (Vector2){start_x + 0 * cell_width + padding,
                             start_y - cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(*windowM->fontStyle.regular, "Siswa",
                   (Vector2){start_x + 1 * cell_width + padding,
                             start_y - cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(*windowM->fontStyle.regular, "Status",
                   (Vector2){start_x + 2 * cell_width + padding,
                             start_y - cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(*windowM->fontStyle.regular, "Tanggal",
                   (Vector2){start_x + 3 * cell_width + padding,
                             start_y - cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        break;
    default:
        DrawTextEx(*windowM->fontStyle.medium, TextFormat("Halo, %s!", windowM->authUser.nama), (Vector2){300 + 1620 / 2 - MeasureTextEx(*windowM->fontStyle.medium, TextFormat("Halo, %s!", windowM->authUser.nama), 80, 0).x / 2, 90}, 80, 0, SIBELAWHITE);
        break;
    }
}