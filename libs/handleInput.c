#include "handleInput.h"

void handleInput(int *ch, int *destLen, char destText[], InputType fieldType, int maxLen, mutationFunc func, InputField fields[], fetcherAdmin dataFetcher, windowModel *windowM)
{

    switch (fieldType)
    {
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
            if (func != NULL && dataFetcher != NULL)
            {
                func(fields, windowM->dbConn);
                dataFetcher(&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
            }
            windowM->activeSubWindow = READ;
            break;
        }
        break;
    }
}