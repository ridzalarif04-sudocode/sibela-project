#include "login.h"

void loginFunction(windowModel *windowM)
{

    switch (windowM->currWindow)
    {
    case LOGINSTAFF:
        Staf loginStaf = findStafbyEmail(windowM->loginData.email.text, windowM->dbConn);

        if (loginStaf.id_num == -1)
            return;
        // printf("loginaw: %d\n", strcmp(loginStaf.password, windowM->loginData.password.text));

        if (strcmp(loginStaf.password, windowM->loginData.password.text) == 0)
        {

            strcpy(windowM->loginData.email.text, "\0");
            strcpy(windowM->loginData.password.text, "\0");
            windowM->loginData.password.charLen = 0;
            windowM->loginData.email.charLen = 0;

            strcpy(windowM->authUser.id, loginStaf.id_staff);
            strcpy(windowM->authUser.nama, loginStaf.nama);
            strcpy(windowM->authUser.role, loginStaf.role);
            windowM->currWindow = STAFHOME;
        }
        break;
    case LOGINMURID:
        Murid loginMurid = findMuridbyPhoneNum(windowM->loginData.phoneNumber.text, windowM->dbConn);

        if (loginMurid.id_num == -1)
            return;
        // printf("loginaw: %d\n", strcmp(loginMurid.password, windowM->loginData.password.text));

        if (strcmp(loginMurid.password, windowM->loginData.password.text) == 0)
        {

            strcpy(windowM->loginData.email.text, "\0");
            strcpy(windowM->loginData.password.text, "\0");
            windowM->loginData.password.charLen = 0;
            windowM->loginData.email.charLen = 0;

            strcpy(windowM->authUser.id, loginMurid.id_murid);
            strcpy(windowM->authUser.nama, loginMurid.nama);
            strcpy(windowM->authUser.role, "MURID");
            windowM->currWindow = MURIDHOME;
        }
        break;
    case LOGINPENGAJAR:
    Pengajar loginpengajar = findPengajarbyPhoneNum(windowM->loginData.phoneNumber.text, windowM->dbConn);

        if (loginpengajar.id_num == -1)
            return;
        // printf("loginaw: %d\n", strcmp(loginpengajar.password, windowM->loginData.password.text));

        if (strcmp(loginpengajar.password, windowM->loginData.password.text) == 0)
        {

            strcpy(windowM->loginData.email.text, "\0");
            strcpy(windowM->loginData.password.text, "\0");
            windowM->loginData.password.charLen = 0;
            windowM->loginData.email.charLen = 0;

            strcpy(windowM->authUser.id, loginpengajar.id_pengajar);
            strcpy(windowM->authUser.nama, loginpengajar.nama);
            strcpy(windowM->authUser.role, "PENGAJAR");
            windowM->currWindow = PENGAJARHOME;
        }
        break;
    }
}