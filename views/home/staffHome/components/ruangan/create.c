#include "create.h"
#include <math.h>

void drawRuanganCreate(windowModel *windowM)
{
    int cell_width = 250;
    int cell_height = 50;
    int start_x = 1920 / 2 - 600 + 100;
    int start_y = 1080 / 2 - 300;
    int padding = 5;
    int font_size = 32;
    DrawTextEx(*windowM->fontStyle.regular, "CREATE RUANGAN",
               (Vector2){start_x + 390,
                         start_y - 120},
               64, 0,
               SIBELAWHITE);

    windowM->forms[windowM->selectedPage].totalPages = (int)ceilf((float)windowM->forms[windowM->selectedPage].nField / windowM->forms[windowM->selectedPage].fieldPerPage);
    windowM->forms[windowM->selectedPage].offset = (windowM->page - 1) * windowM->forms[windowM->selectedPage].fieldPerPage + 1;
    windowM->forms[windowM->selectedPage].lastIndex = windowM->forms[windowM->selectedPage].offset + (windowM->forms[windowM->selectedPage].fieldPerPage - 1) > windowM->forms[windowM->selectedPage].nField ? windowM->forms[windowM->selectedPage].nField : windowM->forms[windowM->selectedPage].offset + (windowM->forms[windowM->selectedPage].fieldPerPage - 1);

    for (int i = windowM->forms[windowM->selectedPage].offset; i <= windowM->forms[windowM->selectedPage].lastIndex; i++)
    {
        Rectangle textBox = {
            1920 / 2.0f - 300,
            start_y + 100 + (i - 1 - windowM->forms[windowM->selectedPage].offset) * 150,
            600,
            63,
        };
        Rectangle buttonBox = {
            1920 / 2.0f - 80,
            start_y + 100 + (i - 1 - windowM->forms[windowM->selectedPage].offset) * 150,
            160,
            67,
        };
        switch (windowM->forms[windowM->selectedPage].fields[i].type)
        {
        case TEXTINPUT:
            DrawTextEx(*windowM->fontStyle.medium, windowM->forms[windowM->selectedPage].fields[i].label, (Vector2){(int)textBox.x, (int)textBox.y - 44}, 40, 0, SIBELAWHITE);
            DrawRectangleRoundedLines(textBox, 0.3, 0, windowM->curPos == i ? PRIMARY : SIBELAWHITE);
            DrawTextEx(*windowM->fontStyle.regular, windowM->forms[windowM->selectedPage].fields[i].value.text, (Vector2){(int)textBox.x + 5, (int)textBox.y + 8}, 40, 0, SIBELAWHITE);
            break;

        case BUTTONINPUT:
            if (windowM->curPos == i)
            {
                DrawRectangleRounded(buttonBox, 0.3, 0, PRIMARY);
            }
            else
                DrawRectangleRoundedLines(buttonBox, 0.3, 0, SIBELAWHITE);
            DrawTextEx(*windowM->fontStyle.medium, windowM->forms[windowM->selectedPage].fields[i].label, (Vector2){(int)buttonBox.x + MeasureTextEx(*windowM->fontStyle.medium, windowM->forms[windowM->selectedPage].fields[i].label, 40, 0).x / 2, (int)buttonBox.y + MeasureTextEx(*windowM->fontStyle.medium, "Login", 40, 0).y / 2 - 8}, 40, 0, SIBELAWHITE);
            break;
        }
    }
}