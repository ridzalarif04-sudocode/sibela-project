#include "window.h"

void initForm(windowModel *windowM)
{
    windowM->forms.staffPage[STAFF].fields[1] = (InputField){.label = "Nama", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[STAFF].fields[2] = (InputField){.label = "Tanggal Lahir", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[STAFF].fields[3] = (InputField){.label = "No. HP", .type = NUMERICINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[STAFF].fields[4] = (InputField){.label = "Password", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[STAFF].fields[5] = (InputField){.label = "Email", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[STAFF].fields[6] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    windowM->forms.staffPage[MURID].fields[1] = (InputField){.label = "Nama", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MURID].fields[2] = (InputField){.label = "Tanggal Lahir", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MURID].fields[3] = (InputField){.label = "No HP", .type = NUMERICINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MURID].fields[4] = (InputField){.label = "Password", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MURID].fields[5] = (InputField){.label = "Tingkat", .type = NUMERICINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MURID].fields[6] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    windowM->forms.staffPage[PENGAJAR].fields[1] = (InputField){.label = "Nama", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[PENGAJAR].fields[2] = (InputField){.label = "Tanggal Lahir", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[PENGAJAR].fields[3] = (InputField){.label = "No HP", .type = NUMERICINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[PENGAJAR].fields[4] = (InputField){.label = "Password", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[PENGAJAR].fields[5] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    windowM->forms.staffPage[RUANGAN].fields[1] = (InputField){.label = "Lokasi", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[RUANGAN].fields[2] = (InputField){.label = "Deskripsi", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[RUANGAN].fields[3] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    windowM->forms.staffPage[MAPEL].fields[1] = (InputField){.label = "Nama Mapel", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[MAPEL].fields[2] = (InputField){.label = "Submit", .type = BUTTONINPUT};
    windowM->forms.staffPage[STAFF].nField = 6;
    windowM->forms.staffPage[MURID].nField = 6;
    windowM->forms.staffPage[MAPEL].nField = 2;
    windowM->forms.staffPage[PENGAJAR].nField = 5;
    windowM->forms.staffPage[RUANGAN].nField = 3;
    windowM->forms.staffPage[STAFF].fieldPerPage = 4;
    windowM->forms.staffPage[MAPEL].fieldPerPage = 2;
    windowM->forms.staffPage[MURID].fieldPerPage = 4;
    windowM->forms.staffPage[PENGAJAR].fieldPerPage = 5;
    windowM->forms.staffPage[RUANGAN].fieldPerPage = 3;
    windowM->forms.staffPage[STAFF].func = createStaff;
    windowM->forms.staffPage[MAPEL].func = createMapel;
    windowM->forms.staffPage[MURID].func = createMurid;
    windowM->forms.staffPage[PENGAJAR].func = createPengajar;
    windowM->forms.staffPage[RUANGAN].func = createRuangan;
    windowM->dataFetchers.admin[0] = findAllStaff;
    windowM->dataFetchers.admin[1] = findAllMurid;
    windowM->dataFetchers.admin[2] = findAllPengajar;
    windowM->dataFetchers.admin[3] = findAllRuangan;
    windowM->dataFetchers.admin[4] = findAllMapel;
}

void initAssets(windowModel *windowM)
{
    windowM->members[0]
        .image = LoadTexture("assets/images/member/rayyan.png");
    windowM->members[1].image = LoadTexture("assets/images/member/rasya.png");
    windowM->members[2].image = LoadTexture("assets/images/member/bayu.png");
    windowM->members[3].image = LoadTexture("assets/images/member/rijal.png");
    windowM->members[4].image = LoadTexture("assets/images/member/nabilah.png");

    // Logo Sibela
    windowM->images.logo = LoadTexture("assets/images/sibela_Versi2.png");
    // Logo Robot Sibela
    windowM->images.logoRobot = LoadTexture("assets/images/Robot_Sibela.png");

    windowM->isLoading = true;
    windowM->loadingTime = 0.0f;

    // FONTS
    windowM->fontStyle.medium = LoadFontEx("assets/fonts/Poppins-Medium.ttf", 224, 0, 250);
    windowM->fontStyle.regular = LoadFontEx("assets/fonts/Poppins-Regular.ttf", 224, 0, 250);
    windowM->fontStyle.mediumItalic = LoadFontEx("assets/fonts/Poppins-MediumItalic.ttf", 224, 0, 250);
}

void initWindow(windowModel *windowM)
{
    *windowM = (windowModel){
        .currWindow = LANDINGPAGE,
        .shouldClose = 0,
        .curPos = 0,
        .page = 1,
        .cursorEnabled = 1,
        .selectedPage = -1,
        .isModalShown = 0,
        .activeSubWindow = READ,
        .loginData = {.email = {.charLen = 0, .text = "\0"}, .activeInput = 0}};
    windowM->datas.page = 1;

    initForm(windowM);
    initAssets(windowM);
}

void unloadAssets(windowModel *windowM)
{
    UnloadFont(windowM->fontStyle.medium);
    UnloadFont(windowM->fontStyle.regular);
    UnloadFont(windowM->fontStyle.mediumItalic);
    UnloadTexture(windowM->images.logo);
    UnloadTexture(windowM->images.logoRobot);
    UnloadTexture(windowM->members[0].image);
    UnloadTexture(windowM->members[1].image);
    UnloadTexture(windowM->members[2].image);
    UnloadTexture(windowM->members[3].image);
    UnloadTexture(windowM->members[4].image);
}