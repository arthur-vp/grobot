/**
 * @file Screen.h
 * @brief Provides a simple interface for using the SSD1309 screen with the U8g2 library over I2C.
 *
 * This class encapsulates basic operations for drawing text and simple graphics,
 * such as a smiling face, on an SSD1309 128x64 OLED display using hardware I2C.
 */

#pragma once
#include <U8g2lib.h>

class Screen 
{
public:
    Screen();
    void begin();
    void clear();
    void drawText(int x, int y, const char* text);
    void drawSmiley(int x, int y, int r = 20);
    void display();
    U8G2& getU8g2();

private:
    U8G2_SSD1309_128X64_NONAME0_F_HW_I2C u8g2;
};