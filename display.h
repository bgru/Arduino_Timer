#include "api/Common.h"

int selectedClock = 0;
int nextClock = 1;

bool flashing = true;
unsigned long int prevMilis;

int times_switcher = numOfTimes;


void flashing_handler() {
  if (millis() - prevMilis >= 500) {
    prevMilis = millis();
    if (flashing) {
      flashing = false;
    } else {
      flashing = true;
    }
  }
}

void clean_display() {
  lcd.setCursor(5, 0);
  lcd.print("      ");
  lcd.setCursor(5, 1);
  lcd.print("      ");
}

void display_predefined_time(int row) {
  times_switcher += 1;
  if (times_switcher >= numOfTimes) {
    times_switcher = 0;
  }

  lcd.setCursor(5, row);
  lcd.print(times_text[times_switcher]);
}

void print_total_time(int value) {
  int hours, minutes, seconds;

  seconds = value % 60;
  value /= 60;
  minutes = value;
  value /= 60;
  hours = value;

  lcd.print(hours);
  lcd.print("H");
  lcd.print(minutes);
  lcd.print("M");
  lcd.print(seconds);
  lcd.print("S");
}

void display_total_time(int clock) {
  int value;
  switch (clock) {
    case 1:
      lcd.setCursor(0, 0);
      value = clocksSum[0];
      break;
    case 2:
      lcd.setCursor(8, 0);
      value = clocksSum[1];
      break;
    case 3:
      lcd.setCursor(0, 1);
      value = clocksSum[2];
      break;
    case 4:
      lcd.setCursor(8, 1);
      value = clocksSum[3];
      break;
    default:
      return;
  }
  if (selectedClock == clock && flashing) {
    lcd.print("        ");
  } else {
    print_total_time(value);
  }
}

void print_time(int value) {
  int minutes, seconds;

  seconds = value % 60;
  value /= 60;
  minutes = value;

  if (minutes < 10) {
    lcd.print(0);
  }
  lcd.print(minutes);
  lcd.print(":");

  if (seconds < 10) {
    lcd.print(0);
  }
  lcd.print(seconds);
}

void display_time(int clock) {
  int value;
  bool sus;

  switch (clock) {
    case 1:
      lcd.setCursor(0, 0);
      value = clocks[0];
      sus = suspendedClocks[0];
      break;
    case 2:
      lcd.setCursor(11, 0);
      value = clocks[1];
      sus = suspendedClocks[1];

      break;
    case 3:
      lcd.setCursor(0, 1);
      value = clocks[2];
      sus = suspendedClocks[2];

      break;
    case 4:
      lcd.setCursor(11, 1);
      value = clocks[3];
      sus = suspendedClocks[3];
      break;
    default:
      return;
  }

  if (sus && flashing) {
    lcd.print("     ");
  } else {
    print_time(value);
  }
}
