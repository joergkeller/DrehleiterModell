# Design Notizen

## 2020-10-09 Erster Versuch
Ich würde die Speichendurchgänge mit einem Interrupt zählen. 
Das macht dich unabhängig von allem anderen das läuft. 
Dazu kannst du auf Nano allerdings nur die Pins 2/3 nutzen. 

Mit einem Timer prüfst du zB alle 1000ms den Zählerstand. 
Das ist etwas unflexibel, wenn der Zug stoppt, dauert es 1..2 sec, bis der Stillstand gemeldet wird. Wenn er losfährt 0..1 sec bis Meldung. Verbesserung ist möglich. 

Gib mir eine Nachricht, ob das so klappt (bin in den Ferien und habe kein Board).

## 2020-10-10 Erster Speichendurchgang
Eine Fahrtmeldung kann sofort erfolgen, wenn er durch jeden detektierten Durchgang (Interrupt) ausgelöst wird.

## 2020-10-09 Draft: Sliding Window
Das Intervall wird auf zB 200ms reduziert. 
Sobald in einem Intervall ein Speichendurchgang detektiert wird, "fährt" der Zug.
Erst wenn zB. 5 Intervalle hintereinander keinen Durchgang zählen, "hält" der Zug.

Dadurch dauert es 1 .. 1.2 sec bis ein Stillstand gemeldet wird, aber nur 0 .. 0.2 sec bis eine Zugfahrt gemeldet wird.

Die Speichendurchgänge können auch zur Geschwindigkeitsmessung benutzt werden.
Die Anzahl Zähler (Raise+Fall) dividiert durch 2 dividiert durch Anzahl Speichen ergibt die Anzahl Umdrehungen pro Sekunde.