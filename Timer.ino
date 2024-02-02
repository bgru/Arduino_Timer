#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <string.h>
// 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BUTTON_1 2
#define BUTTON_2 3
#define BUTTON_3 4
#define BUTTON_4 5
#define BUZZER_PIN 12

#include "time.h"
#include "display.h"
#include "button_logic.h"
#include "custom_chars.h"

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.createChar(0, arrowHeadLeft);
  lcd.createChar(2, arrowTail);
  lcd.createChar(1, arrowHeadRight);
}


void loop() {

  flashing_handler();

  button_choose();
  time_choose();
  button_pause_select();
  button_show();

  timeflow();
  for (int i = 1; i <= 4; i++) {
    if (showTimeTotal) {
      display_total_time(i);
    } else {
      display_time(i);
    }
  }

  if (buzzer) {
    tone(BUZZER_PIN, 150, 100);
  }
}