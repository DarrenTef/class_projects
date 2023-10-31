/*Darren Lee, dlee181
 * 2023 Spring CSE101 PA6
 * BigInteger.cpp
 * Big Integer ADT
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include "BigInteger.h"

using namespace std;

#define BASE    1000000000
#define POWER   9

int counter = 0;
int normalizeList(List& L);
void negateList(List& L);
void sumList(List& S, List A, List B, int sgn);
void shiftList(List& L, int p);
void scalarMultList(List& L, ListElement m);

// Signs when dealing with negate, sign() of A and B are neg,
// Does add() need a bunch of if conditions checking for signage
// Infinite recursion on negateList.

// Constructor ======================================================
// Zero state
BigInteger::BigInteger() {
    signum = 0;
    digits = List(); // or digits = List();
}

// Creates BigInteger from long x;
BigInteger::BigInteger(long x) {
    string s = "";
    s.append(std::to_string(x));
    long index = 0;
    int offSet = 0;
    if (s.length() <= 0) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    string sig = s.substr(0, 1);
    if (sig == "-"){
        signum = -1;
        index += 1;
        offSet = 1;
        if (s.length() == 0) {
            throw std::invalid_argument("BigInteger: Constructor: empty string");
        }
    }
    else if (sig == "+") {
        signum = 1;
        index += 1;
        offSet = 1;
        if (s.length() == 0) {
            throw std::invalid_argument("BigInteger: Constructor: empty string");
        }
    }
    else {
        signum = 1;
    }
    // gets the first char to check if it is 0
    sig = s.substr(0, 1);
    // deletes all zeros
    for (long i = index; index < s.length(); i += 1) {
        if (s[i] == '0') {
            index += 1;
        }
        else {
            break;
        }
    }
    if (index == s.length()) {
        signum = 0;
        digits.insertBefore(0);
        return;
    }
    for (long i = s.length(); i > index; i -= POWER) {
        string temp = "";
        if (i - POWER <= 0) {
            if (offSet == 1) {
                temp = s.substr(offSet, i - 1);
            }
            else {
                temp = s.substr(offSet, i);
            }
        }
        else {
            temp = s.substr(i - POWER, POWER);
        }
        for (long j = 0; j < temp.length(); j += 1) {
            if (isdigit(temp[j]) == 0) {
                throw invalid_argument("BigInteger: Constructor: non-numeric string");
            }
        }

        long val = stol(temp, nullptr, 10);
        digits.insertAfter(val);
    }
}

// Creates BigInteger from string s;
BigInteger::BigInteger(std::string s) {
    int index = 0;
    int offSet = 0;
    if (s.length() <= 0) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    string sig = s.substr(0, 1);
    if (sig == "-"){
        signum = -1;
        index += 1;
        offSet = 1;
        if (s.length() == 0) {
            throw std::invalid_argument("BigInteger: Constructor: empty string");
        }
    }
    else if (sig == "+") {
        signum = 1;
        index += 1;
        offSet = 1;
        if (s.length() == 0) {
            throw std::invalid_argument("BigInteger: Constructor: empty string");
        }
    }
    else {
        signum = 1;
    }
    // gets the first char to check if it is 0
    sig = s.substr(0, 1);
    // deletes all zeros
    for (long i = index; index < s.length(); i += 1) {
        if (s[i] == '0') {
            index += 1;
        }
        else {
            break;
        }
    }
    if (index == s.length()) {
        signum = 0;
        digits.insertBefore(0);
        return;
    }
    for (long i = s.length(); i > index; i -= POWER) {
        string temp = "";
        if (i - POWER <= 0) {
            if (offSet == 1) {
                temp = s.substr(offSet, i - 1);
            }
            else {
                temp = s.substr(offSet, i);
            }
        }
        else {
            temp = s.substr(i - POWER, POWER);
        }
        for (long j = 0; j < temp.length(); j += 1) {
            if (isdigit(temp[j]) == 0) {
                throw invalid_argument("BigInteger: Constructor: non-numeric string");
            }
        }

        long val = stol(temp, nullptr, 10);
        digits.insertAfter(val);
    }
    // To test whether normalizing properly
    /*
    List A = digits;
    A.moveBack();
    A.insertBefore(10000000);
    negateList(A);
    cout << "digits\t\t" << digits << endl;
    cout << "negate\t\t" << A << endl;
    normalizeList(A);
    cout << "Normalized\t" << A << endl;
    */
}
// copy Constructor
BigInteger::BigInteger(const BigInteger& N) {
    this->signum = N.signum;
    this->digits = N.digits;
}

// Accessors ========================================================
// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive,
// negative or 0, respectively.
int BigInteger::sign() const {
    if (this->signum > 0) {
        return 1;
    }
    else if (this->signum < 0) {
        return -1;
    }
    else {
        return 0;
    }
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    ListElement x, y;
    if (this->signum > N.signum) {
        return 1;
    }
    else if (this->signum < N.signum) {
        return -1;
    }
    else if (this->digits.length() > N.digits.length()) {
        return 1;
    }
    else if ( this->digits.length() < N.digits.length()) {
        return -1;
    }
    else {
        List A = this->digits;
        List B = N.digits;
        A.moveFront();
        B.moveFront();
        for (int i = 0; i < digits.length(); i += 1) {
            x = A.peekNext();
            y = B.peekNext();
            if (x > y) {
                return 1;
            }
            else if (x < y) {
                return -1;
            }
            A.moveNext();
            B.moveNext();
        }
        return 0;
    }
}

// Setters ==========================================================
// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger positive <--> negative.
void BigInteger::negate() {
    signum *= -1;
}
// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    List L;
    List A = this->digits;
    List B = N.digits;
    BigInteger Z;
    A.moveFront();
    B.moveFront();
    if (A.peekNext() == 0) {
        Z.digits = B;
        Z.signum = N.signum;
        return Z;
    }
    if (B.peekNext() == 0) {
        Z.digits = A;
        Z.signum = this->signum;
        return Z;
    }
    if (this->signum == 1 && N.signum == -1) {
        sumList(L, A, B, -1);
        Z.signum = normalizeList(L);
    }
    else if (this->signum == -1 && N.signum == 1) {
        sumList(L, B, A, -1);
        Z.signum = normalizeList(L);
    }
    else {
        sumList(L, A, B, 1);
        Z.signum = this->signum * normalizeList(L);
    }
    Z.digits = L;
    return Z;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    List L;
    List A = this->digits;
    List B = N.digits;
    negateList(B);
    BigInteger C;
    BigInteger D;
    BigInteger Z;
    C.digits = B;
    C.signum = N.signum;
    D.digits = A;
    D.signum = this->signum;
    Z = D + C;
    return Z;

    /*
    incorrect first implementation
    negateList(B);
    sumList(L, A, B, 1);
    BigInteger Z = normalizeList(L);
    Z.signum = normalizeList(L);
    Z.digits = L;
    return Z;
    */
}

// mult()
// Returns a BigInteger representing the product of this and N.
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger M;
    if (this->sign() == 0 || N.sign() == 0) {
        M.signum = 0;
        M.digits.insertAfter(0);
        return M;
    }
    List A = this->digits;
    List B = N.digits;
    ListElement x;
    int p = (A.length() >= B.length()) ? B.length() : A.length();
    List bot = (A.length() >= B.length()) ? B : A;
    List top = (A.length() >= B.length()) ? A : B;
    List added;
    List multiplied;
    bot.moveBack();
    A.moveBack();
    B.moveBack();
    // my scalarMult returns a List
    for (int i = 0; i < p; i += 1) {
        multiplied = top;
        x = bot.movePrev();
        scalarMultList(multiplied, x);
        // cout << "multiplied\t" << multiplied << "bot" << x << endl;
        shiftList(multiplied, i);
        sumList(added, added, multiplied, 1);
        normalizeList(added);
        // cout << added << endl;
    }

    M.digits = added;
    M.signum = this->sign() * N.sign();
    return M;


        /*
        x = bot.movePrev();
        // cout << "top * x\t" << top << " * " << x << endl;
        added = scalarMultList(top, x);
        // cout << "scalarMulted\t" << added << endl;
        shiftList(added, i);
        // cout << "shift" << added << endl;
        */

    // Setting signum
}


// Helpers ==========================================================
// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    string str = "";
    if (signum == 0) {
        return str + "0";
    }
    else {
        int len = this->digits.length();
        this->digits.moveBack();
        for (int i = 0; i < len; i += 1) {
            str = std::to_string(this->digits.peekPrev()) + str;
            if (i != len) {
                int extra = std::to_string(this->digits.peekPrev()).length();
                if (extra != POWER) {
                    for (int j = 0; j < POWER - extra; j += 1) {
                        str = '0' + str;
                    }
                }
                this->digits.movePrev();
            }
        }
        string s = str.substr(0, 1);
        while (s == "0") {
            str.erase(0, 1);
            s = str.substr(0, 1);
        }

        if (signum == -1) {
            str = '-' + str;
        }
    }
    return str;
}

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L) {
    ListElement x;
    for (L.moveBack(); L.position() > 0;) {
        x = L.movePrev();
        L.setAfter(x * -1);
    }
}
// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn) {
    int len = (A.length() >= B.length()) ? A.length() : B.length();
    A.moveBack();
    B.moveBack();
    S.clear();
    ListElement a;
    ListElement b;
    for (int i = 0; i < len; i += 1) {
        a = 0;
        b = 0;
        if (A.position() > 0) {
            a = A.movePrev();
        }
        if (B.position() > 0) {
            b = B.movePrev() * sgn;
        }
        S.insertAfter(a + b);
    }
    /*
    A.moveBack();
    B.moveBack();
    S.clear();
    while (A.position() > 0 || B.position() > 0) {
        S.insertAfter(A.movePrev() + (B.movePrev() * sgn));
    }

    while (A.position() > 0) {
        S.insertAfter(A.movePrev());
    }

    while (B.position() > 0) {
        S.insertAfter(B.movePrev()* sgn);
    }
    */
}
// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L) {
    /*
    ListElement carry = 0;
    ListElement x;
    bool neg = false;
    for (L.moveBack(); L.position() >= 1;) {
        x = L.movePrev() + carry;
        carry = 0;
        L.setAfter(x);
        if (x >= BASE) {
            L.setAfter(x % BASE);
            carry = x / BASE;
        }
        else {
            if (x < 0) {
                L.setAfter(-x % BASE);
                carry = x / BASE;
                if (carry == 0 && L.position() == 0) {
                    neg = true;
                }
            }
        }
        if (L.position() == 0) {
            if (carry != 0) {
                L.insertBefore(carry);
                break;
            }
        }
    }
    // Loop to get rid of the leading zeros
    L.moveFront();
    while (L.position() == 0 && L.length() > 1 && L.peekNext() == 0) {
        L.eraseAfter();
    }

    if (neg) {
        if (counter == 0) {
            counter += 1;
            negateList(L);
            normalizeList(L);
        }
        counter = 0;
        return -1;
    }

    L.moveFront();
    if (L.length() > 0) {
        if (L.peekNext() > 0) {
            return 1;
        }
    }
    else {
        return 0;
    }
    */

    L.moveFront();
    if (L.peekNext() < 0) {
        negateList(L);
        normalizeList(L);
        return -1;
    }
    ListElement carry = 0;
    ListElement q, r, x;
    for (L.moveBack(); L.position() >= 1;) {
        x = L.movePrev() + carry;
        q = x / BASE;
        r = x % BASE;
        if (r < 0) {
            L.setAfter(r + BASE);
            carry = q - 1;
        }
        else {
            if (r >= 0) {
                L.setAfter(r);
                carry = q;
            }
        }

        if (L.position() == 0) {
            if (carry != 0) {
                L.insertBefore(carry);
                break;
            }
        }
    }

    L.moveFront();
    while (L.position() == 0 && L.length() > 1 && L.peekNext() == 0) {
        L.eraseAfter();
    }


    L.moveFront();
    if (L.peekNext() > 0) {
        return 1;
    }

    else if (L.peekNext() < 0) {
        negateList(L);
        normalizeList(L);
        return -1;
    }
    else{
        return 0;
    }
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p) {
    L.moveBack();
    for (int i = 0; i < p; i += 1) {
        L.insertBefore(0);
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m) {
    int x;
    for (L.moveBack(); L.position() > 0;) {
        x = L.movePrev();
        L.setAfter(x * m);
    }
}

// Overriden Operators ==============================================

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B.
bool operator==( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) == 0) ? true : false;
}

// operator<()
// Returns true if and only if A is less than B.
bool operator<( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) < 0) ? true : false;
}
// operator<=()
// Returns true if and only if A is less than or equal to B.
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) <= 0) ? true : false;
}
// operator>()
// Returns true if and only if A is greater than B.
bool operator>( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) > 0) ? true : false;
}
// operator>=()
// Returns true if and only if A is greater than or equal to B.
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) >= 0) ? true : false;
}
// operator+()
// Returns the sum A+B.
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}
// operator+=()
// Overwrites A with the sum A+B.
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A + B;
    return A;
}
// operator-()
// Returns the difference A-B.
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}
// operator-=()
// Overwrites A with the difference A-B.
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A - B;
    return B;
}
// operator*()
// Returns the product A*B.
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}
// operator*=()
// Overwrites A with the product A*B.
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A * B;
    return A;
}




