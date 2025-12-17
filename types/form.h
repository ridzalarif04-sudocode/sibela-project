#ifndef FORMTYPES
#define FORMTYPES

#include "../model/model.h"

typedef struct
{
    char text[100];
    char multiValue[50][8];
    int charLen;
    int selected;
} InputParams;

typedef enum
{
    TEXTINPUT,
    BUTTONINPUT,
    SHORTINPUT,
    NUMERICINPUT,
    LONGTEXTINPUT,
    CUSTOMMODAL,
    CUSTOMMODALMULTI,
} InputType;

typedef struct
{
    char label[50];
    char value[100];
} SelectProp;

typedef struct
{
    SelectProp Options[100];
    int nOptions;
    int page;
    int nPage;
    char searchQuery[100];
    SelectProp selected;
    int nMultiSelected;
    SelectProp MultiSelected[50];
} Select;

typedef struct
{
    char label[25];
    InputParams value;
    InputType type;
} InputField;

typedef QUERYSTATUS (*mutationFunc)(InputField fields[], SQLHDBC *dbConn);
typedef void (*selectOptionFetcher)(Select *selectObject, SQLHDBC *dbConn);

typedef struct
{
    InputField fields[10];
    int nField;
    mutationFunc createFunc;
    mutationFunc updateFunction;
    int fieldPerPage;
    int totalPages;
    int offset;
    int lastIndex;
    int selectedField;
    selectOptionFetcher optionFetcher[10];
} FORM;

#endif