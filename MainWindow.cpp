#include "MainWindow.h"
#include <iostream>
#include <string>
#include <fstream>

/* using namespace std;

string read_file(string path) {
    string line;
    string text;
    ifstream file(path);

    while(getline(file, line)) {
        text += line;
    }

    file.close();
    return text;
} */

MainWindow::MainWindow() {
    set_title("Primitive Wings Mod Loader");
    set_default_size(600, 400);
    
}