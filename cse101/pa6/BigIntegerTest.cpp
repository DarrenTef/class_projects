/* Darren Lee, dlee181
 * 2023 Spring CSE101 PA6
 * BigIntgerTest.cpp
 * BigIntegerADT Test
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include "BigInteger.h"

using namespace std;

int main() {
    // string a = "91287346670000043892345634563400005619187236478";
    // string b = "-330293847502398475";
    string a = "-101289388123";
    string b = "2128381923";
    string c = "-200301301234502";
    long d = 12341;
    string e = "+123";
    string f = "-456";

    BigInteger A = BigInteger(a);
    BigInteger B = BigInteger(b);
    BigInteger C = BigInteger(c);
    BigInteger D = BigInteger(d);
    BigInteger E = BigInteger(e);
    BigInteger F = BigInteger(f);


    cout << endl;

    cout << "Testing for mult ============================================================" << endl;
    BigInteger X;
    BigInteger Y;
    X = BigInteger("123782637162378126371862387126378123");
    Y = BigInteger("45612837192837189237891238912739812");
    cout << "X\t" << X << endl;
    cout << "Y\t" << Y << endl;
    BigInteger XY = X * Y;
    cout << "mult X*Y\t" << XY << endl;
    cout << "XY.sign\t" << XY.sign() << endl;
    cout <<"=============================================================================" << endl;

    cout << endl;

    cout << "Testing for sub ============================================================" << endl;
    BigInteger V = BigInteger("-100");
    BigInteger Z = BigInteger("+100");
    cout << "V\t" << V << endl;
    cout << "Z\t" << Z << endl;
    BigInteger VZ = V - Z;
    cout << "sub V-Z\t" << VZ << endl;
    cout << "VZ.sign\t" << VZ.sign() << endl;
    cout <<"=============================================================================" << endl;

    cout << endl;

    cout << "Testing for Add() ==========================================================" << endl;
    BigInteger S = BigInteger("+100");
    BigInteger T = BigInteger("+101");
    cout << "S\t" << S << endl;
    cout << "T\t" << T << endl;
    BigInteger ST = S + T;
    cout << "sum S+T\t" << ST << endl;
    cout << "ST.sign\t" << ST.sign() << endl;
    cout << "S == T" << (S == T) << endl;

    cout << "==================================================================" << endl;

    cout << endl;

    // Compare()
    cout << "compare()" << endl;
    cout << "A\t" << A << endl;
    cout << "B\t" << B << endl;
    cout << "A.cmp(B)\t" << A.compare(B) << endl;

    cout << endl;

    // MakeZero()
    cout << "MakeZero()" << endl;
    cout << "C\t\t" << C << endl;
    C.makeZero();
    cout << "c.zero\t\t" << C << endl;

    cout << endl;

    // Negate()
    cout << "negate()" << endl;
    cout << "D\t\t" << D << endl;
    D.negate();
    cout << "c.zero\t\t" << D << endl;

    cout << endl;

    // add()
    cout << "add()" << endl;
    cout << "E\t" << E << endl;
    cout << "F\t" << F << endl;
    BigInteger G = E + F;
    cout << "E + F\t" << G << endl;

    cout << endl;

    // sign()
    cout << "sign()" << endl;
    cout << A.sign() << endl;
    cout << B.sign() << endl;
    cout << G.sign() << endl;
    cout << endl;

    // compare()
    cout << "compare" << endl;
    cout << "should -1\t" << A.compare(B) << endl;
    cout << "should 1\t" << B.compare(A) << endl;

    cout << endl;

    cout << endl;
    return (0);
}
