 /* Darren Lee, dlee181
 * 2023 Winter CSE101 PA5
 * Shuffle.cpp
 * Executable client which does multiple operations relating to the shuffling of numbers that implements the List ADT
 */

#include <iostream>
#include <string>
#include <fstream>
#include "List.h"
using namespace std;

void shuffle(List& D);

void shuffle(List& D) {
    int n, a, b;
    n = D.length();
    List L, R;
    D.moveFront();
    while (D.position() < n/2) {
        a = D.moveNext();
        L.insertBefore(a);
    }
    while (D.position() < n) {
        b = D.moveNext();
        R.insertBefore(b);
    }
    D.clear();
    L.moveFront();
    R.moveFront();
    for (int i = 1; i <= n; i += 1) {
        if(i % 2 == 0){
            a = L.moveNext();
            D.insertBefore(a);
        }
        else {
            b = R.moveNext();
            D.insertBefore(b);
        }
    }
}

int main (int argc, char* argv[]) {

    int count;
    List D, cpy;
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " Shuffle <int>" << endl;
        return (EXIT_FAILURE);
    }

    int cards = stoi(argv[1]);
    if (cards <= 0) {
        cerr << "Usage: " << argv[1] << " Shuffle <int>" << endl;
        return (EXIT_FAILURE);
    }

    cout << "deck size\tshuffle count" << endl;
    cout << "------------------------------" << endl;
    D.moveBack();
    for (int i = 1; i <= cards; i += 1) {
        count = 0;
        D.insertBefore(i - 1);
        cpy = D;
        shuffle(D);
        count += 1;
        while (!(cpy == D)) {
            shuffle(D);
            count += 1;
        }
        cout << i << "\t" << count << endl;
    }
    return (0);
}

