#include "Screen.h"
#include <U8g2lib.h>

// Constructor: Initialize the U8G2 object with default I2C pins
Screen::Screen()
    : u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE) // No reset pin by default
{
}

// Initialize the display hardware
void Screen::begin()
{
    u8g2.begin();
}

// Clear the internal display buffer
void Screen::clear()
{
    u8g2.clearBuffer();
}

// Draw a text string at the specified position
void Screen::drawText(int x, int y, const char *text)
{
    u8g2.setFont(u8g2_font_ncenB08_tr); // Example font, can be changed
    u8g2.drawStr(x, y, text);
}

// Draw a simple smiling face graphic
void Screen::drawSmiley(int x, int y, int r)
{
    // Face outline
    u8g2.drawCircle(x, y, r, U8G2_DRAW_ALL);

    // Eyes
    int eyeOffsetX = r / 2;
    int eyeOffsetY = r / 3;
    int eyeR = r / 6;
    u8g2.drawDisc(x - eyeOffsetX, y - eyeOffsetY, eyeR, U8G2_DRAW_ALL);
    u8g2.drawDisc(x + eyeOffsetX, y - eyeOffsetY, eyeR, U8G2_DRAW_ALL);

    // Smile (arc)
    int smileR = r / 2;
    int smileY = y + r / 4;
    u8g2.drawArc(x, smileY, smileR, smileR, 30); // Smile arc from 30 to 150 degrees
}

// Send the current buffer to the display
void Screen::display()
{
    u8g2.sendBuffer();
}

// Provides access to the underlying U8G2 object
U8G2 &Screen::getU8g2()
{
    return u8g2;
}