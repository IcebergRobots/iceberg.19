#include "Container.h"

/*********************************************************************
  Konstruktor
  - füge dieses Objekt zum Container hinzu
*********************************************************************/
Container::Container() {
    getObjects(this);
}

/*********************************************************************
  greife auf den Container zu
  @param myself:
    1) NULL
      - Objektcontainer zurückgeben
      - gib eine Liste aus Pointern (konvertiert zu Integern) zu allen Objekten dieser Klasse zurück
    2) Pointer zum eigenen Objekt
      - füge das eigene Objekt zum Container hinzu
*********************************************************************/
LinkedList<int> *Container::getObjects(Container *myself) {
    static LinkedList<int> objectAddresses; // statischer klassenweite Liste alle Objektpointer
    if (myself == NULL) return &objectAddresses; // gebe Containerliste zurück, wenn keine Parameter angegeben sind
    else objectAddresses.add((int)myself); // füge das eigene Objekt zum Container hinzu
}