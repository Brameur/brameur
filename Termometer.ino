#include "SevSeg.h"
SevSeg sevseg;


const int sensorPin = A4;
float sensorValue;
float voltageOut;
float temperatureC;
float temperatureF;
float temperatureK;

const int Stand1Button = 5;
const int PWM_Pin = 9;

int PreviousMillis = millis();
int PreviousMillis1 = millis();
int PreviousMillis2 = millis();

byte PWM_out_Level;
int PercentValue;
int ButtonValue;

void setup() {

  sevseg.refreshDisplay();

  pinMode(Stand1Button, INPUT_PULLUP);
  pinMode(PWM_Pin, OUTPUT);

  pinMode(sensorPin, INPUT);

  Serial.begin(9600);

  byte numDigits = 4;
  byte digitPins[] = { A0, A1, A2, A3 };
  byte segmentPins[] = { 6, 7, 8, 9, 10, 11, 12, 13 };
  bool resistorsOnSegments = true;
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = false;  // Default 'false' is Recommended
  bool leadingZeros = false;      // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false;   // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);

  PWM_out_Level = 0;
}

void loop() {

  sevseg.refreshDisplay();

int CurrentMillis = millis();

  if (CurrentMillis - PreviousMillis >= 1000) {

    sensorValue = analogRead(sensorPin);
    voltageOut = (sensorValue * 5000) / 1024;
    // calculate temperature for LM335
    temperatureK = voltageOut / 10;
    temperatureC = temperatureK - 273;
    temperatureF = (temperatureC * 1.8) + 32;
    Serial.print("Temperature(ºC): ");
    Serial.print(temperatureC);
    Serial.print("  Temperature(ºF): ");
    Serial.print(temperatureF);
    Serial.print("  Voltage(mV): ");
    Serial.println(voltageOut);

    sevseg.setNumber(temperatureC);

    PreviousMillis = millis();
  }
}




//   if (digitalRead(Stand1Button) == 0 && ButtonValue == 1) {
//     // sevseg.refreshDisplay();
//     Serial.println("Value = 0");
//     ButtonValue = !ButtonValue;
//     sevseg.setNumber(0);
//     delay(200);
//   }

//   if (digitalRead(Stand1Button) == 0 && ButtonValue == 0) {
//     // sevseg.refreshDisplay();
//     Serial.println("Value = 1");
//     ButtonValue = !ButtonValue;
//     sevseg.setNumber(1);
//     delay(200);
//   }
// }






//   static unsigned long timer = millis();
//   static int deciSeconds = 0;

//   if (millis() - timer >= 100) {
//     timer += 100;
//     deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond

//     if (deciSeconds == 10000) { // Reset to 0 after counting for 1000 seconds.
//       deciSeconds=0;
//     }
//     sevseg.setNumber(deciSeconds, 1);
//   }

//   sevseg.refreshDisplay(); // Must run repeatedly
// }
