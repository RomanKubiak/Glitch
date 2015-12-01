#ifndef GLITCH_DISPLAY_ILI9341_I
#define GLITCH_DISPLAY_ILI9341_I

#include "../Core/Globals.h"

#define TFT_DC      20
#define TFT_CS      21
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12

int lastMem;
int lastCpu;
unsigned long currentMillis;
void drawSteps();
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);
void initDisplay()
{
    tft.begin();
    tft.fillScreen(ILI9341_BLACK);
    tft.setRotation(3);
}

void printDebug()
{
    //tft.fillRect(0, 224, 320, 16, ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(0,224);
    tft.setTextSize(1);
    char data[256];
    sprintf (data, "CPU:%d MEM:%d SEC:%u", lastCpu, lastMem, currentMillis/1000);
    tft.print(data);
    drawSteps();
}

void drawSteps()
{
    for (int x=0; x<16; x++)
    {
        tft.drawRoundRect(x*20,0,20,20,3,ILI9341_WHITE);
        
        if (currentPosition == x)
            tft.fillRoundRect(x*20,0,20,20,3,ILI9341_RED);            
    }
}
#endif
