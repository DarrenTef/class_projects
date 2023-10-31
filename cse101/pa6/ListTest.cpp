/*Darren Lee, dlee181
 * CSE101 Spring 2023, pa6
 * ListTest.cpp
 * executable testing file for List ADT implemented in cpp
 */

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

void RemoveDuplicates(List& L);
List Remove(List& L, int x);
bool Anagram(List A, List B);


List Remove(List& L, int x) {
    List R = L;
    int y;
    R.moveFront();
    while (R.position() < R.length()) {
        y = R.moveNext();
        if (x == y) {
            R.eraseBefore();
        }
    }
    return R;
}

bool Anagram(List A, List B) {
    if (A.length() != B.length()) {
        return false;
    }
    List temp = B;
    int x;
    A.moveFront();
    B.moveFront();
    while (A.position() < A.length()) {
        x = A.moveNext();
        if (temp.findNext(x) == -1) {
            return false;
        }
        temp.eraseBefore();
        temp.moveFront();
    }
    return temp.length() == 0;
}


int main(){
    List L;
    L.moveBack();
    L.insertBefore(1);
    L.insertBefore(1);
    L.insertBefore(2);
    L.insertBefore(3);
    L.insertBefore(5);
    L.insertBefore(1);
    L.insertBefore(2);
    // cout << L << endl;

    List A = L;
    List B = L;
    cout << A<< endl;
    cout << B << endl;
    cout << "ana\t" << Anagram(A, B) << endl;
    // List X = Remove(L, 2);
    //cout << X << endl;

    // cout << L << endl;


    /*
   int i, n=10;
   List A, B, C, D, Z;

   for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertAfter(11-i);
      C.insertBefore(i);
      D.insertBefore(11-i);
   }
   Z.moveBack();
   cout << "Z postion\t" << Z.position() << endl;
   for (int j = 1; j <= 50; j += 1) {
        Z.insertBefore(j);
   }
   cout << "Z List\t" << Z << endl;
    cout << "Z postion\t" << Z.position() << endl;
    cout << "Z length" << Z.length() << endl;
    Z.moveBack();
   for (int j = 1; j <= 50; j += 2) {
       Z.insertBefore(j);
   }
   cout << "Z length" << Z.length() << endl;

   cout << "Z List\t" << Z << endl;
    cout << "Z postion\t" << Z.position() << endl;
   cout << "Find Prev 2" << Z.findPrev(2) <<endl;
   cout << "Find Next 2" << Z.findNext(2) <<endl;
    cout << "Find Prev 47" << Z.findPrev(47) <<endl;
    cout << "Find Next 47" << Z.findNext(47) <<endl;
    cout << "Z length" << Z.length() << endl;
   Z.cleanup();
   cout << "Find Prev 2" << Z.findPrev(2) <<endl;
   cout << "Find Next 2" << Z.findNext(2) <<endl;
    cout << "Find Prev 47" << Z.findPrev(47) <<endl;
    cout << "Find Next 47" << Z.findNext(47) <<endl;

   cout << "Z List - Cleaned up\t" << Z << endl;
    cout << "Z postion Cleaned up\t" << Z.position() << endl;
    cout << "Z length" << Z.length() << endl;


   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   A.moveBack();
   B.moveBack();
   C.moveFront();
   D.moveFront();

   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;

   cout << endl << "B: ";
   for(i=1; i<=7; i++){
      cout << B.movePrev() << " ";
   }
   cout << endl << "B.position() = " << B.position() << endl;

   cout << endl << "C: ";
   for(i=1; i<=7; i++){
      cout << C.moveNext() << " ";
   }
   cout << endl << "C.position() = " << C.position() << endl;

   cout << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==D is " << (C==D?"true":"false") << endl;
   cout << "D==A is " << (D==A?"true":"false") << endl;
   cout << endl;

   cout << B.findNext(5) << endl;
   cout << B << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl;
   cout << B.findPrev(2) << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl;
   cout << B.findNext(20) << endl;
   cout << B.position() << endl;
   cout << B.findPrev(20) << endl;
   cout << B.position() << endl;
   cout << endl;

   for( i=10; i>=1; i--){
      A.insertAfter(i);
      A.movePrev();
   }
   cout << "A = " << A << endl;
   for( i=1; i<=15; i++){
      A.moveNext();
   }
   cout << A.position() << endl;
   A.cleanup();
   cout << "A = " << A << endl;
   cout << A.position() << endl;
   cout << endl;

   List E = A;
   cout << "E==A is " << (E==A?"true":"false") << endl;

   cout << endl;

   List F = A.concat(B);
   cout << "F = " << F << endl;
   cout << "length: " << F.length() << endl;
   cout << "front: " << F.front() << endl;
   cout << "back: " << F.back() << endl;
   cout << "position: " << F.position() << endl;
   for( i=1; i<=7; i++){
      cout << "peekNext: " << F.peekNext() << endl;
      F.insertBefore(-i);
      cout << F.moveNext() << endl;
   }
   cout << "F = " << F << endl;

   cout << endl;

   cout << "test exceptions: " << endl;
   cout << "A = " << A << endl;
   A.moveFront();
   try{
      A.peekPrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.movePrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setBefore(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseBefore();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.moveBack();
   try{
      A.peekNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.moveNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setAfter(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseAfter();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.clear();
   try{
      A.front();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.back();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;


   return( EXIT_SUCCESS );
   */
}
void RemoveDuplicates(List& L) {
    int x, y;
    for (L.moveFront(); L.position() < L.length();) {
        x = L.moveNext();
        while (L.position() < L.length()) {
            y = L.moveNext();
            if (x == y) {
                L.eraseBefore();
            }
        }
    }
}

