#include "api/Common.h"

bool showTimeTotal = false;

// button 1 - cycle clocks                                                        / cycle total time clocks
// button 2 - cycle predefined times
// button 3 - pause  / select predefined time (RESET as a predefined time =  0)   / reset selected total clock time
// button 4 - toggle show total time

bool kill_buzzer() {
  if (buzzer) {
    buzzer = false;
    for (int i = 0; i < 4; i++) {
      if (clocks[i] == 0 && suspendedClocks[i]) {
        suspendedClocks[i] = false;
      }
    }
    delay(120);
    return true;
  }
  return false;
}


//=========================================================
void button_choose() {
  const int pin = BUTTON_1;

  int row, column;

  if (digitalRead(pin) == LOW) {
    delay(20);
    if (kill_buzzer())
      return;


    selectedClock = nextClock;
    if (!showTimeTotal) {

      clean_display();
      times_switcher = numOfTimes;

      switch (selectedClock) {
        case 1:
          row = 0;
          column = 6;
          nextClock = 2;
          break;
        case 2:
          row = 0;
          column = 9;
          nextClock = 3;
          break;
        case 3:
          row = 1;
          column = 6;
          nextClock = 4;
          break;
        case 4:
          row = 1;
          column = 9;
          nextClock = 0;
          break;
        case 0:
          nextClock = 1;
          break;
        default:
          return;
      }

      if (selectedClock == 1 || selectedClock == 3) {
        lcd.setCursor(column, row);
        lcd.write(0);
        lcd.setCursor(column + 1, row);
        lcd.write(2);
      } else if (selectedClock == 2 || selectedClock == 4) {
        lcd.setCursor(column, row);
        lcd.write(1);
        lcd.setCursor(column - 1, row);
        lcd.write(2);
      }
    } else {
      switch (selectedClock) {
        case 1:
          nextClock = 2;
          break;
        case 2:
          nextClock = 3;
          break;
        case 3:
          nextClock = 4;
          break;
        case 4:
          nextClock = 0;
          break;
        case 0:
          nextClock = 1;
          break;
        default:
          return;
      }
    }



    while (digitalRead(pin) == LOW) {}
    delay(20);
  }
}


//=========================================================
void time_choose() {
  const int pin = BUTTON_2;

  if (digitalRead(pin) == LOW) {
    delay(20);
    if (kill_buzzer())
      return;


    if (selectedClock == 1 || selectedClock == 2) {
      display_predefined_time(1);
    } else if (selectedClock == 3 || selectedClock == 4) {
      display_predefined_time(0);
    }

    while (digitalRead(pin) == LOW) {}
    delay(20);
  }
}



//=========================================================
void button_pause_select() {
  const int pin = BUTTON_3;


  if (digitalRead(pin) == LOW) {
    delay(20);
    if (kill_buzzer())
      return;

    if (!showTimeTotal) {
      if (selectedClock != 0 && times_switcher != numOfTimes) {  // select predefined time, start timer
        clocks[selectedClock - 1] = times[times_switcher];
        clocksTimeStart[selectedClock - 1] = millis();
        suspendedClocks[selectedClock - 1] = false;
        // clocksSum[selectedClock-1] += times[times_switcher]; // wrong
        selectedClock = 0;
        nextClock = 1;
        clean_display();
      } else if (selectedClock != 0) {  // pause selected timer
        if (suspendedClocks[selectedClock - 1]) {
          suspendedClocks[selectedClock - 1] = false;
          clocksTimeStart[selectedClock - 1] = millis();
        } else {
          suspendedClocks[selectedClock - 1] = true;
        }
      }
    } else if (showTimeTotal) {
      clocksSum[selectedClock - 1] = 0;
    }

    while (digitalRead(pin) == LOW) {}
    delay(20);
  }
}



//=========================================================
void button_show() {
  const int pin = BUTTON_4;


  if (digitalRead(pin) == LOW) {
    delay(20);
    if (kill_buzzer())
      return;

    if (showTimeTotal) {
      showTimeTotal = false;
      selectedClock = 0;
      nextClock = 1;
      clean_display();
    } else {
      showTimeTotal = true;
      selectedClock = 0;
      nextClock = 1;
      lcd.clear();
    }

    while (digitalRead(pin) == LOW) {}
    delay(20);
  }
}
