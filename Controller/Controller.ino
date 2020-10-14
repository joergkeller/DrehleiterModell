/*
 * Einlesen eines Näherungssensors für die Speichen eines Wagenrades einer Modelleisenbahn.
 * Wenn sich das Rad bewegt (Zug fährt), soll ein Pin auf HIGH geschaltet werden. Wenn der Sensor
 * eine gewisse Zeit kein Signal liefert (Zug hält), wird der Pin auf LOW geschaltet.
 */

#include "TimerOne.h"
#if defined(__AVR_ATtiny85__)
#include "PinChangeInterrupt.h"
#endif

#if defined(__AVR_ATtiny85__)
#define LED_OUTPUT        1   // Test mit LED for ATTINY85
#else
#define LED_OUTPUT       13   // Test mit LED for other Arduinos
#endif
#define SENSOR_INPUT	  2   // Arduino Uno/Nano/Mini: Only Pin 2/3 allowed
#define DREHLICHT_HINTEN  4
#define DREHLICHT_VORNE   5

#define MILLISECONDS   1000
#define INTERVAL      (1000 * MILLISECONDS)

int spokeCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_INPUT, INPUT);
  pinMode(LED_OUTPUT, OUTPUT);
  pinMode(DREHLICHT_HINTEN, OUTPUT);
  pinMode(DREHLICHT_VORNE, OUTPUT);
  #if defined(__AVR_ATtiny85__)
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(SENSOR_INPUT), signalIsr, CHANGE);
  #else
    attachInterrupt(digitalPinToInterrupt(SENSOR_INPUT), signalIsr, CHANGE);
  #endif
  Timer1.initialize(INTERVAL);
  Timer1.attachInterrupt(timerIsr);
}

/*
 * Zählt die Speichen, die vom Näherungssensor gemeldet werden.
 * Jede Speiche wird doppelt gezählt, da sowohl die Rising- wie auch die Falling-Flanke
 * des Signals einen Interrupt auslöst. Dies wurde so eingestellt, damit auch kleine Bewegungen
 * des Wagenrades bemerkt werden.
 */
void signalIsr(void) {
  spokeCount += 1;
}

/*
 * Prüft ob innerhalb des definierte Intervalls eine Bewegung des Rades stattgefunden hat.
 * Entsprechend wird der Modus des Wagens (fährt, stoppt) gesetzt. Anschliessend wird der
 * Zähler wieder auf 0 gesetzt.
 */
void timerIsr(void) {
  trainStopped(spokeCount == 0);
  spokeCount = 0;
}

/*
 * Der Modus des Wagens wird auf "fährt" oder "wartet" gesetzt.
 */
void trainStopped(bool stopped) {
  digitalWrite(LED_OUTPUT, stopped ? LOW : HIGH);
  digitalWrite(DREHLICHT_VORNE, stopped ? LOW : HIGH);
  digitalWrite(DREHLICHT_HINTEN, stopped ? LOW : HIGH);
  Serial.println(stopped ? "wartet" : "fährt");
}

void loop() {
  // nop
}