# Arduino LCD Transition Days
An Arduino project to show the number of days since my transition on an LCD screen

## LCD Rainbow Test
This is a small demo of changing the LCD screen backlight colors going through the rainbow.

See LCD_rainbow folder.

## LCD Transition Days
This is the main project. It shows the number of days since my transition started.

Features:
* Saves in EEPROM the numbers of hours since transition, so that if Arduino is restart it looses at most 1 hour.
  * The 1 hour resolution is a tradeoff betweem accuracy and EEPROM life which is limited to 100,000 write cycles (cf https://docs.arduino.cc/learn/built-in-libraries/eeprom/). This ensures that the program can run for about 10 years before the EEPROM is burnt.
