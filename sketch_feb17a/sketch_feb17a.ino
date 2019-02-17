#include <Adafruit_ssd1306syp.h>

// Light Sensor
int sensorPin = A0;    // select the input pin for the potentiometer
float rawRange = 1024; // 3.3v
float logRange = 5.0; // 3.3v = 10^5 lux

// Moisture Sensor
#include "Adafruit_seesaw.h"
Adafruit_seesaw ss;

// OLED
#define SDA_PIN 9
#define SCL_PIN 8
Adafruit_ssd1306syp display(SDA_PIN,SCL_PIN);

void setup()
{
  // Light Sensor
  analogReference(EXTERNAL);
  Serial.begin(115200);
  Serial.println("Adafruit Analog Light Sensor Test");

  // Moisture Sensor
  Serial.println("seesaw Soil Sensor example!");
  if (!ss.begin(0x36)) 
  {
    Serial.println("ERROR! seesaw not found");
    while(1);
  } 
  else 
  {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }
  
  // OLED
  delay(1000);
  display.initialize(); 
}

void loop() 
{
  // Light Sensor
  // read the raw value from the sensor:
  int rawValue = analogRead(sensorPin);    
  
  Serial.print("Raw = ");
  Serial.print(rawValue);
  Serial.print(" - Lux = ");
  Serial.println(RawToLux(rawValue)); 

  // Moisture Sensor
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  Serial.print("Temperature: "); 
  Serial.print(tempC); 
  Serial.println("*C");
  Serial.print("Capacitive: ");
  Serial.println(capread);
  
  // OLED
  display.clear();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  display.print("Raw = ");
  display.println(rawValue);
  display.print("Lux = ");
  display.println(RawToLux(rawValue)); 

  display.print("Temperature: "); 
  display.print(tempC); 
  display.println("*C");
  display.print("Capacitive: ");
  display.println(capread);
  
  display.update();
  // delay(5000);
  // display.clear();

  delay(3000);
}

// Light Sensor
float RawToLux(int raw)
{
  float logLux = raw * logRange / rawRange;
  return pow(10, logLux);
}

// Moisture Sensor

  
// OLED
