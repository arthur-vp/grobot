#include "Screen.h"
#include <U8g2lib.h>

// I2C address for the SSD1309 display

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
// Dessine un visage souriant plus expressif
void Screen::drawSmiley(int x, int y, int r)
{
    // === Visage ===
    u8g2.drawCircle(x, y, r, U8G2_DRAW_ALL); // Contour du visage

    // === Yeux ===
    int eyeDistanceX = r * 0.4;
    int eyeOffsetY   = r * 0.35;
    int eyeRadius    = r * 0.12;

    // Œil gauche
    u8g2.drawDisc(x - eyeDistanceX, y - eyeOffsetY, eyeRadius, U8G2_DRAW_ALL);
    // Œil droit
    u8g2.drawDisc(x + eyeDistanceX, y - eyeOffsetY, eyeRadius, U8G2_DRAW_ALL);

// Sourire faux avec ellipse + masque
u8g2.drawEllipse(x, mouthY, mouthRadius, r * 0.15, U8G2_DRAW_ALL);

// Masquer la moitié supérieure de l'ellipse
u8g2.setDrawColor(0); // Couleur "effacement"
u8g2.drawBox(x - mouthRadius, mouthY - r * 0.15, 2 * mouthRadius, r * 0.15);
u8g2.setDrawColor(1); // Revenir à dessin normal


    // === Joues (optionnel) ===
    int cheekRadius = r * 0.08;
    int cheekOffsetX = r * 0.6;
    int cheekOffsetY = r * 0.15;

    u8g2.drawDisc(x - cheekOffsetX, y + cheekOffsetY, cheekRadius, U8G2_DRAW_ALL); // Joue gauche
    u8g2.drawDisc(x + cheekOffsetX, y + cheekOffsetY, cheekRadius, U8G2_DRAW_ALL); // Joue droite
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