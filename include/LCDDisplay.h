#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

#include "Display.h"

class LCDDisplay : public Display {
public:
    LCDDisplay();
    void show(int number);

private:
    int lcd_fd;
};

#endif
