#ifndef DISPLAY_H
#define DISPLAY_H

//  The display shows a buffer of size 7 that is painted to simulate
//  a queue.
//
//  Example of display painted (size 7):
//  =======

class Display {
public:
    enum DisplayType {
        CONSOLE,
        LCD
    };

    virtual void show(int number) = 0;
};

#endif
