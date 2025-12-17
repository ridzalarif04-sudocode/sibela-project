#include "utils.h"

void readAscii(char name[], char dest[])
{
    FILE *ascii_file;
    char line[256];
    const char filename[150];

    sprintf(filename, "assets/ascii/%s", name);

    ascii_file = fopen(filename, "r");
    if (ascii_file == NULL)
    {
        perror(filename);
        perror("Error opening file");
    }

    while (fgets(line, sizeof(line), ascii_file) != NULL)
    {
        strcat(dest, line);
    }

    fclose(ascii_file);
}

time_t parseDate(char strDate[])
{
    struct tm tm_info = {0};

    sscanf(strDate, "%d-%d-%d %d:%d:%d", &tm_info.tm_year, &tm_info.tm_mon, &tm_info.tm_mday, &tm_info.tm_hour, &tm_info.tm_min, &tm_info.tm_sec);
    tm_info.tm_year -= 1900;

    return mktime(&tm_info);
}

char *parseDateToString(time_t cDate)
{
    char *dateBuff;
    struct tm *parsedDate;

    parsedDate = localtime(&cDate);

    sprintf(dateBuff, "%d-%d-%d", parsedDate->tm_year + 1900, parsedDate->tm_mon, parsedDate->tm_mday);

    return dateBuff;
}

void copyStringData(char src[], InputParams *dest)
{
    strcpy(dest->text, src);
    dest->charLen = strlen(src);
}

void copySelectData(char label[], char value[], SelectProp *dest)
{
    strcpy(dest->label, label);
    strcpy(dest->value, value);
}

char *intToString(int i)
{
    char *buff;
    sprintf(buff, "%d", i);

    return buff;
}

void clearFields(InputField fields[])
{
    for (int i = 0; i < 10; i++)
    {
        fields[i].value.charLen = 0;
        strcpy(fields[i].value.text, "");
    }
}

int isOptionInMultiSelected(SelectProp target, SelectProp domain[], int nDomain)
{
    for (int i = 0; i < nDomain; i++)
    {
        if (strcmp(domain[i].value, target.value) == 0)
            return 1;
    }

    return 0;
}