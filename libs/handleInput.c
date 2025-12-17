#include "handleInput.h"

void handleInput(int *ch, int *destLen, char destText[], InputType fieldType, int maxLen, mutationFunc func, InputField fields[], fetcherFunc dataFetcher, windowModel *windowM)
{

    switch (fieldType)
    {
    case LONGTEXTINPUT:
    case TEXTINPUT:
        *ch = GetCharPressed();
        while (*ch > 0)
        {
            if ((*ch >= 32) && (*ch <= 125) && (*destLen < maxLen))
            {
                destText[*destLen] = (char)*ch;
                destText[(*destLen) + 1] = '\0';
                (*destLen)++;
            }

            *ch = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            (*destLen)--;
            if ((*destLen) < 0)
                (*destLen) = 0;
            destText[*destLen] = '\0';
        }
        break;
    case NUMERICINPUT:
        *ch = GetCharPressed();
        while (*ch > 0)
        {
            if ((*ch >= '0') && (*ch <= '9') && (*destLen < maxLen))
            {
                destText[*destLen] = (char)*ch;
                destText[(*destLen) + 1] = '\0';
                (*destLen)++;
            }

            *ch = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            (*destLen)--;
            if ((*destLen) < 0)
                (*destLen) = 0;
            destText[*destLen] = '\0';
        }
        break;
    case BUTTONINPUT:
        switch (*ch)
        {
        case KEY_ENTER:
            if (windowM->currWindow == PENGAJARHOME && windowM->selectedPage == MATERI)
            {
                strcpy(windowM->forms.pengajarPage[windowM->selectedPage].fields[1].value.text, windowM->selectByPage.pengajarPage[windowM->selectedPage].selected.value);
                windowM->selectByPage.pengajarPage[windowM->selectedPage].selected = (SelectProp){};
            }
            if (windowM->currWindow == STAFHOME && windowM->selectedPage == JADWAL)
            {
                strcpy(windowM->forms.staffPage[windowM->selectedPage].fields[2].value.text, windowM->selectByPage.staffPage[windowM->selectedPage][2].selected.value);
                windowM->selectByPage.staffPage[windowM->selectedPage][2].selected = (SelectProp){};
                strcpy(windowM->forms.staffPage[windowM->selectedPage].fields[3].value.text, windowM->selectByPage.staffPage[windowM->selectedPage][3].selected.value);
                windowM->selectByPage.staffPage[windowM->selectedPage][3].selected = (SelectProp){};
                strcpy(windowM->forms.staffPage[windowM->selectedPage].fields[4].value.text, windowM->selectByPage.staffPage[windowM->selectedPage][4].selected.value);
                windowM->selectByPage.staffPage[windowM->selectedPage][4].selected = (SelectProp){};
                for (int i = 0; i < windowM->selectByPage.staffPage[windowM->selectedPage][6].nMultiSelected; i++)
                {
                    strcpy(windowM->forms.staffPage[windowM->selectedPage].fields[6].value.multiValue[i], windowM->selectByPage.staffPage[windowM->selectedPage][6].MultiSelected[i].value);
                }
                windowM->forms.staffPage[windowM->selectedPage].fields[6].value.charLen = windowM->selectByPage.staffPage[windowM->selectedPage][6].nMultiSelected;
            }
            if (func != NULL && dataFetcher != NULL)
            {
                func(fields, windowM->dbConn);
                dataFetcher(&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
                clearFields(fields);
            }
            windowM->activeSubWindow = READ;
            break;
        }
        break;
    }
}