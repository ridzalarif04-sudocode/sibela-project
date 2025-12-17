#include "update.h"

void updateView(windowModel *windowM)
{
    if (windowM->isLoading)
    {
        windowM->loadingTime += GetFrameTime();
        float progress = windowM->loadingTime / 2.0f;

        if (progress > 1.0f)
            progress = 1.0f;
        windowM->progress = progress;

        if (windowM->loadingTime >= 2.0f)
        {
            windowM->isLoading = false;
            windowM->currWindow = LANDINGPAGE;
        }

        return;
    }
    int ch = GetKeyPressed();
    switch (ch)
    {
    case KEY_ESCAPE:
        windowM->shouldClose = 1;
        break;
    case KEY_F2:
        windowM->currWindow = STAFHOME;
        break;
    case KEY_F3:
        windowM->currWindow = PENGAJARHOME;
    }
    switch (windowM->currWindow)
    {
    case STAFHOME:
        switch (ch)
        {
        case KEY_UP:
            windowM->curPos -= 1;
            break;
        case KEY_DOWN:
            windowM->curPos += 1;
            break;
        case KEY_TAB:
            if (windowM->forms.staffPage[windowM->selectedPage].selectedField == -1)
                windowM->activeSubWindow = READ;
            else
            {
                windowM->curPos = windowM->forms.staffPage[windowM->selectedPage].selectedField;
                windowM->forms.staffPage[windowM->selectedPage].selectedField = -1;
            }
            break;

        default:
            if (!windowM->cursorEnabled && (windowM->activeSubWindow == CREATE || windowM->activeSubWindow == UPDATE))
            {
                switch (ch)
                {
                case KEY_RIGHT:

                    if (windowM->forms.staffPage[windowM->selectedPage].selectedField > 0 && windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].page < windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].nPage)
                    {
                        windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].page++;
                        windowM->forms.staffPage[windowM->selectedPage].optionFetcher[windowM->forms.staffPage[windowM->selectedPage].selectedField](&windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField], windowM->dbConn);
                    }
                    else if (windowM->forms.staffPage[windowM->selectedPage].selectedField < 0)
                    {
                        windowM->page++;
                        windowM->curPos = windowM->page * windowM->forms.staffPage[windowM->selectedPage].fieldPerPage - windowM->forms.staffPage[windowM->selectedPage].fieldPerPage + 1;
                    }
                    break;
                case KEY_LEFT:
                    if (windowM->forms.staffPage[windowM->selectedPage].selectedField > 0 && windowM->forms.staffPage[windowM->selectedPage].selectedField >= 0 && windowM->forms.staffPage[windowM->selectedPage].fields[windowM->forms.staffPage[windowM->selectedPage].selectedField].type == CUSTOMMODAL)
                    {
                        if (windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].page > 1)
                            windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].page--;
                        windowM->forms.staffPage[windowM->selectedPage].optionFetcher[windowM->forms.staffPage[windowM->selectedPage].selectedField](&windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField], windowM->dbConn);
                    }
                    else if (windowM->forms.staffPage[windowM->selectedPage].selectedField < 0)
                    {
                        windowM->page--;
                        windowM->curPos = windowM->page * windowM->forms.staffPage[windowM->selectedPage].fieldPerPage - windowM->forms.staffPage[windowM->selectedPage].fieldPerPage + 1;
                    }
                    break;
                default:
                    if (ch == KEY_ENTER && (windowM->forms.staffPage[windowM->selectedPage].fields[windowM->curPos].type == CUSTOMMODAL || windowM->forms.staffPage[windowM->selectedPage].fields[windowM->curPos].type == CUSTOMMODALMULTI) && windowM->forms.staffPage[windowM->selectedPage].selectedField == -1)
                    {
                        windowM->selectByPage.staffPage[windowM->selectedPage][windowM->curPos].page = 1;

                        windowM->forms.staffPage[windowM->selectedPage].optionFetcher[windowM->curPos](&windowM->selectByPage.staffPage[windowM->selectedPage][windowM->curPos], windowM->dbConn);
                        windowM->forms.staffPage[windowM->selectedPage].selectedField = windowM->curPos;
                        windowM->curPos = 0;
                    }
                    else if (ch == KEY_ENTER && windowM->forms.staffPage[windowM->selectedPage].selectedField >= 0 && windowM->forms.staffPage[windowM->selectedPage].fields[windowM->forms.staffPage[windowM->selectedPage].selectedField].type == CUSTOMMODAL)
                    {
                        windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].selected = windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].Options[windowM->curPos];
                    }
                    else if (ch == KEY_ENTER && windowM->forms.staffPage[windowM->selectedPage].selectedField >= 0 && windowM->forms.staffPage[windowM->selectedPage].fields[windowM->forms.staffPage[windowM->selectedPage].selectedField].type == CUSTOMMODALMULTI)
                    {
                        windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].MultiSelected[windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].nMultiSelected] = windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].Options[windowM->curPos];
                        windowM->selectByPage.staffPage[windowM->selectedPage][windowM->forms.staffPage[windowM->selectedPage].selectedField].nMultiSelected++;
                    }
                    else
                    {
                        int selectedPage = windowM->selectedPage;
                        int curPos = windowM->curPos;
                        switch (windowM->activeSubWindow)
                        {
                        case UPDATE:
                            handleInput(&ch, &windowM->forms.staffPage[selectedPage].fields[curPos].value.charLen, windowM->forms.staffPage[selectedPage].fields[curPos].value.text, windowM->forms.staffPage[selectedPage].fields[curPos].type, 100, windowM->forms.staffPage[selectedPage].updateFunction, windowM->forms.staffPage[selectedPage].fields, windowM->dataFetchers.staffPage[selectedPage], windowM);
                            break;

                        case CREATE:
                            handleInput(&ch, &windowM->forms.staffPage[selectedPage].fields[curPos].value.charLen, windowM->forms.staffPage[selectedPage].fields[curPos].value.text, windowM->forms.staffPage[selectedPage].fields[curPos].type, 100, windowM->forms.staffPage[selectedPage].createFunc, windowM->forms.staffPage[selectedPage].fields, windowM->dataFetchers.staffPage[selectedPage], windowM);
                            break;
                        }
                    }
                    break;
                }
            }
            if (!windowM->cursorEnabled && windowM->activeSubWindow == READ)
            {
                switch (ch)
                {
                case KEY_N:
                    strcpy(windowM->forms.staffPage[windowM->selectedPage].fields[1].value.text, windowM->authUser.id);
                    windowM->forms.staffPage[windowM->selectedPage].fields[1].value.charLen = strlen(windowM->authUser.id);
                    windowM->activeSubWindow = CREATE;
                    windowM->page = 1;
                    for (int i = 0; i < 6; i++)
                    {
                        windowM->selectByPage.staffPage[windowM->selectedPage][i].nMultiSelected = 0;
                    }
                    windowM->curPos = 1;
                    break;
                case KEY_RIGHT:
                    if (windowM->datas.page < windowM->datas.totalPages)
                    {
                        windowM->datas.page++;
                        windowM->curPos = 0;
                        windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
                    }
                    break;
                case KEY_D:
                    windowM->isModalShown = 1;
                    break;
                case KEY_U:
                    switch (windowM->selectedPage)
                    {
                    case STAFF:
                        copyStringData(windowM->focusedData.staff.id_staff, &windowM->forms.staffPage[STAFF].fields[0].value);
                        copyStringData(windowM->focusedData.staff.nama, &windowM->forms.staffPage[STAFF].fields[1].value);
                        copyStringData(windowM->focusedData.staff.tanggal_lahir, &windowM->forms.staffPage[STAFF].fields[2].value);
                        copyStringData(windowM->focusedData.staff.no_hp, &windowM->forms.staffPage[STAFF].fields[3].value);
                        copyStringData(windowM->focusedData.staff.password, &windowM->forms.staffPage[STAFF].fields[4].value);
                        copyStringData(windowM->focusedData.staff.email, &windowM->forms.staffPage[STAFF].fields[5].value);
                        break;
                    case MURID:
                        char tingkatBuff[4];
                        sprintf(tingkatBuff, "%d", windowM->focusedData.murid.tingkat);
                        copyStringData(windowM->focusedData.murid.id_murid, &windowM->forms.staffPage[MURID].fields[0].value);
                        copyStringData(windowM->focusedData.murid.nama, &windowM->forms.staffPage[MURID].fields[1].value);
                        copyStringData(windowM->focusedData.murid.tanggal_lahir, &windowM->forms.staffPage[MURID].fields[2].value);
                        copyStringData(windowM->focusedData.murid.no_hp, &windowM->forms.staffPage[MURID].fields[3].value);
                        copyStringData(windowM->focusedData.murid.password, &windowM->forms.staffPage[MURID].fields[4].value);
                        copyStringData(tingkatBuff, &windowM->forms.staffPage[MURID].fields[5].value);
                        break;
                    case PENGAJAR:
                        copyStringData(windowM->focusedData.pengajar.id_pengajar, &windowM->forms.staffPage[PENGAJAR].fields[0].value);
                        copyStringData(windowM->focusedData.pengajar.nama, &windowM->forms.staffPage[PENGAJAR].fields[1].value);
                        copyStringData(windowM->focusedData.pengajar.tanggal_lahir, &windowM->forms.staffPage[PENGAJAR].fields[2].value);
                        copyStringData(windowM->focusedData.pengajar.no_hp, &windowM->forms.staffPage[PENGAJAR].fields[3].value);
                        copyStringData(windowM->focusedData.pengajar.password, &windowM->forms.staffPage[PENGAJAR].fields[4].value);
                        break;
                    case RUANGAN:
                        copyStringData(windowM->focusedData.ruangan.id_ruangan, &windowM->forms.staffPage[RUANGAN].fields[0].value);
                        copyStringData(windowM->focusedData.ruangan.lokasi, &windowM->forms.staffPage[RUANGAN].fields[1].value);
                        copyStringData(windowM->focusedData.ruangan.deskripsi, &windowM->forms.staffPage[RUANGAN].fields[2].value);
                        break;
                    case MAPEL:
                        copyStringData(windowM->focusedData.mapel.id_mapel, &windowM->forms.staffPage[MAPEL].fields[0].value);
                        copyStringData(windowM->focusedData.mapel.nama_mapel, &windowM->forms.staffPage[MAPEL].fields[1].value);
                        break;
                    case JADWAL:
                        copyStringData(windowM->focusedData.jadwal.id_pertemuan, &windowM->forms.staffPage[JADWAL].fields[0].value);
                        copyStringData(windowM->focusedData.jadwal.id_staff, &windowM->forms.staffPage[JADWAL].fields[1].value);
                        copySelectData(windowM->focusedData.jadwal.nama_pengajar, windowM->focusedData.jadwal.id_pengajar, &windowM->selectByPage.staffPage[JADWAL][2].selected);
                        copySelectData(windowM->focusedData.jadwal.lokasi, windowM->focusedData.jadwal.id_ruangan, &windowM->selectByPage.staffPage[JADWAL][3].selected);
                        copySelectData(windowM->focusedData.jadwal.judul_materi, windowM->focusedData.jadwal.id_materi, &windowM->selectByPage.staffPage[JADWAL][4].selected);
                        copyStringData(windowM->focusedData.jadwal.waktu, &windowM->forms.staffPage[JADWAL].fields[5].value);
                        findAllSelectedSiswaByPertemuanID(windowM->focusedData.jadwal.id_pertemuan, &windowM->selectByPage.staffPage[JADWAL][6], windowM->dbConn);
                        break;
                    }
                    strcpy(windowM->forms.staffPage[windowM->selectedPage].fields[1].value.text, windowM->authUser.id);
                    windowM->forms.staffPage[windowM->selectedPage].fields[1].value.charLen = strlen(windowM->authUser.id);
                    windowM->activeSubWindow = UPDATE;
                    windowM->page = 1;
                    windowM->curPos = 1;
                    break;
                case KEY_LEFT:
                    if (windowM->datas.page > 1)
                    {
                        windowM->datas.page--;
                        windowM->curPos = 0;
                        windowM->dataFetchers.staffPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
                    }
                    break;
                }
            }

            if (windowM->cursorEnabled)
            {
                switch (ch)
                {
                case KEY_ENTER:

                    if (windowM->curPos == 7)
                    {
                        logoutFunction(windowM);
                        return;
                    }
                    windowM->dataFetchers.staffPage[windowM->curPos](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
                    windowM->selectedPage = windowM->curPos;
                    windowM->datas.page = 1;
                    windowM->curPos = 0;
                    windowM->cursorEnabled = 0;
                    break;
                }
            }
            break;
        }
        break;
    case PENGAJARHOME:

        if (!windowM->cursorEnabled && (windowM->activeSubWindow == CREATE || windowM->activeSubWindow == UPDATE))
        {
            switch (ch)
            {
            case KEY_UP:
                windowM->curPos -= 1;
                break;
            case KEY_DOWN:
                windowM->curPos += 1;
                break;
            case KEY_TAB:
                if (windowM->forms.pengajarPage[windowM->selectedPage].selectedField == -1)
                    windowM->activeSubWindow = READ;
                else
                {
                    windowM->curPos = windowM->forms.pengajarPage[windowM->selectedPage].selectedField;
                    windowM->forms.pengajarPage[windowM->selectedPage].selectedField = -1;
                }
                break;
            case KEY_RIGHT:
                if (windowM->forms.pengajarPage[windowM->selectedPage].selectedField >= 0 && windowM->forms.pengajarPage[windowM->selectedPage].fields[windowM->forms.pengajarPage[windowM->selectedPage].selectedField].type == CUSTOMMODAL)
                {
                    if (windowM->selectByPage.pengajarPage[windowM->selectedPage].page < windowM->selectByPage.pengajarPage[windowM->selectedPage].nPage)
                        windowM->selectByPage.pengajarPage[windowM->selectedPage].page++;
                    windowM->forms.pengajarPage[windowM->selectedPage].optionFetcher[windowM->selectedPage](&windowM->selectByPage.pengajarPage[windowM->selectedPage], windowM->dbConn);
                }
                else if (windowM->forms.pengajarPage[windowM->selectedPage].selectedField < 0)
                {
                    windowM->page++;
                    windowM->curPos = windowM->page * windowM->forms.pengajarPage[windowM->selectedPage].fieldPerPage - windowM->forms.pengajarPage[windowM->selectedPage].fieldPerPage + 1;
                }
                break;
            case KEY_LEFT:
                if (windowM->forms.pengajarPage[windowM->selectedPage].selectedField >= 0 && windowM->forms.pengajarPage[windowM->selectedPage].fields[windowM->forms.pengajarPage[windowM->selectedPage].selectedField].type == CUSTOMMODAL)
                {
                    if (windowM->selectByPage.pengajarPage[windowM->selectedPage].page > 1)
                        windowM->selectByPage.pengajarPage[windowM->selectedPage].page--;
                    windowM->forms.pengajarPage[windowM->selectedPage].optionFetcher[windowM->selectedPage](&windowM->selectByPage.pengajarPage[windowM->selectedPage], windowM->dbConn);
                }
                else if (windowM->forms.pengajarPage[windowM->selectedPage].selectedField < 0)
                {
                    windowM->page--;
                    windowM->curPos = windowM->page * windowM->forms.pengajarPage[windowM->selectedPage].fieldPerPage - windowM->forms.pengajarPage[windowM->selectedPage].fieldPerPage + 1;
                }
                break;
            default:
                if (ch == KEY_ENTER && windowM->forms.pengajarPage[windowM->selectedPage].fields[windowM->curPos].type == CUSTOMMODAL && windowM->forms.pengajarPage[windowM->selectedPage].selectedField == -1)
                {
                    windowM->selectByPage.pengajarPage[windowM->selectedPage].page = 1;
                    windowM->forms.pengajarPage[windowM->selectedPage].optionFetcher[windowM->selectedPage](&windowM->selectByPage.pengajarPage[windowM->selectedPage], windowM->dbConn);
                    windowM->forms.pengajarPage[windowM->selectedPage].selectedField = windowM->curPos;
                    windowM->curPos = 0;
                }
                else if (ch == KEY_ENTER && windowM->forms.pengajarPage[windowM->selectedPage].selectedField >= 0)
                {
                    windowM->selectByPage.pengajarPage[windowM->selectedPage].selected = windowM->selectByPage.pengajarPage[windowM->selectedPage].Options[windowM->curPos];
                }
                else
                {
                    int selectedPage = windowM->selectedPage;
                    int curPos = windowM->curPos;
                    switch (windowM->activeSubWindow)
                    {
                    case UPDATE:
                        handleInput(&ch, &windowM->forms.pengajarPage[selectedPage].fields[curPos].value.charLen, windowM->forms.pengajarPage[selectedPage].fields[curPos].value.text, windowM->forms.pengajarPage[selectedPage].fields[curPos].type, 100, windowM->forms.pengajarPage[selectedPage].updateFunction, windowM->forms.pengajarPage[selectedPage].fields, windowM->dataFetchers.pengajarPage[selectedPage], windowM);
                        break;
                    case CREATE:
                        handleInput(&ch, &windowM->forms.pengajarPage[selectedPage].fields[curPos].value.charLen, windowM->forms.pengajarPage[selectedPage].fields[curPos].value.text, windowM->forms.pengajarPage[selectedPage].fields[curPos].type, 100, windowM->forms.pengajarPage[selectedPage].createFunc, windowM->forms.pengajarPage[selectedPage].fields, windowM->dataFetchers.pengajarPage[selectedPage], windowM);
                        break;
                    }
                }

                break;
            }
        }
        // if (!windowM->cursorEnabled && windowM->activeSubWindow == UPDATE && windowM->forms.pengajarPage[windowM->selectedPage].selectedField == -1)
        // {
        //     switch (ch)
        //     {
        //     case KEY_UP:
        //         windowM->curPos -= 1;
        //         break;
        //     case KEY_DOWN:
        //         windowM->curPos += 1;
        //         break;
        //     case KEY_TAB:
        //         if (windowM->activeSubWindow == READ)
        //         {
        //             windowM->cursorEnabled = 1;
        //             windowM->selectedPage = -1;
        //         }
        //         windowM->activeSubWindow = READ;
        //         windowM->curPos = 0;
        //         break;
        //     case KEY_RIGHT:
        //         windowM->page++;
        //         windowM->curPos = windowM->page * windowM->forms.pengajarPage[windowM->selectedPage].fieldPerPage - windowM->forms.pengajarPage[windowM->selectedPage].fieldPerPage + 1;
        //         break;
        //     case KEY_LEFT:
        //         windowM->page--;
        //         windowM->curPos = windowM->page * windowM->forms.pengajarPage[windowM->selectedPage].fieldPerPage - windowM->forms.pengajarPage[windowM->selectedPage].fieldPerPage + 1;
        //         break;
        //     default:
        //         if (ch == KEY_ENTER && windowM->forms.pengajarPage[windowM->selectedPage].fields[windowM->curPos].type == CUSTOMMODAL && windowM->forms.pengajarPage[windowM->selectedPage].selectedField == -1)
        //         {
        //             windowM->selectByPage.staffPage[windowM->selectedPage].page = 1;
        //             windowM->forms.pengajarPage[windowM->selectedPage].optionFetcher[windowM->selectedPage](&windowM->selectByPage.staffPage[windowM->selectedPage], windowM->dbConn);
        //             windowM->forms.pengajarPage[windowM->selectedPage].selectedField = windowM->curPos;
        //             windowM->curPos = 0;
        //         }
        //         else if (ch == KEY_ENTER && windowM->forms.pengajarPage[windowM->selectedPage].selectedField >= 0)
        //         {
        //             windowM->selectByPage.staffPage[windowM->selectedPage].selected = windowM->selectByPage.staffPage[windowM->selectedPage].Options[windowM->curPos];
        //         }
        //         else
        //         {
        //             int selectedPage = windowM->selectedPage;
        //             int curPos = windowM->curPos;
        //             handleInput(&ch, &windowM->forms.pengajarPage[selectedPage].fields[curPos].value.charLen, windowM->forms.pengajarPage[selectedPage].fields[curPos].value.text, windowM->forms.pengajarPage[selectedPage].fields[curPos].type, 100, windowM->forms.pengajarPage[selectedPage].updateFunction, windowM->forms.pengajarPage[selectedPage].fields, windowM->dataFetchers.pengajarPage[selectedPage], windowM);
        //         }
        //         break;
        //     }
        // }
        if (!windowM->cursorEnabled && windowM->activeSubWindow == READ && windowM->forms.pengajarPage[windowM->selectedPage].selectedField == -1)
        {
            switch (ch)
            {
            case KEY_UP:
                windowM->curPos -= 1;
                break;
            case KEY_DOWN:
                windowM->curPos += 1;
                break;
            case KEY_TAB:

                windowM->cursorEnabled = 1;
                windowM->selectedPage = -1;

                windowM->activeSubWindow = READ;
                windowM->curPos = 0;
                break;
            case KEY_N:
                // windowM->forms.pengajarPage[windowM->selectedPage].optionFetcher[1](&windowM->forms.staffPage[windowM->selectedPage].se)
                windowM->activeSubWindow = CREATE;
                windowM->page = 1;
                windowM->curPos = 1;
                break;
            case KEY_RIGHT:
                if (windowM->datas.page < windowM->datas.totalPages)
                {
                    windowM->datas.page++;
                    windowM->curPos = 0;
                    windowM->dataFetchers.pengajarPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
                }
                break;
            case KEY_D:
                windowM->isModalShown = 1;
                break;
            case KEY_U:
                switch (windowM->selectedPage)
                {
                case MATERI:
                    copyStringData(windowM->focusedData.materi.id_materi, &windowM->forms.pengajarPage[2].fields[0].value);
                    copyStringData(windowM->focusedData.materi.id_mapel, &windowM->forms.pengajarPage[2].fields[1].value);
                    strcpy(windowM->selectByPage.pengajarPage[windowM->selectedPage].selected.value, windowM->focusedData.materi.id_mapel);
                    strcpy(windowM->selectByPage.pengajarPage[windowM->selectedPage].selected.label, windowM->focusedData.materi.nama_mapel);
                    copyStringData(windowM->focusedData.materi.judul_materi, &windowM->forms.pengajarPage[2].fields[2].value);
                    copyStringData(windowM->focusedData.materi.isi_materi, &windowM->forms.pengajarPage[2].fields[3].value);
                    break;
                }
                windowM->activeSubWindow = UPDATE;
                windowM->page = 1;
                windowM->curPos = 1;
                break;
            case KEY_LEFT:
                if (windowM->datas.page > 1)
                {
                    windowM->datas.page--;
                    windowM->curPos = 0;
                    windowM->dataFetchers.pengajarPage[windowM->selectedPage](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
                }
                break;
            }
        }
        if (windowM->forms.pengajarPage[windowM->selectedPage].selectedField >= 0)
        {
            switch (ch)
            {
            KEY_TAB:
                windowM->forms.pengajarPage[windowM->selectedPage].selectedField = -1;
                break;
            }
        }
        if (windowM->cursorEnabled)
        {
            switch (ch)
            {
            case KEY_UP:
                windowM->curPos -= 1;
                break;
            case KEY_DOWN:
                windowM->curPos += 1;
                break;
            case KEY_ENTER:

                if (windowM->curPos == 3)
                {
                    logoutFunction(windowM);
                    return;
                }
                windowM->dataFetchers.pengajarPage[windowM->curPos](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
                windowM->selectedPage = windowM->curPos;
                windowM->datas.page = 1;
                windowM->curPos = 0;
                windowM->cursorEnabled = 0;
                break;
            }
        }

        break;
    case MURIDHOME:
        switch (ch)
        {
        case KEY_W:
        case KEY_UP:
            windowM->curPos -= 1;
            break;
        case KEY_S:
        case KEY_DOWN:
            windowM->curPos += 1;
            break;

        case KEY_TAB:
            windowM->cursorEnabled = 1;
            windowM->selectedPage = -1;
            windowM->curPos = 0;
            break;
        case KEY_SPACE:
        case KEY_ENTER:
            // windowM->dataFetchers.pengajarPage[windowM->curPos](&windowM->datas, &windowM->datas.totalPages, windowM->dbConn);
            if (windowM->curPos == 3)
            {
                logoutFunction(windowM);
                return;
            }
            windowM->selectedPage = windowM->curPos;
            windowM->curPos = 0;
            windowM->cursorEnabled = 0;
            break;
        }
        break;
    case LOGINSTAFF:
        switch (ch)
        {
        case KEY_TAB:
            break;

        case KEY_DOWN:
            windowM->loginData.activeInput++;
            break;
        case KEY_UP:
            windowM->loginData.activeInput--;
            break;

        default:
            switch (windowM->loginData.activeInput)
            {
            case 0:
                handleInput(&ch, &windowM->loginData.email.charLen, windowM->loginData.email.text, TEXTINPUT, 100, NULL, NULL, NULL, windowM);
                break;
            case 1:
                handleInput(&ch, &windowM->loginData.password.charLen, windowM->loginData.password.text, TEXTINPUT, 100, NULL, NULL, NULL, windowM);
                break;
            case 2:
                switch (ch)
                {
                case KEY_ENTER:
                    loginFunction(windowM);
                    break;
                }
                break;
            }
            break;
        }
        break;
    case LOGINPENGAJAR:
    case LOGINMURID:
        switch (ch)
        {
        case KEY_TAB:
            break;

        case KEY_DOWN:
            windowM->loginData.activeInput++;
            break;
        case KEY_UP:
            windowM->loginData.activeInput--;
            break;

        default:
            switch (windowM->loginData.activeInput)
            {
            case 0:
                handleInput(&ch, &windowM->loginData.phoneNumber.charLen, windowM->loginData.phoneNumber.text, NUMERICINPUT, 15, NULL, NULL, NULL, windowM);
                break;
            case 1:
                handleInput(&ch, &windowM->loginData.password.charLen, windowM->loginData.password.text, TEXTINPUT, 100, NULL, NULL, NULL, windowM);
                break;
            case 2:
                switch (ch)
                {
                case KEY_ENTER:
                    loginFunction(windowM);
                    break;
                }
                break;
            }
            break;
        }
        break;
    case LANDINGPAGE:
        switch (ch)
        {
        case KEY_UP:
            windowM->curPos -= 1;
            break;
        case KEY_DOWN:
            windowM->curPos += 1;
            break;
        case KEY_ENTER:
            windowM->currWindow = windowM->navigation.landingPage[windowM->curPos].targetPage;
            windowM->curPos = 0;
            break;
        }
        break;
    case CONTRIBPAGE:
        switch (ch)
        {
        case KEY_LEFT:
            if (windowM->page > 1)
                windowM->page--;
            break;
        case KEY_RIGHT:
            if (windowM->page < 5)
                windowM->page++;
            break;
        case KEY_TAB:
            windowM->currWindow = LANDINGPAGE;
            windowM->page = 1;
            break;
        }
        break;
    }
}