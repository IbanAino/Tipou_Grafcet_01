#include "stdint.h" // include all variables types like "uint8_t"

//-----------------------
//------ VARIABLES ------
//-----------------------

//static uint8_t buffer[1024];


//-----------------------
//------ FUNCTIONS ------
//-----------------------

//void ssd1306_command(uint8_t c);
void screenDisplay();
void InitializeDisplay();
void clearDisplay();

// drawPixel(pixel's position on width, pixel's position on height)
void drawPixel(int16_t x, int16_t y);

// drawPixel(first pixel position on width,
//           first pixel position on height,
//           image: array of bytes,
//           image width in pixels,
//           image height in pixels)

void drawBitmap(int16_t x,
                int16_t y,
                const uint8_t bitmap[],
                int16_t w, int16_t h);
                
