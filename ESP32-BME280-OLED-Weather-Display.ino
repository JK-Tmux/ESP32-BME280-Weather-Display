#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_BME280 bme;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  if (!bme.begin(0x76)) {
    Serial.println("BME280 not found!");
    while (1);
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("BME280 Ready");
  display.display();
  delay(1000);
}

void loop() {
  float tempC = bme.readTemperature();
  float tempF = (tempC * 9.0 / 5.0) + 32.0;
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("BME280 Weather");

  display.setTextSize(2);
  display.setCursor(0, 16);
  display.print(tempF, 1);
  display.println(" F");

  display.setTextSize(1);
  display.setCursor(0, 42);
  display.print("Humidity: ");
  display.print(humidity, 1);
  display.println("%");

  display.setCursor(0, 54);
  display.print("Pressure: ");
  display.print(pressure, 1);
  display.print(" hPa");

  display.display();

  delay(2000);
}