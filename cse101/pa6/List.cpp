 /* Darren Lee, dlee181
 * 2023 Winter CSE101 PA5
 * List.cpp
 * List ADT
 */
#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

using namespace std;
// Private Constructor
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// List in empty state
List::List() {
    pos_cursor = 0;
    num_elements = 0;
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;

}

// Copy Constructor
List::List(const List& L) {
    num_elements = 0;
    pos_cursor = 0;
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    // Loading elements of List into this List
    Node* N = L.frontDummy->next;
    while (N != L.backDummy) {
        this->insertBefore(N->data);
        N = N->next;
    }
    this->moveFront();
}

// Destructor
List::~List() {
    this->moveFront();
    while (this->length() > 0) {
        this->eraseAfter();
    }
    delete this->frontDummy;
    delete this->backDummy;
}

// Accessors
// How to check if List == NULL
int List::length() const{
    return this->num_elements;
}

ListElement List::front() const {
    if (length() <= 0) {
        throw std::length_error("List: front(): empty List");
    }
    return frontDummy->next->data;
}

ListElement List::back() const {
    if (length() <= 0) {
        throw std::length_error("List: back(): empty List");
    }
    return backDummy->prev->data;
}

int List::position() const{
    if (pos_cursor < 0 || pos_cursor > length()) {
        throw std::range_error("List: position(): pos_cursor <= || pos_cursor > length");
    }
    return pos_cursor;
}

ListElement List::peekNext() const {
    if (pos_cursor >= length()) {
        throw std::range_error("List: peekNext(): pos_cursor >= length");
    }
    return afterCursor->data;
}

ListElement List::peekPrev() const {
    if (pos_cursor <= 0) {
        throw std::range_error("List: peekPrev(): pos_cursor <= 0");
    }
    return beforeCursor->data;
}

// Setters

void List::clear() {
    this->moveFront();
    while (this->length() > 0) {
        this->eraseAfter();
    }
    pos_cursor = 0;
    num_elements = 0;
}

void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

void List::moveBack() {
    pos_cursor = length();
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

ListElement List::moveNext() {
    if (pos_cursor >= length()) {
        throw std::range_error("List: moveNext(): pos_cursor >= length");
    }
    pos_cursor += 1;
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    return beforeCursor->data;
}

ListElement List::movePrev() {
    if (pos_cursor <= 0) {
        throw std::range_error("List: movePrev(): pos_cursor <= 0");
    }
    pos_cursor -= 1;
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    return afterCursor->data;
}

void List::insertAfter(ListElement x) {
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements += 1;
}

void List::insertBefore(ListElement x) {
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    pos_cursor += 1;
    num_elements += 1;
}

void List::setAfter(ListElement x) {
    if (pos_cursor >= length()) {
        throw std::range_error("List: setAfter(): pos_cursor >= length()");
    }
    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (pos_cursor <= 0) {
        throw std::range_error("List: setBefore(): pos_cursor <= 0");
    }
    beforeCursor->data = x;
}

void List::eraseAfter() {
    if (pos_cursor >= length()) {
        throw std::range_error("List: eraseAfter(): pos_cursor >= length()");
    }
    Node *N = afterCursor;
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    afterCursor = beforeCursor->next;
    delete (N);
    num_elements -= 1;
}

void List::eraseBefore() {
    if (pos_cursor <= 0) {
        throw std::range_error("List: eraseBefore(): pos_cursor <= 0");
    }
    Node *N = beforeCursor;
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;
    beforeCursor = afterCursor->prev;
    delete (N);
    num_elements -= 1;
    pos_cursor -= 1;
}

// Other Functions ========================================

int List::findNext(ListElement x) {
    int y;
    bool found = false;
    while (pos_cursor < length() && !found) {
        y = moveNext();
        if (x == y) {
            found = true;
            break;
        }
    }
    if (!found) {
        moveBack();
        return -1;
    }
    return pos_cursor;
}

int List::findPrev(ListElement x) {
    int y;
    bool found = false;
    while (pos_cursor > 0 && !found) {
        y = movePrev();
        if (x == y) {
            found = true;
            break;
        }
    }
    if (!found) {
        moveFront();
        return -1;
    }
    return pos_cursor;
}

void List::cleanup() {
    Node *A = frontDummy->next;
    for (int i = 0; i < this->length(); i += 1) {
        Node *B = A->next;
        for (int j = 0; j < this->length(); j += 1) {
            if (A->data == B->data) {
                Node *temp = B;
                if (temp == beforeCursor) {
                    beforeCursor = beforeCursor->prev;
                    beforeCursor->next = afterCursor;
                    // I added
                    afterCursor->prev = beforeCursor;
                    if (beforeCursor != frontDummy) {
                        beforeCursor->prev->next = beforeCursor;
                    }
                    pos_cursor -= 1;
                }else if(temp < beforeCursor) pos_cursor -= 1;
                else if (temp == afterCursor){
                    afterCursor = afterCursor->next;
                    afterCursor->prev = beforeCursor;
                    if (afterCursor != backDummy) {
                        afterCursor->next->prev = afterCursor;
                    }
                    beforeCursor->next = afterCursor;
                }
            B->prev->next = B->next;
            B->next->prev = B->prev;
            B = B->next;
            delete(temp);
            // Need a check to compare if the position of the cursor is ahead or behind.
            num_elements -= 1;
            }
            else if (B != backDummy) {
                B = B->next;
            }
        }
        A = A->next;
    }
    cout << "Ah" << pos_cursor << endl;
}

List List::concat(const List& L) const {
    Node *N = nullptr;

    List newList;
    newList.moveBack();

    for (N = this->frontDummy->next; N != this->backDummy; N = N->next) {
        newList.insertBefore(N->data);
    }

    for (N = L.frontDummy->next; N != L.backDummy; N = N->next) {
        newList.insertBefore(N->data);
    }

    newList.moveFront();
    return newList;
}

std::string List::to_string() const {
    Node *N = frontDummy->next;
    std::string s = "(";
    for (int i = 0; i < length() - 1; i++) {
        s += std::to_string(N->data) + ", ";
        N = N->next;
    }
    s += std::to_string(N->data) + ")";
    return s;
}

bool List::equals(const List& R) const {
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = (this->length() == R.length());
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    while (eq && N != this->backDummy) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Operator Overloaders

std::ostream& operator<<( std::ostream& stream, const List& L) {
    return stream << L.List::to_string();
}

bool operator== (const List& A, const List& B) {
    return A.List::equals(B);
}

List& List::operator= (const List& L) {
    if (this != &L) {
        List temp = L;

        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
}
