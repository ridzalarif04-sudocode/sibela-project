#include "read.h"
#include "../../../../../libs/headers/raygui.h"

void drawRuanganRead(windowModel *windowM)
{
    int cell_width = 250;
    int cell_height = 50;
    int start_x = 1920 / 2 - 600 + 100;
    int start_y = 1080 / 2 - 300;
    int padding = 5;
    int font_size = 32;
    DrawTextEx(*windowM->fontStyle.regular, "DATA RUANGAN",
               (Vector2){start_x + 390,
                         start_y - 120},
               64, 0,
               SIBELAWHITE);
    for (int col = 0; col < 3; col++)
    {
        Rectangle cellRect = {
            start_x + col * cell_width,
            start_y - cell_height,
            cell_width,
            cell_height};
        DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
        DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
    }
    DrawTextEx(*windowM->fontStyle.regular, "id",
               (Vector2){start_x + 0 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(*windowM->fontStyle.regular, "Lokasi",
               (Vector2){start_x + 1 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);
    DrawTextEx(*windowM->fontStyle.regular, "Deskripsi",
               (Vector2){start_x + 2 * cell_width + padding,
                         start_y - cell_height + padding},
               font_size, 0,
               SIBELAWHITE);

    for (int row = 0; row < windowM->datas.nRuangan; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            Rectangle cellRect = {
                start_x + col * cell_width,
                start_y + row * cell_height,
                cell_width,
                cell_height};
            if (row == windowM->curPos)
            {
                windowM->focusedData.ruangan = windowM->datas.ruangans[row];
                DrawRectangleRec(cellRect, PRIMARY);
            }
            DrawRectangleLinesEx(cellRect, 1, SIBELAWHITE);
        }
        DrawTextEx(*windowM->fontStyle.regular, windowM->datas.ruangans[row].id_ruangan,
                   (Vector2){start_x + 0 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(*windowM->fontStyle.regular, windowM->datas.ruangans[row].lokasi,
                   (Vector2){start_x + 1 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
        DrawTextEx(*windowM->fontStyle.regular, windowM->datas.ruangans[row].deskripsi,
                   (Vector2){start_x + 2 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   SIBELAWHITE);
    }
    DrawTextEx(*windowM->fontStyle.regular, TextFormat("Halaman %d dari %d", windowM->datas.page, windowM->datas.totalPages),
               (Vector2){300 + (1620 / 2 - 30),
                         1000},
               40, 0,
               SIBELAWHITE);
    if (windowM->isModalShown)
    {
        int res = GuiMessageBox((Rectangle){.height = 200, .width = 300, .x = 1920 / 2 - 150, .y = 1080 / 2 - 300}, "Delete Ruangan?", TextFormat("Apakah anda ingin menghapus Ruangan %s?", windowM->focusedData.ruangan.id_ruangan), "Batal;Hapus!");

        if (res == 2)
        {
            deleteRuangan(windowM->dbConn, windowM->focusedData.ruangan);
            windowM->dataFetchers.admin[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
            windowM->isModalShown = 0;
        }
        else if (res >= 0 && res < 2)
            windowM->isModalShown = 0;
    }
}