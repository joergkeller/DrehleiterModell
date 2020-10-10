/*
 * Einlesen eines Näherungssensors für die Speichen eines Wagenrades einer Modelleisenbahn.
 * Wenn sich das Rad bewegt (Zug fährt), soll ein Pin auf HIGH geschaltet werden. Wenn der Sensor
 * eine gewisse Zeit kein Signal liefert (Zug hält), wird der Pin auf LOW geschaltet.
 */

#include <TimerOne.h>

#define SENSOR_INPUT	2   // Arduino Uno/Nano/Mini: Only Pin 2/3 allowed
#define SIGNAL_OUTPUT  13   // Test mit LED

#define MILLISECONDS 1000
#define INTERVAL     1000 * MILLISECONDS

int spokeCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_INPUT, INPUT);
  pinMode(SIGNAL_OUTPUT, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR_INPUT), signalIsr, CHANGE);
  Timer1.initialize(INTERVAL);
  Timer1.attachInterrupt(timerIsr);
}

/*
 * Zählt die Speichen, die vom Näherungssensor gemeldet werden.
 * Jede Speiche wird doppelt gezählt, da sowohl die Rising- wie auch die Falling-Flanke
 * des Signals einen Interrupt auslöst. Dies wurde so eingestellt, damit auch kleine Bewegungen
 * des Wagenrades bemerkt werden. Der Modus des Wages wird sofort auf "fährt" gesetzt.
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
 */
void trainMoving(bool moving) {
  digitalWrite(SIGNAL_OUTPUT, moving ? HIGH : LOW);
  Serial.println(moving ? "fährt" : "wartet");
}

void loop() {
  // nop
}