#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8
#define TFT_BLK    7  // Backlight pin

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  Serial.println("ST7789 Fast Animation Test");

  pinMode(TFT_BLK, OUTPUT);
  analogWrite(TFT_BLK, 255);  // Full brightness

  tft.init(135, 240);
  tft.setRotation(3);  // Landscape
  tft.fillScreen(ST77XX_BLACK);
}

// Convert HSV to RGB565 for ST7789
uint16_t hsvToRGB(float h, float s, float v) {
  float r, g, b;

  int i = int(h * 6);
  float f = h * 6 - i;
  float p = v * (1 - s);
  float q = v * (1 - f * s);
  float t = v * (1 - (1 - f) * s);

  switch (i % 6) {
    case 0: r = v, g = t, b = p; break;
    case 1: r = q, g = v, b = p; break;
    case 2: r = p, g = v, b = t; break;
    case 3: r = p, g = q, b = v; break;
    case 4: r = t, g = p, b = v; break;
    case 5: r = v, g = p, b = q; break;
  }

  uint8_t R = r * 255;
  uint8_t G = g * 255;
  uint8_t B = b * 255;

  return tft.color565(R, G, B);
}

void loop() {
  static float hueOffset = 0.0;

  for (int x = 0; x < tft.width(); x += 10) {
    for (int y = 0; y < tft.height(); y += 10) {
      float hue = fmod((float)x / tft.width() + (float)y / tft.height() + hueOffset, 1.0);
      uint16_t color = hsvToRGB(hue, 1.0, 1.0);
      tft.fillRect(x, y, 10, 10, color);
    }
  }

  hueOffset += 0.05;  // Faster transition
  if (hueOffset > 1.0) hueOffset -= 1.0;

  // No delay = max framerate (about 20-30 FPS on most Arduinos)
}
