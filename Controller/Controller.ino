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
  trainHas(spokeCount == 0);
  spokeCount = 0;
}

/*
 * Der Modus des Wagens wird auf "fährt" oder "wartet" gesetzt.
 */
void trainHas(bool stopped) {
  digitalWrite(SIGNAL_OUTPUT, stopped ? LOW : HIGH);
  Serial.println(stopped ? "wartet" : "fährt");
}

void loop() {
  // nop
}