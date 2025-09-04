// Code designed for Arduino Uno R3

// Connections to the circuit: LCD screen backlight
const int LCD_BACKLIGHT_RED = 9;
const int LCD_BACKLIGHT_GREEN = 10;
const int LCD_BACKLIGHT_BLUE = 11;

void setup() {
  pinMode(LCD_BACKLIGHT_RED, OUTPUT);
  pinMode(LCD_BACKLIGHT_GREEN, OUTPUT);
  pinMode(LCD_BACKLIGHT_BLUE, OUTPUT);
}

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

int color = 0;

void loop() {
  setRainbowColor(color);
  color++;
  if (color > 256*6) {
    color = 0;
  }
  delay(10);
}
