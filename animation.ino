//8x8 LED Grid Animation with a Pulse Sensor Input

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <PulseSensorPlayground.h>

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
const int buttonPin = 2;
int buttonState = 0;
const int PulseWire = A0;
const int LED = LED_BUILTIN;  // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;          // Determine which Signal to "count as a beat" and which to ignore.


PulseSensorPlayground pulseSensor;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  matrix.begin(0x70);  // pass in the address

  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED);  //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);

  // Double-check the "pulseSensor" object was created and "began" seeing a signal.
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.
  }
}

static const uint8_t PROGMEM
  run1_bmp[] = { B00011000,
                 B00011010,
                 B11110110,
                 B10010000,
                 B00011110,
                 B11110010,
                 B00000010,
                 B00000010 },
  run2_bmp[] = { B00011000,
                 B00011000,
                 B01110110,
                 B01010000,
                 B00011110,
                 B00110010,
                 B11000100,
                 B00000000 },
  run3_bmp[] = { B00011000,
                 B00011000,
                 B01110100,
                 B00010110,
                 B00010000,
                 B00110000,
                 B01110000,
                 B00010000 },
  run4_bmp[] = { B00011000,
                 B00011000,
                 B01110100,
                 B00010110,
                 B00010000,
                 B00011000,
                 B00010100,
                 B00011000 },
  heart0_bmp[] = { B00000000,
                   B00000000,
                   B00101000,
                   B00111000,
                   B00010000,
                   B00000000,
                   B00000000,
                   B00000000 },
  heart1_bmp[] = { B00000000,
                   B00000000,
                   B00101000,
                   B01111100,
                   B00111000,
                   B00010000,
                   B00000000,
                   B00000000 },
  heart2_bmp[] = { B00000000,
                   B00000000,
                   B01101100,
                   B11111110,
                   B01111100,
                   B00111000,
                   B00010000,
                   B00000000 };
void loop() {
  int myBPM = 0;
  if (pulseSensor.sawStartOfBeat()) {              // Constantly test to see if "a beat happened".
    myBPM = pulseSensor.getBeatsPerMinute();       // Calls function on our pulseSensor object that returns BPM as an "int".
                                                   // "myBPM" hold this BPM value now.
    Serial.println("♥  A HeartBeat Happened ! ");  // If test is "true", print a message "a heartbeat happened".
    Serial.print("BPM: ");                         // Print phrase "BPM: "
    // Serial.println(myBPM);                         // Print the value inside of myBPM.
  }

  delay(20);  // considered best practice in a simple sketch.
  Serial.println(myBPM);
  int delayTime = 0;
  delayTime = map(myBPM, 1, 300, 200, 0);
  if (delayTime != 0) {
    matrix.clear();
    matrix.drawBitmap(0, 0, run1_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(delayTime);

    matrix.clear();
    matrix.drawBitmap(0, 0, run2_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(delayTime);

    matrix.clear();
    matrix.drawBitmap(0, 0, run3_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(delayTime);

    matrix.clear();
    matrix.drawBitmap(0, 0, run4_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(delayTime);

    matrix.clear();
    matrix.drawBitmap(0, 0, run2_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(delayTime);

    matrix.clear();
    matrix.drawBitmap(0, 0, run1_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(delayTime);
  } else {
    matrix.clear();
    matrix.drawBitmap(0, 0, run1_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(delayTime);
  }
  if (buttonState == HIGH) {
    matrix.clear();
    matrix.drawBitmap(0, 0, heart0_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(delayTime);

    matrix.clear();
    matrix.drawBitmap(0, 0, heart1_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(delayTime);

    matrix.clear();
    matrix.drawBitmap(0, 0, heart2_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(delayTime);

    matrix.clear();
    matrix.drawBitmap(0, 0, heart2_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(delayTime);

    matrix.clear();
    matrix.drawBitmap(0, 0, heart1_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(delayTime);

    matrix.clear();
    matrix.drawBitmap(0, 0, heart0_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(delayTime);
  }
}