#include "memberView.h"

void drawMemberPage(windowModel *windowM)
{
    windowM->members[0] = (Member){.nama = "Rayyan Abdurrahman Qadar", .julukan = "Pak Ketua", .domisili = "Jakarta Utara", .nim = "0920250049", .tanggalLahir = "19 Oktober 2006", .image = windowM->members[0].image};
    windowM->members[1] = (Member){.nama = "Rasya Bintang Priyanto", .julukan = "Nol Lima", .domisili = "Cikarang Utara", .nim = "0920250048", .tanggalLahir = "14 Agustus 2007", .image = windowM->members[1].image};
    windowM->members[2] = (Member){.nama = "Teguh Bayu Pratama ", .julukan = "-", .domisili = "Palu", .nim = "0920250052", .tanggalLahir = "17 Juni 2007", .image = windowM->members[2].image};
    windowM->members[3] = (Member){.nama = "Ridzal Arif Billah", .julukan = "Extreme Programmer", .domisili = "Bekasi", .nim = "0920250051", .tanggalLahir = "04 Agustus 2007", .image = windowM->members[3].image};
    windowM->members[4] = (Member){.nama = "Nabilah Tri Utami", .julukan = "Kroconya rijal", .domisili = "Brebes", .nim = "0920250044", .tanggalLahir = "03 September 2007", .image = windowM->members[4].image};

    Member currMember = windowM->members[windowM->page - 1];
    char page[50];
    char nim[30];
    char julukan[60];
    char domisili[60];
    char tanggalLahir[60];

    strcpy(page, TextFormat("Member %d dari 5", windowM->page));
    strcpy(nim, TextFormat("NIM:\t\"%s\"", currMember.nim));
    strcpy(julukan, TextFormat("Julukan:\t\"%s\"", currMember.julukan));
    strcpy(domisili, TextFormat("Domisili:\t\"%s\"", currMember.domisili));
    strcpy(tanggalLahir, TextFormat("Tanggal Lahir: \"%s\"", currMember.tanggalLahir));

    Rectangle boundingArea = {.width = 1920 * 0.6, .height = 1080 * 0.5, .x = 1920 / 2 - 576, .y = 1080 / 2 - 270};
    int infoStartX = boundingArea.x + 460;
    int infoStartY = boundingArea.y + boundingArea.height / 2 - 116;

    DrawRectangleRoundedLinesEx(boundingArea, 0.2, 0, 1, SIBELAWHITE);

    DrawTextureEx(currMember.image, (Vector2){boundingArea.x + 54, boundingArea.y + 80}, 0, 0.7, WHITE);
    DrawTextEx(*windowM->fontStyle.medium, currMember.nama, (Vector2){infoStartX, infoStartY}, 50, 0, SIBELAWHITE);
    DrawTextEx(*windowM->fontStyle.regular, nim, (Vector2){infoStartX, infoStartY + 52}, 32, 0, SIBELAWHITE);
    DrawTextEx(*windowM->fontStyle.regular, julukan, (Vector2){infoStartX, infoStartY + 82}, 32, 0, SIBELAWHITE);
    DrawTextEx(*windowM->fontStyle.regular, domisili, (Vector2){infoStartX, infoStartY + 112}, 32, 0, SIBELAWHITE);
    DrawTextEx(*windowM->fontStyle.regular, tanggalLahir, (Vector2){infoStartX, infoStartY + 144}, 32, 0, SIBELAWHITE);
    DrawTextEx(*windowM->fontStyle.regular, page, (Vector2){1920 / 2 - MeasureTextEx(*windowM->fontStyle.regular, page, 32, 0).x / 2, 1080 - 70}, 32, 0, SIBELAWHITE);
}