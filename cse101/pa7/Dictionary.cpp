/* Darren Lee, dlee181
 * 2023 Spring CSE101 PA7
 * Dictionary.cpp
 * Dictionary ADT
 */

#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// getVal, search(arguments)
//

// Private Constructor
Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string &s, Node *R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}
// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string &s, Node *R) const {
    if (R != nil) {
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}
// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this·
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node *R, Node *N) {
    if (R != nil && R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}
// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node *R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        num_pairs -= 1;
        delete R;
    }
}
// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node *Dictionary::search(Node *R, keyType k) const {
    if (R == nil || k == R->key) {
        return R;
    } else if (k < R->key) {
        return search(R->left, k);
    } else { // k > R.key
        return search(R->right, k);
    }
}
// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the·
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMin(Node *R) {
    // treeMin
    if (R == nil) {
        throw logic_error("Dictionary: findMin(): R == nil");
    }
    while (R->left != nil) {
        R = R->left;
    }
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the·
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMax(Node *R) {
    if (R == nil) {
        throw logic_error("Dictionary: findMax(): R == nil");
    }
    while (R->right != nil) {
        R = R->right;
    }
    return R;
}
// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost·
// Node, or is nil, returns nil.·
Dictionary::Node *Dictionary::findNext(Node *N) {
    if (N->right != nil) {
        return findMin(N->right);
    }
    Node *Y = N->parent;
    while (Y != nil && N == Y->right) {
        N = Y;
        Y = Y->parent;
    }
    return Y;
}
// TreeSuccessor

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost·
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findPrev(Node *N) {
    if (N->left != nil) {
        return findMax(N->left);
    }
    Node *Y = N->parent;
    while (Y != nil && N == Y->left) {
        N = Y;
        Y = Y->parent;
    }
    return Y;
}
// opposite treeSuccessor
// invert lefts and invert min

void Dictionary::transplant(Node *U, Node *V) {
    if (U->parent == nil) {
        this->root = V;
    } else if (U == U->parent->left) {
        U->parent->left = V;
    } else {
        U->parent->right = V;
    }
    if (V != nil) {
        V->parent = U->parent;
    }
}

// Constructor - Empty state
Dictionary::Dictionary() {
    nil = new Node("\0", 0);
    root = nil;
    current = root;
    num_pairs = 0;
}

// Copy Constructor
Dictionary::Dictionary(const Dictionary &D) {
    nil = new Node("\0", 0);
    root = nil;
    current = nil;
    num_pairs = 0;
    this->preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
    postOrderDelete(this->root);
    root = nil;
    current = nil;
    num_pairs = 0;
    delete nil;
}

// Accessors

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const { return this->num_pairs; }

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    Node *N = search(root, k);
    if (N == nil) {
        return false;
    } else {
        return true;
    }
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType &Dictionary::getValue(keyType k) const {
    if (!contains(k)) {
        throw std::logic_error("getValue(), key doesn't exist");
    } else {
        Node *N = search(this->root, k);
        return N->val;
    }
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false·
// otherwise.
bool Dictionary::hasCurrent() const {
    if (current == nil) {
        return false;
    } else {
        return true;
    }
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()·
keyType Dictionary::currentKey() const {
    if (hasCurrent() == false) {
        throw logic_error("Dictionary: currentKey(): hasCurrent() == false");
    }
    return current->key;
}
// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType &Dictionary::currentVal() const {
    if (hasCurrent() == false) {
        throw logic_error("Dictionary: currentVal(): hasCurrent() == false");
    }
    return current->val;
}
// Setters

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    postOrderDelete(this->root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,·
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    /*
    if (!contains(k)) {
        throw logic_error("Dictionary: setValue(), !contains(k)");
    }
    */

    Node *Y = nil;
    Node *X = this->root;
    while (X != nil) {
        Y = X;
        if (k < X->key) {
            X = X->left;
        } else if (k > X->key) {
            X = X->right;
        } else {
            X->val = v;
            return;
        }
    }
    Node *Z = new Node(k, v);
    Z->left = nil;
    Z->right = nil;
    Z->parent = Y;
    if (Y == nil) {
        this->root = Z;
        num_pairs += 1;
    } else if (k < Y->key) {
        Y->left = Z;
        num_pairs += 1;
    } else if (k > Y->key) {
        Y->right = Z;
        num_pairs += 1;
    } else {
        Y->val = v;
        delete Z;
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
// replace treeMin with findmin
void Dictionary::remove(keyType k) {
    if (!contains(k)) {
        throw logic_error("Dictionary: remove(): !contains(k)");
    }
    num_pairs -= 1;
    if (k == current->key) {
        current = nil;
    }
    Node *Z = search(this->root, k);
    if (Z->left == nil) {
        transplant(Z, Z->right);
    } else if (Z->right == nil) {
        transplant(Z, Z->left);
    } else {
        Node *Y = findMin(Z->right);
        if (Y->parent != Z) {
            transplant(Y, Y->right);
            Y->right = Z->right;
            Y->right->parent = Y;
        }
        transplant(Z, Y);
        Y->left = Z->left;
        Y->left->parent = Y;
    }
    delete Z;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.·
void Dictionary::begin() {
    if (num_pairs != 0) {
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.·
void Dictionary::end() {
    if (num_pairs != 0) {
        current = findMax(root);
    }
}
// next()
// If the current iterator is not at the last pair, advances current·
// to the next pair (as defined by the order operator < on keys). If·
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if (!hasCurrent()) {
        throw logic_error("Dictionary: next(): !hasCurrent()");
    }
    current = findNext(current);
}
// prev()
// If the current iterator is not at the first pair, moves current to··
// the previous pair (as defined by the order operator < on keys). If·
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if (!hasCurrent()) {
        throw logic_error("Dictionary: prev(): !hasCurrent()");
    }
    current = findPrev(current);
}
// Other
// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value·
// are separated by the sequence space-colon-space " : ". The pairs are
// arranged· in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    string s = "";
    this->inOrderString(s, this->root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    string s = "";
    this->preOrderString(s, this->root);
    return s;
}
// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary &D) const {
    if (this->size() != D.size()) {
        return false;
    }
    return (this->to_string() == D.to_string()) ? true : false;
}

// OverLoaded Operaters

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream &operator<<(std::ostream &stream, Dictionary &D) {
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals().·
bool operator==(const Dictionary &A, const Dictionary &B) {
    return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary &Dictionary::operator=(const Dictionary &D) {
    if (this != &D) {
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}
