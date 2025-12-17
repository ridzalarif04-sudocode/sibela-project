#include "update.h"
#include <math.h>

void drawJadwalUpdate(windowModel *windowM)
{
    int cell_width = 250;
    int cell_height = 50;
    int start_x = 1920 / 2 - 600 + 100;
    int start_y = 1080 / 2 - 300;
    int padding = 5;
    int font_size = 32;
    DrawTextEx(windowM->fontStyle.regular, "UPDATE JADWAL",
               (Vector2){start_x + 390,
                         start_y - 120},
               64, 0,
               SIBELAWHITE);

    windowM->forms.staffPage[windowM->selectedPage].totalPages = (int)ceilf((float)windowM->forms.staffPage[windowM->selectedPage].nField / windowM->forms.staffPage[windowM->selectedPage].fieldPerPage);
    windowM->forms.staffPage[windowM->selectedPage].offset = (windowM->page - 1) * windowM->forms.staffPage[windowM->selectedPage].fieldPerPage + 1;
    windowM->forms.staffPage[windowM->selectedPage].lastIndex = windowM->forms.staffPage[windowM->selectedPage].offset + (windowM->forms.staffPage[windowM->selectedPage].fieldPerPage - 1) > windowM->forms.staffPage[windowM->selectedPage].nField ? windowM->forms.staffPage[windowM->selectedPage].nField : windowM->forms.staffPage[windowM->selectedPage].offset + (windowM->forms.staffPage[windowM->selectedPage].fieldPerPage - 1);

    for (int i = windowM->forms.staffPage[windowM->selectedPage].offset; i <= windowM->forms.staffPage[windowM->selectedPage].lastIndex; i++)
    {
        Rectangle textBox = {
            1920 / 2.0f - 300,
            start_y + 200 + (i - 1 - windowM->forms.staffPage[windowM->selectedPage].offset) * 150,
            600,
            63,
        };
        Rectangle buttonBox = {
            1920 / 2.0f - 80,
            start_y + 200 + (i - 1 - windowM->forms.staffPage[windowM->selectedPage].offset) * 150,
            160,
            67,
        };
        switch (windowM->forms.staffPage[windowM->selectedPage].fields[i].type)
        {
        case LONGTEXTINPUT:
        case NUMERICINPUT:
        case TEXTINPUT:
            DrawTextEx(windowM->fontStyle.medium, windowM->forms.staffPage[windowM->selectedPage].fields[i].label, (Vector2){(int)textBox.x, (int)textBox.y - 44}, 40, 0, SIBELAWHITE);
            DrawRectangleRoundedLines(textBox, 0.3, 0, windowM->curPos == i ? PRIMARY : SIBELAWHITE);
            DrawTextEx(windowM->fontStyle.regular, windowM->forms.staffPage[windowM->selectedPage].fields[i].value.text, (Vector2){(int)textBox.x + 5, (int)textBox.y + 8}, 40, 0, SIBELAWHITE);
            break;

        case BUTTONINPUT:
            if ((windowM->forms.staffPage[windowM->selectedPage].selectedField == -1 && windowM->curPos == i) || windowM->forms.staffPage[windowM->selectedPage].selectedField == i)
            {
                DrawRectangleRounded(buttonBox, 0.3, 0, PRIMARY);
            }
            else
                DrawRectangleRoundedLines(buttonBox, 0.3, 0, SIBELAWHITE);
            DrawTextEx(windowM->fontStyle.medium, windowM->forms.staffPage[windowM->selectedPage].fields[i].label, (Vector2){(int)buttonBox.x + buttonBox.width / 2 - MeasureTextEx(windowM->fontStyle.medium, windowM->forms.staffPage[windowM->selectedPage].fields[i].label, 40, 0).x / 2, (int)buttonBox.y + MeasureTextEx(windowM->fontStyle.medium, windowM->forms.staffPage[windowM->selectedPage].fields[i].label, 40, 0).y / 2 - 8}, 40, 0, SIBELAWHITE);
            break;

        case CUSTOMMODALMULTI:
        case CUSTOMMODAL:
            DrawTextEx(windowM->fontStyle.medium, windowM->forms.staffPage[windowM->selectedPage].fields[i].label, (Vector2){(int)buttonBox.x, (int)buttonBox.y - 45}, 40, 0, SIBELAWHITE);
            if (windowM->curPos == i)
            {
                DrawRectangleRounded(buttonBox, 0.3, 0, PRIMARY);
            }
            else
                DrawRectangleRoundedLines(buttonBox, 0.3, 0, SIBELAWHITE);
            DrawTextEx(windowM->fontStyle.medium, "PILIH", (Vector2){(int)buttonBox.x + buttonBox.width / 2 - MeasureTextEx(windowM->fontStyle.medium, "PILIH", 40, 0).x / 2, (int)buttonBox.y + MeasureTextEx(windowM->fontStyle.medium, "PILIH", 40, 0).y / 2 - 8}, 40, 0, SIBELAWHITE);
            break;
        }
    }
    if (windowM->forms.staffPage[windowM->selectedPage].selectedField >= 0)
    {
        Rectangle ModalBox = (Rectangle){.width = 800, .height = 600, .x = 300 + 1620 / 2 - 400, .y = 1080 / 2 - 300};
        DrawRectangleRounded(ModalBox, 0.3, 0, SECONDARY);
        for (int i = 0; i < windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].nOptions; i++)
        {
            SelectProp props = windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].Options[i];
            char *text = TextFormat("%d. %s", (windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].page - 1) * 10 + i + 1, props.label);
            Vector2 textMeasure = MeasureTextEx(windowM->fontStyle.regular, text, 25, 0);
            int padding = 40;
            Rectangle selectbg = (Rectangle){.width = 10 + textMeasure.x, .height = 4 + textMeasure.y, .x = (int)ModalBox.x + padding - 5, (int)ModalBox.y + padding + i * 40 - 2};

            if (windowM->curPos == i)
                DrawRectangleRounded(selectbg, 0.3, 0, PRIMARY);

            switch (windowM->forms.staffPage[windowM->selectedPage].fields[windowM->forms.staffPage[windowM->selectedPage].selectedField].type)
            {
            case CUSTOMMODALMULTI:
                if (isOptionInMultiSelected(props, windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].MultiSelected, sizeof(windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].MultiSelected) / sizeof(windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].MultiSelected[0])))
                    DrawCircle(ModalBox.x + padding + textMeasure.x + 20, (int)ModalBox.y + padding + i * 40 + textMeasure.y / 2, 8, GREEN);
                break;
            case CUSTOMMODAL:
                if (TextIsEqual(props.value, windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].selected.value))
                    DrawCircle(ModalBox.x + padding + textMeasure.x + 20, (int)ModalBox.y + padding + i * 40 + textMeasure.y / 2, 8, GREEN);
                break;
            }

            DrawTextEx(windowM->fontStyle.regular, text, (Vector2){(int)ModalBox.x + padding, (int)ModalBox.y + padding + i * 40}, 25, 0, SIBELAWHITE);
        }
        DrawTextEx(windowM->fontStyle.medium, TextFormat("Halaman %d dari %d", windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].page, windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].nPage), (Vector2){(int)ModalBox.x + ModalBox.width / 2 - 100, (int)ModalBox.y + ModalBox.height - 60}, 40, 0, SIBELAWHITE);
    }
}