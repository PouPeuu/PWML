#!/bin/bash
if [ ! -d build/ ]; then
    mkdir build
fi
if [ "$1" == "linux" ]; then
    g++ -o build/PWML *.cpp $(pkg-config gtkmm-4.0 tinyxml2 --cflags --libs)
fi
if [ "$1" == "windows" ]; then
    x86_64-w64-mingw32-g++ -o build/PWML.exe *.cpp $(pkg-config gtkmm-4.0 tinyxml2 --cflags --libs)
fi
cp style.css build/style.css