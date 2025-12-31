#include "drawView.h"
#include "Loading.h"

void drawRootView(windowModel *windowM)
{
    ClearBackground(TERTIARY);

    if (windowM->isLoading)
    {
        LoadingScreen(windowM, windowM->loadingTime / 2.0f);
        return;
    }

    switch (windowM->currWindow)
    {
    case STAFHOME:
        drawStaffHome(windowM);
        break;
    case PENGAJARHOME:
        drawPengajarHome(windowM);
        break;
    case MURIDHOME:
        drawMuridHome(windowM);
        break;
    case LOGINSTAFF:
        drawHeader(windowM);
        drawStaffLogin(windowM);
        break;
    case LOGINPENGAJAR:
        drawHeader(windowM);
        drawMuridTeacherLogin(windowM);
        break;
    case LOGINMURID:
        drawHeader(windowM);
        drawMuridTeacherLogin(windowM);
        break;
    case ADMINSTUDENT:
        break;
    case LANDINGPAGE:
        drawHeader(windowM);
        drawLandingPage(windowM);
        break;

    case CONTRIBPAGE:
        drawMemberPage(windowM);
        break;
    }
    DrawLegend(windowM);
}