#include "DisplayFactory.h"

#include "ConsoleDisplay.h"
#include "LCDDisplay.h"

Display* DisplayFactory::getDisplay(Display::DisplayType type)
{
    switch (type) {
    case Display::CONSOLE:
        return new ConsoleDisplay;
    case Display::LCD:
        return new LCDDisplay;
    default:
        return 0;
    }
}
