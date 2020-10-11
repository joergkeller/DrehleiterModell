Einlesen eines Näherungssensors für die Speichen eines Wagenrades einer Modelleisenbahn.

## Mit Git auslesen
(Alternativ Download Zip).
```
git clone https://github.com/joergkeller/DrehleiterModell.git
cd DrehleiterModell
git submodule init
git submodule update
```

## Compile mit Arduino-CLI
```
cd DrehleiterModell         // falls nicht schon dort
arduino-cli core update-index
arduino-cli core install arduino:avr@1.8.3
arduino-cli core list       // prüfen
arduino-cli board listall   // prüfen
arduino-cli compile -b arduino:avr:nano Controller/Controller.ino
```
