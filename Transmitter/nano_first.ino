#include <avr/sleep.h>
#include <avr/power.h>

const int commonPin = 2;
const int buttonPins[] = { 4, 5, 6, 7 };
const int ledPin1 = 8;  // First LED pin, change to your desired pin
const int extModul = 3;  // Power up Ext modul

unsigned long lastFire = 0;
int status = 0;

void setup() {
  pinMode(commonPin, INPUT_PULLUP);

  pinMode(ledPin1, OUTPUT);     // Initialize first LED pin
  digitalWrite(ledPin1, LOW);  // Turn on LED 1

  pinMode(extModul, OUTPUT);    // Initialize second LED pin
  digitalWrite(extModul, LOW);  // Turn off module

  Serial.begin(9600);
  configureCommon();
  attachInterrupt(digitalPinToInterrupt(commonPin), pressInterrupt, FALLING);

  Serial.println("Initialization finished");

  delay(1000);                  // Wait for 2 seconds
  digitalWrite(ledPin1, HIGH);  // Turn off LED 1
}

void loop() {
  if (millis() - lastFire > 1500) {  // Stay wake up few seconds
    digitalWrite(extModul, LOW);     // Turn off module

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
  }

  delay(10);
}

void pressInterrupt() {
  sleep_disable();
  power_all_enable();

  digitalWrite(extModul, HIGH);  // Turn module

  if (millis() - lastFire < 300) {  // DEBOUNDE
    return;
  }
  lastFire = millis();

  configureDistinct();

  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) {
    if (!digitalRead(buttonPins[i])) {
      if (i >= 0 && i < 5) {
        digitalWrite(ledPin1, LOW);  // Turn on LED 1
        delay(800);
        Serial.print(i + 1);
        digitalWrite(ledPin1, HIGH);  // Turn off LED 1
      }
    }
  }

  configureCommon();
}

void configureCommon() {
  pinMode(commonPin, INPUT_PULLUP);

  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) {
    pinMode(buttonPins[i], OUTPUT);
    digitalWrite(buttonPins[i], LOW);
  }
}

void configureDistinct() {
  pinMode(commonPin, OUTPUT);
  digitalWrite(commonPin, LOW);

  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}
