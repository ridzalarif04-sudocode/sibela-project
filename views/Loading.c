#include "Loading.h"
#include <math.h>
// void LoadingScreen(windowModel *windowM, float progress)
// {
//     const int screenWidth = 1920;
//     const int screenHeight = 1080;

//     static Texture2D logo = {0};

//     // Load sekali
//     if (logo.id == 0) {
//         logo = LoadTexture("assets/images/sibela_Versi2.png");
//     }

//     int boxSize = 22;
//     int boxGap  = 8;
//     int totalBox = 12;
//     int loadingWidth = totalBox * (boxSize + boxGap);

//     Vector2 logoPos = {
//         (screenWidth  - logo.width) / 2.0f,
//         (screenHeight / 2.0f) - logo.height - 40.0f
//     };

//     DrawTexture(logo, logoPos.x, logoPos.y, WHITE);

//     Vector2 loadingPos = {
//         (screenWidth - loadingWidth) / 2.0f,
//         logoPos.y + logo.height + 60.0f
//     };

//     int filled = (int)(progress * totalBox);

//     for (int i = 0; i < totalBox; i++) {
//         float x = loadingPos.x + i * (boxSize + boxGap);

//         if (i < filled)
//             DrawRectangle(x, loadingPos.y, boxSize, boxSize, BLUE);
//         else
//             DrawRectangleLines(x, loadingPos.y, boxSize, boxSize, BLUE);
//     }

//     char persen[16];
//     sprintf(persen, "%d%%", (int)(progress * 100));

//     Vector2 textPos = {
//         loadingPos.x + loadingWidth + 25,
//         loadingPos.y + 2
//     };

//     DrawText(persen, textPos.x, textPos.y, 30, BLUE);
// }
void LoadingScreen(windowModel *windowM, float progress)
{
    int screenWidth  = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    static Texture2D logo = {0};
    if (logo.id == 0)
        logo = LoadTexture("assets/images/sibela_Versi2.png");

    float glow = (sinf(GetTime() * 3.0f) + 1.0f) * 0.5f;
    int alphaGlow = (int)(glow * 120.0f);

    Vector2 logoPos = {
        (screenWidth  - logo.width)  / 2.0f + 40,
        (screenHeight / 2.0f) - logo.height - 40
    };

    DrawTexture(logo, logoPos.x, logoPos.y, WHITE);

    int barWidth  = 600;
    int barHeight = 22;

    Vector2 barPos = {
        (screenWidth - barWidth) / 2.0f,
        logoPos.y + logo.height + 70
    };

    DrawRectangle(barPos.x, barPos.y, barWidth, barHeight, Fade(BLUE, 0.25f));

    DrawRectangle(barPos.x, barPos.y, barWidth * progress, barHeight, Fade(BLUE, 0.9f));

    DrawRectangle(barPos.x, barPos.y, barWidth * progress, barHeight, (Color){0, 150, 255, alphaGlow});

    DrawRectangleLines(barPos.x, barPos.y, barWidth, barHeight, BLUE);

    char persen[16];
    sprintf(persen, "%d%%", (int)(progress * 100));

    DrawTextEx(*windowM->fontStyle.medium,persen,(Vector2){ barPos.x + barWidth + 20, barPos.y - 4 },32,1,BLUE);
}