#ifndef utils
#define utils

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../types/form.h"

void readAscii(char name[], char dest[]);
time_t parseDate(char strDate[]);
char *parseDateToString(time_t cDate);
void copyStringData(char src[], InputParams *dest);
char *intToString(int i);
int isOptionInMultiSelected(SelectProp target, SelectProp domain[], int nDomain);
void clearFields(InputField fields[]);
void copySelectData(char label[], char value[], SelectProp *dest);

#endif