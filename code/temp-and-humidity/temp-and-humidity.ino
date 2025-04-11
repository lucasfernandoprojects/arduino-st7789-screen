#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <DHT.h>

// ST7789 Display Pins
#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// DHT11 Sensor Pin
#define DHTPIN 2  // DHT11 connected to D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  // Initialize Display
  tft.init(135, 240);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  
  // Initialize DHT Sensor
  dht.begin();
}

void loop() {
  // Read Temperature & Humidity
  float temperatureC = dht.readTemperature();
  float temperatureF = temperatureC * 9.0 / 5.0 + 32.0;
  float humidity = dht.readHumidity();

  // Check if readings are valid
  if (isnan(temperatureC) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Determine temperature color
  uint16_t tempColor;
  if (temperatureC < 16) {
    tempColor = ST77XX_BLUE;
  } else if (temperatureC <= 32) {
    tempColor = ST77XX_GREEN;
  } else {
    tempColor = ST77XX_RED;
  }

  // Determine humidity color
  uint16_t humColor;
  if (humidity < 50) {
    humColor = ST77XX_RED;
  } else if (humidity <= 85) {
    humColor = ST77XX_GREEN;
  } else {
    humColor = ST77XX_BLUE;
  }

  // Display temperature in Celsius
  displayData(temperatureC, 'C', tempColor, humidity, humColor);
  delay(2000);

  // Display temperature in Fahrenheit
  displayData(temperatureF, 'F', tempColor, humidity, humColor);
  delay(2000);
}

// Function to display temperature, humidity, and message
void displayData(float temp, char unit, uint16_t tempColor, float humidity, uint16_t humColor) {
  tft.fillScreen(ST77XX_BLACK);

  // Calculate vertical centering
  int centerY = (135 + 32) / 2; // Middle of 135px screen minus half text height

  // Print Temperature
  tft.setTextSize(2);
  tft.setTextColor(tempColor);
  tft.setCursor(10, centerY - 20); // Move up slightly for centering
  tft.print("Temp: ");
  tft.print(temp);
  tft.print(" ");
  tft.print(unit);

  // Print Humidity (right below temperature)
  tft.setTextColor(humColor);
  tft.setCursor(10, centerY + 10); // Slightly below temperature
  tft.print("Humidity: ");
  tft.print(humidity);
  tft.print(" %");

  // Print bottom message in white (small size)
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(10, 120);
  tft.print("Data from DHT11 sensor");

  // Serial Monitor Output
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" ");
  Serial.print(unit);
  Serial.print(" | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}
