Einlesen eines Näherungssensors für die Speichen eines Wagenrades einer Modelleisenbahn.

## Mit Git auslesen
(Alternativ Download Zip).
```
git clone https://github.com/joergkeller/DrehleiterModell.git
cd DrehleiterModell
git submodule init
git submodule update
```

Aktualisieren:
```
cd DrehleiterModell
git reset --hard
git checkout master
git pull
```

## Compile mit Arduino-CLI
Für Arduino Nano:
```
cd DrehleiterModell         // falls nicht schon dort
arduino-cli core update-index
arduino-cli core install arduino:avr@1.8.3
arduino-cli core list       // prüfen
arduino-cli board listall   // prüfen
arduino-cli compile Controller -b arduino:avr:nano
```

Für Digispark ATtiny85:
```
cd DrehleiterModell         // falls nicht schon dort
arduino-cli core update-index
arduino-cli core install digistump:avr@1.6.7
arduino-cli core list       // prüfen
arduino-cli board listall   // prüfen
arduino-cli compile Controller -b digistump:avr:digispark-tiny8
```

## Verwendete Bibliotheken
* [TimerOne](https://github.com/PaulStoffregen/TimerOne.git) für den zeitgesteuerten Mess-Intervall 
* [PinChangeInterrupt](https://github.com/NicoHood/PinChangeInterrupt.git) für Signal-Interrupt auf ATtiny
 