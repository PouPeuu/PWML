#!/bin/bash
if [ ! -d build/ ]; then
    mkdir build
fi
g++ -o build/PWML *.cpp $(pkg-config gtkmm-4.0 tinyxml2 --cflags --libs) $2 -std=c++20
cp style.css build/style.css