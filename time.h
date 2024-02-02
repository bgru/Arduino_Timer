#include "api/Common.h"
int times[] = { 0, 5, 60, 180, 300, 900, 1800, 3600 };
const int numOfTimes = 8;

arduino::String times_text[] = { "RESET", " 5 S  ", " 1 M  ", " 3 M  ", " 5 M  ", " 15 M ", " 30 M ", " 1 H  ", "      " };
const int numOfTimes_text = 9;

int clocks[] = { 0, 0, 0, 0 };
int clocksSum[] = { 0, 0, 0, 0 };
unsigned long int clocksTimeStart[] = { 0, 0, 0, 0 };
bool suspendedClocks[] = { false, false, false, false };

bool buzzer = false;


void timeflow() {
  for (int i = 0; i < 4; i++) {
    if (clocks[i] != 0 && !suspendedClocks[i]) {
      if (millis() >= clocksTimeStart[i]) {
        clocks[i] -= 1;
        if (clocks[i]== 0){
          buzzer = true;
          suspendedClocks[i] = true;
        }
        clocksSum[i] += 1;
        clocksTimeStart[i] += 1000;
      }
    }
  }
}