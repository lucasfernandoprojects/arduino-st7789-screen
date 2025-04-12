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
  Serial.println("ST7789 Display Test");
  
  pinMode(TFT_BLK, OUTPUT);
  analogWrite(TFT_BLK, 255);  // Set backlight to full brightness (0-255)

  tft.init(135, 240);
  tft.setRotation(3);  // Adjust rotation if needed
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("Hello, Arduino!");
}

void loop() {
  // Example: Dim the backlight over time
  for (int i = 255; i >= 0; i -= 5) {
    analogWrite(TFT_BLK, i);
  }
}
