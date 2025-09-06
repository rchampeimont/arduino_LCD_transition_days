// Code designed for Arduino Uno R3

#include <LiquidCrystal.h>
#include <EEPROM.h>

// Connections to the circuit: LCD screen
const int LCD_RS_PIN = 7;
const int LCD_ENABLE_PIN = 6;
const int LCD_DATA_PIN_D4 = 5;
const int LCD_DATA_PIN_D5 = 4;
const int LCD_DATA_PIN_D6 = 3;
const int LCD_DATA_PIN_D7 = 2;
const int LCD_BACKLIGHT_RED = 9;
const int LCD_BACKLIGHT_GREEN = 10;
const int LCD_BACKLIGHT_BLUE = 11;

LiquidCrystal lcd(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_DATA_PIN_D4, LCD_DATA_PIN_D5, LCD_DATA_PIN_D6, LCD_DATA_PIN_D7);

const int LCD_ROWS = 2;
const int LCD_COLS = 16;

const int EEPROM_ADDR = 50;

const unsigned long INCREMENT_EVERY = 3600000; // 1 hour;
//const unsigned long INCREMENT_EVERY = 10000; // just for testing

void updateEepromIfNecessary(unsigned long newValue) {
  unsigned long readValue;
  EEPROM.get(EEPROM_ADDR, readValue);
  Serial.print("Read ");
  Serial.println(readValue);
  if (readValue != newValue) {
    EEPROM.put(EEPROM_ADDR, newValue);
    Serial.print("Wrote ");
    Serial.println(newValue);

    EEPROM.get(EEPROM_ADDR, readValue);
    Serial.print("Read ");
    Serial.println(readValue);
  } else {
    Serial.print("No update needed");
  }
}

// value from 0 to 256*6-1
void setRainbowColor(int value) {
  int internalValue;
  if (value < 256) { // green rises
    internalValue = value;
    analogWrite(LCD_BACKLIGHT_RED, 0);
    analogWrite(LCD_BACKLIGHT_GREEN, 255 - internalValue);
    analogWrite(LCD_BACKLIGHT_BLUE, 255);
  } else if (value < 256*2) { // red falls
    internalValue = value - 256;
    analogWrite(LCD_BACKLIGHT_RED, internalValue);
    analogWrite(LCD_BACKLIGHT_GREEN, 0);
    analogWrite(LCD_BACKLIGHT_BLUE, 255);
  } else if (value < 256*3) { // blue rises
    internalValue = value - 256*2;
    analogWrite(LCD_BACKLIGHT_RED, 255);
    analogWrite(LCD_BACKLIGHT_GREEN, 0);
    analogWrite(LCD_BACKLIGHT_BLUE, 255 - internalValue);
  } else if (value < 256*4) { // green falls
    internalValue = value - 256*3;
    analogWrite(LCD_BACKLIGHT_RED, 255);
    analogWrite(LCD_BACKLIGHT_GREEN, internalValue);
    analogWrite(LCD_BACKLIGHT_BLUE, 0);
  } else if (value < 256*5) { // red rises again
    internalValue = value - 256*4;
    analogWrite(LCD_BACKLIGHT_RED, 255 - internalValue);
    analogWrite(LCD_BACKLIGHT_GREEN, 255);
    analogWrite(LCD_BACKLIGHT_BLUE, 0);
  } else if (value < 256*6) { // blue falls
    internalValue = value - 256*5;
    analogWrite(LCD_BACKLIGHT_RED, 0);
    analogWrite(LCD_BACKLIGHT_GREEN, 255);
    analogWrite(LCD_BACKLIGHT_BLUE, internalValue);
  }
}

void setup() {
  // for debug
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Started");
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LCD_BACKLIGHT_RED, OUTPUT);
  pinMode(LCD_BACKLIGHT_GREEN, OUTPUT);
  pinMode(LCD_BACKLIGHT_BLUE, OUTPUT);

  digitalWrite(LED_BUILTIN, 0);
  analogWrite(LCD_BACKLIGHT_RED, 0);
  analogWrite(LCD_BACKLIGHT_GREEN, 140);
  analogWrite(LCD_BACKLIGHT_BLUE, 140);

  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.clear();

  // Uncomment to manually load/change initial value (days * 24 + hrs)
  //updateEepromIfNecessary(678* 24 + 21); digitalWrite(LED_BUILTIN, 1);
  // Then comment and upload AGAIN because you don't want to reset the
  // date each time Arduino restarts. Off internal LED indicates that it's good.
}

void loop() {
  unsigned long hoursSinceTransition;
  EEPROM.get(EEPROM_ADDR, hoursSinceTransition);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(hoursSinceTransition / 24);
  lcd.print(" days ");

  double yrs = hoursSinceTransition / 24 / 365.25;
  lcd.print(yrs);
  lcd.print(" yr");

  lcd.setCursor(0, 1);
  int coloredCell = ((hoursSinceTransition % 24) * 16) / 24;
  for (int i=0; i<=coloredCell; i++) {
    lcd.write(0xFF);
  }

  setRainbowColor(((hoursSinceTransition % 24) * 6*256) / 24);
  
  delay(INCREMENT_EVERY); // 1 hour

  hoursSinceTransition++;
  updateEepromIfNecessary(hoursSinceTransition);
}
