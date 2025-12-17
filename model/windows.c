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
    windowM->forms.staffPage[JADWAL].nField = 7;
    windowM->forms.staffPage[PENGAJAR].nField = 5;
    windowM->forms.staffPage[RUANGAN].nField = 3;
    windowM->forms.staffPage[STAFF].fieldPerPage = 4;
    windowM->forms.staffPage[MAPEL].fieldPerPage = 2;
    windowM->forms.staffPage[MURID].fieldPerPage = 4;
    windowM->forms.staffPage[PENGAJAR].fieldPerPage = 5;
    windowM->forms.staffPage[RUANGAN].fieldPerPage = 3;
    windowM->forms.staffPage[JADWAL].fieldPerPage = 4;
    windowM->forms.staffPage[STAFF].createFunc = createStaff;
    windowM->forms.staffPage[STAFF].updateFunction = updateStaff;
    windowM->forms.staffPage[MAPEL].createFunc = createMapel;
    windowM->forms.staffPage[MAPEL].updateFunction = updateMapel;
    windowM->forms.staffPage[MURID].createFunc = createMurid;
    windowM->forms.staffPage[MURID].updateFunction = updateMurid;
    windowM->forms.staffPage[PENGAJAR].createFunc = createPengajar;
    windowM->forms.staffPage[PENGAJAR].updateFunction = updatePengajar;
    windowM->forms.staffPage[RUANGAN].createFunc = createRuangan;
    windowM->forms.staffPage[RUANGAN].updateFunction = updateRuangan;
    windowM->forms.staffPage[JADWAL].createFunc = createJadwalPertemuan;
    windowM->forms.staffPage[JADWAL].updateFunction = updateJadwalPertemuan;
    windowM->dataFetchers.staffPage[STAFF] = findAllStaff;
    windowM->dataFetchers.staffPage[MURID] = findAllMurid;
    windowM->dataFetchers.staffPage[PENGAJAR] = findAllPengajar;
    windowM->dataFetchers.staffPage[RUANGAN] = findAllRuangan;
    windowM->dataFetchers.staffPage[MAPEL] = findAllMapel;
    windowM->dataFetchers.staffPage[JADWAL] = findAllJadwalPertemuan;

    windowM->forms.staffPage[JADWAL].fields[1] = (InputField){.label = "ID STAFF", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[JADWAL].fields[2] = (InputField){.label = "ID PENGAJAR", .type = CUSTOMMODAL, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[JADWAL].fields[3] = (InputField){.label = "ID RUANGAN", .type = CUSTOMMODAL, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[JADWAL].fields[4] = (InputField){.label = "ID MATERI", .type = CUSTOMMODAL, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[JADWAL].fields[5] = (InputField){.label = "WAKTU", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[JADWAL].fields[6] = (InputField){.label = "MURID", .type = CUSTOMMODALMULTI, .value = (InputParams){.charLen = 0, .multiValue = {}}};
    windowM->forms.staffPage[JADWAL].fields[7] = (InputField){.label = "SUBMIT", .type = BUTTONINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.staffPage[JADWAL].optionFetcher[2] = findAllPengajarSelect;
    windowM->forms.staffPage[JADWAL].optionFetcher[3] = findAllRuanganSelect;
    windowM->forms.staffPage[JADWAL].optionFetcher[4] = findAllMateriSelect;
    windowM->forms.staffPage[JADWAL].optionFetcher[6] = findAllMuridSelect;
    windowM->forms.staffPage[JADWAL].selectedField = -1;

    windowM->selectByPage.staffPage = (Select(*)[6])malloc(sizeof(Select) * 6 * 10);

    windowM->forms.pengajarPage[MATERI].fields[1] = (InputField){.label = "ID MAPEL", .type = CUSTOMMODAL, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.pengajarPage[MATERI].fields[2] = (InputField){.label = "Judul Materi", .type = TEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.pengajarPage[MATERI].fields[3] = (InputField){.label = "Isi Materi", .type = LONGTEXTINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->forms.pengajarPage[MATERI].fields[4] = (InputField){.label = "SUBMIT", .type = BUTTONINPUT, .value = (InputParams){.charLen = 0, .text = ""}};
    windowM->dataFetchers.pengajarPage[2] = findAllMateri;
    windowM->forms.pengajarPage[MATERI].createFunc = createMateri;
    windowM->forms.pengajarPage[MATERI].updateFunction = updateMateri;
    windowM->forms.pengajarPage[MATERI].fieldPerPage = 4;
    windowM->forms.pengajarPage[MATERI].nField = 4;
    windowM->forms.pengajarPage[MATERI].optionFetcher[2] = findAllMapelSelect;
    windowM->forms.pengajarPage[MATERI].selectedField = -1;
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
    free(windowM->selectByPage.staffPage);
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