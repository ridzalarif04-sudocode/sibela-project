#include "homeView.h"

void drawHome(windowModel *windowM)
{
    int cell_width = 200;
    int cell_height = 50;
    int start_x = 1920 / 2 - 400;
    int start_y = 1080 / 2 - 300;
    int padding = 5;
    int font_size = 45;

    for (int row = 0; row < windowM->datas.nStaf; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            Rectangle cellRect = {
                start_x + col * cell_width,
                start_y + row * cell_height,
                cell_width,
                cell_height};
            DrawRectangleLinesEx(cellRect, 1, WHITE); // Draw cell border
        }
        // DrawTextEx(*windowM->font, windowM->datas.staffs[row].id_num,
        //            (Vector2){start_x + 1 * cell_width + padding,
        //                      start_y + row * cell_height + padding},
        //            font_size, 0,
        //            WHITE);
        DrawTextEx(*windowM->font, windowM->datas.staffs[row].id_staff,
                   (Vector2){start_x + 1 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   WHITE);
        DrawTextEx(*windowM->font, windowM->datas.staffs[row].role,
                   (Vector2){start_x + 2 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   WHITE);
        DrawTextEx(*windowM->font, windowM->datas.staffs[row].nama,
                   (Vector2){start_x + 3 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   WHITE);
        DrawTextEx(*windowM->font, windowM->datas.staffs[row].no_hp,
                   (Vector2){start_x + 4 * cell_width + padding,
                             start_y + row * cell_height + padding},
                   font_size, 0,
                   WHITE);
    }
    // DrawTextEx(*windowM->font, "ID\taw\tyes", (Vector2){1920 / 2, 1080 / 2 - 100}, 120, 0, WHITE);
    ClearBackground((Color){51, 51, 50});
}
