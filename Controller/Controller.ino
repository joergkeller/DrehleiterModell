/*
 * Einlesen eines Näherungssensors für die Speichen eines Wagenrades einer Modelleisenbahn.
 * Wenn sich das Rad bewegt (Zug fährt), soll ein Pin auf HIGH geschaltet werden. Wenn der Sensor
 * eine gewisse Zeit kein Signal liefert (Zug hält), wird der Pin auf LOW geschaltet.
 */

#include <TimerOne.h>

#define SENSOR_INPUT	2   // Arduino Uno/Nano/Mini: Only Pin 2/3 allowed
#define SIGNAL_OUTPUT  13   // Test mit LED
#define INTERVAL     1000   // millisecond

int spokeCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_INPUT, INPUT);
  pinMode(SIGNAL_OUTPUT, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR_INPUT), signalIsr, CHANGE);
  Timer1.initialize(INTERVAL);
  Timer1.attachInterrupt(timerIsr);
}

void signalIsr(void) {
  spokeCount += 1;
}

void timerIsr(void) {
  trainHas(spokeCount == 0);
  spokeCount = 0;
}

void trainHas(bool stopped) {
  digitalWrite(SIGNAL_OUTPUT, stopped ? LOW : HIGH);
  Serial.println(stopped ? "wartet" : "fährt");
}

void loop() {
  // nop
}