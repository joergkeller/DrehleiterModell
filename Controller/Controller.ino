/*
 * Einlesen eines Näherungssensors für die Speichen eines Wagenrades einer Modelleisenbahn.
 * Wenn sich das Rad bewegt (Zug fährt), sollen zwei Pins (für Drehlichter) auf HIGH geschaltet werden.
 * Wenn der Sensor eine gewisse Zeit kein Signal liefert (Zug hält), wird der Pin auf LOW geschaltet.
 */

#include "TimerOne.h"
#if defined(__AVR_ATtiny85__)
#include "PinChangeInterrupt.h"
#endif

#if defined(__AVR_ATtiny85__)
#define LED_OUTPUT        1   // LED für ATtiny85
#else
#define LED_OUTPUT       13   // LED für andere Arduinos
#endif
#define SENSOR_INPUT	  2   // Arduino Uno/Nano/Mini: Nur Pin 2/3 erlaubt, ATtiny85 kann alle Pins benutzen
#define DREHLICHT_HINTEN  4
#define DREHLICHT_VORNE   5

#define MILLISECONDS   1000L
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
  trainMoving(true);
}

/*
 * Prüft ob innerhalb des definierte Intervalls eine Bewegung des Rades stattgefunden hat.
 * Entsprechend wird der Modus des Wagens (fährt, stoppt) gesetzt. Anschliessend wird der
 * Zähler wieder auf 0 gesetzt.
 */
void timerIsr(void) {
  trainMoving(spokeCount != 0);
  spokeCount = 0;
}

/*
 * Der Modus des Wagens wird auf "fährt" oder "wartet" gesetzt.
 * Es werden zwei Pins geschaltet, um genügend Leistung für die Drehlichter zu erzeugen.
 */
void trainMoving(bool moving) {
  #if defined SHOW_LED
    digitalWrite(LED_OUTPUT, moving ? HIGH : LOW);
  #endif
  digitalWrite(DREHLICHT_VORNE, moving ? HIGH : LOW);
  digitalWrite(DREHLICHT_HINTEN, moving ? HIGH : LOW);
  Serial.println(moving ? "fährt" : "wartet");
}

void loop() {
  // nop
}