cmake_minimum_required(VERSION 3.5.1)
project(consumer_producer)

find_package(Threads REQUIRED)

include_directories(include)

add_library(display SHARED
    src/ConsoleDisplay.cpp
    src/LCDDisplay.cpp
    src/lcd.cpp
    src/DisplayFactory.cpp
 )

add_executable(consumer_producer src/main.cpp)

target_link_libraries(consumer_producer 
    display
    -lpthread
)
