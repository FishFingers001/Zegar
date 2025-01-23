#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(13, 12, 27, 26, 25, 33);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    lcd.clear();
    lcd.print("Sensor error!");
    return;
  }
  lcd.clear();
  lcd.print("Wilg: ");
  lcd.print(humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  delay(2000);
}