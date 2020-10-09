# Design Notizen

## 2020-10-09 Erster Versuch

Ich würde die Speichendurchgänge mit einem Interrupt zählen. 
Das macht dich unabhängig von allem anderen das läuft. 
Dazu kannst du auf Nano allerdings nur die Pins 2/3 nutzen. 

Mit einem Timer prüfst du zB alle 1000ms den Zählerstand. 
Das ist etwas unflexibel, wenn der Zug stoppt, dauert es 1..2 sec, bis der Stillstand gemeldet wird. Wenn er losfährt 0..1 sec bis Meldung. Verbesserung ist möglich. 

Gib mir eine Nachricht, ob das so klappt (bin in den Ferien und habe kein Board).