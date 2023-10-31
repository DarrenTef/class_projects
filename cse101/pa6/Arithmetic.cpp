/* Darren Lee, dlee181
 * 2023 Spring CSE101 PA6
 * Arithmetic.cpp
 * Executable file using BigInteger ADT
 */

#include <iostream>
#include <string>
#include <fstream>
#include "BigInteger.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream in;
    ofstream out;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " Arithmetic <input file> <output file> " << endl;
        return (EXIT_FAILURE);
    }

    in.open(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return (EXIT_FAILURE);
    }

    out.open(argv[2]);
    if (!out.is_open()) {
        cerr <<"Unable to open file " << argv[2] << " for writing" << endl;
        return (EXIT_FAILURE);
    }

    string a, b, empty;
    if (!getline(in, a)) {
        cerr << "Missing string: line 1" << endl;
        return (EXIT_FAILURE);
    }
    getline(in, empty);
    if (!getline(in, b)) {
        cerr << "Missing string: line 3" << endl;
        return (EXIT_FAILURE);
    }
    BigInteger A = BigInteger(a);
    BigInteger B = BigInteger(b);

    out << A << endl;
    out << endl;
    out << B << endl;
    out << endl;
    out << A + B << endl;
    out << endl;
    out << A - B << endl;
    out << endl;
    out << A - A << endl;
    out << endl;
    out << (3 * A) - (2 * B) << endl;
    out << endl;
    out << A * B << endl;
    out << endl;
    out << A * A << endl;
    out << endl;
    out << B * B << endl;
    out << endl;
    out << (9 * (A * A * A * A)) + (16 * (B * B * B * B * B)) << endl;
    out << endl;
    in.close();
    out.close();

    return (0);
}
