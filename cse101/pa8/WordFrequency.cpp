/* Darren Lee, dlee181
 * 2023 Spring CSE101 PA8
 *·WordFrequency.cpp
 * Executable client which takes an input file and categorizes keys into x values
 */

#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]) {
    ifstream in;
    ofstream out;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    size_t begin, end, len;
    string line, key, keyBuffer;
    Dictionary A;

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

    while (getline(in, line)) {
        len = line.length();

        begin   = min(line.find_first_not_of(delim, 0), len);
        end     = min(line.find_first_of(delim, begin), len);
        key     = line.substr(begin, end-begin);

        while(key != "") {
            transform(key.begin(), key.end(), key.begin(), ::tolower);
            if (A.contains(key)) {
                A.getValue(key)++;
            }
            else {
                A.setValue(key, 1);
            }
            begin   = min(line.find_first_not_of(delim, end + 1), len);
            end     = min(line.find_first_of(delim, begin), len);
            key     = line.substr(begin, end - begin);
        }
    }
    out << A << endl;

    A.clear();
    in.close();
    out.close();
    return (EXIT_SUCCESS);
}
