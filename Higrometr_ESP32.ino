#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define BUTTON_PIN 32
#define DEBOUNCE_DELAY 50

bool mode = false;  // false = Humidity Mode, true = Time Mode
unsigned long lastDebounceTime = 0;
bool lastButtonState = HIGH;

LiquidCrystal lcd(13, 12, 27, 26, 25, 33);

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Use internal pull-up resistor
  lcd.begin(16, 2);
  displayHumidity();  // Show initial message
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  bool reading = digitalRead(BUTTON_PIN);

  if (reading == LOW && lastButtonState == HIGH && millis() - lastDebounceTime > DEBOUNCE_DELAY) {
        lastDebounceTime = millis();
        mode = !mode;  // Toggle mode
        updateDisplay();  // Update LCD
    }
    lastButtonState = reading;

}
void updateDisplay(){
  lcd.clear();
  if (mode) {
    displayTime();
  }
  else {
    displayHumidity();
  }
}
void displayTime() {
  lcd.setCursor(0, 0);
  lcd.print("Czas");
}
void displayHumidity() {
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

