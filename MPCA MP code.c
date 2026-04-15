#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHT11_PIN 5
#define DHTTYPE DHT11
#define SENSOR_PIN A0
#define RELAY_PIN 6

LiquidCrystal_I2C lcd(0x27, 16, 2); 
DHT dht(DHT11_PIN, DHTTYPE);

void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight(); 
  
  pinMode(SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  digitalWrite(RELAY_PIN, HIGH); 

  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(2000);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int moisture_raw = analogRead(SENSOR_PIN);
  
  int moisture_percent = map(moisture_raw, 550, 10, 0, 100);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: "); lcd.print(t, 1); lcd.print((char)223); lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humid: "); lcd.print(h, 1); lcd.print("%");
  delay(2500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moisture_percent);
  lcd.print("%");

  lcd.setCursor(0, 1);
  
  if(moisture_percent >= 45) {
    digitalWrite(RELAY_PIN, HIGH); 
    lcd.print("Motor: OFF");
  } 
  else if(moisture_percent < 30) {
    digitalWrite(RELAY_PIN, LOW); 
    lcd.print("Motor: ON");
  } 
  else {
    lcd.print("Motor: Standby");
  }

  delay(2500);
}
