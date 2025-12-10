#include "drawView.h"

void drawRootView(windowModel *windowM)
{
    ClearBackground(TERTIARY);
    switch (windowM->currWindow)
    {
    case STAFHOME:
        drawHome(windowM);
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
}