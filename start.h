#ifndef start_h
#define start_h

#ifndef ARDUINO_AVR_MEGA2560
#error "Wrong board selected! Choose Mega 2560"
#endif

#include "config.h"   // Lade fundamentale Daten, die alle benötigen: Einstellungen, Pintabelle, Basiswerkzeuge, Bibliotheken
#include "core.h"  // Lade Ein- und Ausgabe
IO io;              // Ermögliche Ein- und Ausgabe
#include "global.h" // Lade alle aufwendigeren Klassen und Werkzeuze, Initialisiere globale Variablen / Objekte


#endif
