/* Darren Lee, dlee181
 * 2023 Spring CSE101 PA7
 * Order.cpp
 * Executable client which takes a file with strings on each line and sets it according to a key value pair into our dictionary
 */

#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    ifstream in;
    ofstream out;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " Order <input file> <output file> "
             << endl;
        return (EXIT_FAILURE);
    }

    in.open(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return (EXIT_FAILURE);
    }

    out.open(argv[2]);
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return (EXIT_FAILURE);
    }

    Dictionary A;
    string key;
    int value = 1;
    while (getline(in, key)) {
        A.setValue(key, value);
        value += 1;
    }
    out << A << endl;
    out << A.pre_string() << endl;

    in.close();
    out.close();

    return 0;
}
