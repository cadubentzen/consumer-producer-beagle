#ifndef DISPLAYFACTORY_H
#define DISPLAYFACTORY_H

#include "Display.h"

class DisplayFactory {
public:
    static Display* getDisplay(Display::DisplayType type);
};

#endif
