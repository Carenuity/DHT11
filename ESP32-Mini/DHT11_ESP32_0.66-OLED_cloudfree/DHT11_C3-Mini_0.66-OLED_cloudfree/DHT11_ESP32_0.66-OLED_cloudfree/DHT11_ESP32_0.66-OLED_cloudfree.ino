#include "DHT.h"  // DHT Library
#include <Wire.h>
#include <U8g2lib.h>  // Include the U8g2 library for OLED display

// Define the resolution of your 0.66" OLED (64x48)
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 48

// Setup U8g2 library with D1 (SCL) and D2 (SDA) pins for SSD1306 OLED
U8G2_SSD1306_64X48_ER_F_SW_I2C u8g2(U8G2_R0, /* clock=*/22, /* data=*/21, /* reset=*/U8X8_PIN_NONE);

// Pin to which the DHT11 sensor is connected. On D1 Mini, use D4.
const int DHTPIN = 16;

// Specify the type of DHT sensor being used.
#define DHTTYPE DHT11

// Initialize the sensor with the pin and type.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  // Begin serial communication at 9600 Baud.
  Wire.begin();

  u8g2.begin();  // Initialize OLED display
  dht.begin();   // Initialize DHT sensor
}

void loop() {
  // The DHT11 sensor provides a new reading every 2 seconds,
  // so there's no need to constantly loop in the program.
  delay(2000);

  // Read humidity value.
  float humidity = dht.readHumidity();
  // Read temperature in Celsius.
  float temperatureC = dht.readTemperature();

  // Check if the values were read successfully.
  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println("Error reading data from DHT11 sensor.");
    return;
  }

  u8g2.clearBuffer();  // Clear the display buffer

  // Set font and display values on OLED for a 0.66" 64x48 screen
  u8g2.setFont(u8g2_font_6x10_tf);  // Use 6x10 font

  // Display Temperature in Celsius
  u8g2.setCursor(0, 8);     // Set cursor position for temperature
  u8g2.print("Temperature: ");      // Display label
  u8g2.setCursor(10, 20);     // Set cursor position for temperature
  u8g2.print(temperatureC);  // Display temperature
  u8g2.print(" C");

  // Display Humidity
  u8g2.setCursor(0, 33);  // Set cursor position for humidity
  u8g2.print("Humidity: ");    // Display label
    u8g2.setCursor(10, 45);  // Set cursor position for humidity
  u8g2.print(humidity);   // Display humidity
  u8g2.print(" %");

  u8g2.sendBuffer();  // Send the display buffer to the OLED

  // Print the values to Serial Monitor as well
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(1000);  // Update every 2 seconds
}
