#include "legend.h"
#include "raylib.h"

static void drawItem(int x, int y, const char *key, const char *desc, Font font)
{
    DrawTextEx(font, key, (Vector2){x, y}, 22, 0, WHITE);
    DrawTextEx(font, desc, (Vector2){x + 110, y}, 22, 0, WHITE);
}

void DrawLegend(windowModel *windowM)
{
    int x = 1920 - 380;
    int y = 1080 - 220;
    int gap = 30;
    int row = 0;

    Font font = windowM->fontStyle.medium;

    DrawRectangleRounded(
        (Rectangle){x - 20, y - 20, 360, 200},
        0.15f,
        8,
        Fade(BLACK, 0.55f)
    );

    if (windowM->cursorEnabled)
    {
        drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi Menu", font);
        drawItem(x, y + gap * row++, "Enter", "Pilih Menu", font);
        drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
        return; 
    }

    if (windowM->activeSubWindow == READ)
    {
        drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi Data", font);
        drawItem(x, y + gap * row++, "N", "Tambah Data", font);
        drawItem(x, y + gap * row++, "U", "Ubah Data", font);
        drawItem(x, y + gap * row++, "D", "Hapus Data", font);
        drawItem(x, y + gap * row++, "Tab", "Kembali", font);
        drawItem(x, y + gap * row++, "Esc", "Keluar Aplikasi", font);
        return;
    }

    if (windowM->activeSubWindow == CREATE)
    {
        drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi", font);
        drawItem(x, y + gap * row++, "Enter", "Submit", font);
        drawItem(x, y + gap * row++, "Esc", "Batal", font);
        return;
    }

    if (windowM->activeSubWindow == UPDATE)
    {
        drawItem(x, y + gap * row++, "Atas/Bawah", "Navigasi", font);
        drawItem(x, y + gap * row++, "Enter", "Submit", font);
        drawItem(x, y + gap * row++, "Esc", "Batal", font);
        return;
    }
}
