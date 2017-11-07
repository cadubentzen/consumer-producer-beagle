#include "LCDDisplay.h"

#include <cstdio>
#include <cstdlib>
#include <sstream>

#include "lcd.h"

LCDDisplay::LCDDisplay()
{
    lcd_fd = lcd_open("/dev/lcd0");
}

void LCDDisplay::show(int number)
{
    lcd_clear_and_home(lcd_fd);
    
    std::stringstream ss;
    for (int i = 0; i < number; ++i) {
        ss << i + 1;
    }

    lcd_message(lcd_fd, "%s", ss.str().c_str());
}
