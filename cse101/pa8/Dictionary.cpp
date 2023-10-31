/* Darren Lee, dlee181
 * 2023 Spring CSE101 PA8
 *·Dictionary.cpp
 * RBT Dictionary ADT
 */

#include "Dictionary.h"
#include <iostream>
#include <sstream>
#include <stdbool.h>
#include <string.h>
#include <string>

using namespace std;

#define BLACK -1
#define RED -2
#define UNDEFINED -3

Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = BLACK;
}
// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string &s, Node *R) const {
    if (R != nil) {
        // Call in order string.
        inOrderString(s, R->left);
        // Appends key and value to string.
        s += R->key + " : ";
        s += std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The
// appended string will consist of keys only, with the order determined by a
// pre-order tree walk. The keys stored in black Nodes will be appended as
// "key\n", and the keys stored in red Nodes will be appended as "key
// (RED)\n". The output of this function is demonstrated in
// /Examples/pa8/DictionaryClient-out.
void Dictionary::preOrderString(std::string &s, Node *R) const {
    if (R != nil) {
        s += R->key;
        if (R->color == RED) {
            s += " (RED)\n";
        } else {
            s += "\n";
        }

        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// BST_insert()
// Inserts a copy of the Node *M into this Dictionary. Used by
// preOrderCopy().
void Dictionary::BST_insert(Node *M) {
    if (M == nil) {
        throw logic_error("Dictionary: BST_insert(): M == nil");
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node *R, Node *N) {
    if (R != N) {
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
// opposite treeSuccessor
// invert lefts and invert min
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

// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node *N) {
    Node *Y = N->right;
    N->right = Y->left;
    if (Y->left != this->nil) {
        Y->left->parent = N;
    }
    Y->parent = N->parent;
    if (N->parent == this->nil) {
        this->root = Y;
    } else if (N == N->parent->left) {
        N->parent->left = Y;
    } else {
        N->parent->right = Y;
    }
    Y->left = N;
    N->parent = Y;
}

// RightRotate()
void Dictionary::RightRotate(Node *N) {
    Node *Y = N->left;
    N->left = Y->right;
    if (Y->right != this->nil) {
        Y->right->parent = N;
    }
    Y->parent = N->parent;
    if (N->parent == this->nil) {
        this->root = Y;
    } else if (N == N->parent->right) {
        N->parent->right = Y;
    } else {
        N->parent->left = Y;
    }
    Y->right = N;
    N->parent = Y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node *N) {
    while (N->parent->color == RED) {
        if (N->parent == N->parent->parent->left) {
            Node *Y = N->parent->parent->right;
            if (Y->color == RED) {
                N->parent->color = BLACK;
                Y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if (N == N->parent->right) {
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        } else {
            Node *Y = N->parent->parent->left;
            if (Y->color == RED) {
                N->parent->color = BLACK;
                Y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if (N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    // cout << "key:" << N->key << "val" << N->val << endl;
    this->root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node *u, Node *v) {
    if (u->parent == this->nil) {
        this->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node *N) {
    // cout << "N->val " << N->val << endl;cout << "N->key" << N->key << endl;
    // cout << "root->val " << root->val << endl; cout << "root->key" <<
    // root->key << endl; cout << "N->color " << N->color << endl;
    while (N != this->root && N->color == BLACK) {
        if (N == N->parent->left) {
            Node *W = N->parent->right;
            if (W->color == RED) {
                W->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                W = N->parent->right;
            }
            if (W->left->color == BLACK && W->right->color == BLACK) {
                W->color = RED;
                N = N->parent;
            } else {
                if (W->right->color == BLACK) {
                    W->left->color = BLACK;
                    W->color = RED;
                    RightRotate(W);
                    W = N->parent->right;
                }
                W->color = N->parent->color;
                N->parent->color = BLACK;
                W->right->color = BLACK;
                LeftRotate(N->parent);
                N = this->root;
            }
        } else {
            Node *W = N->parent->left;
            if (W->color == RED) {
                W->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                W = N->parent->left;
            }
            if (W->right->color == BLACK && W->left->color == BLACK) {
                W->color = RED;
                N = N->parent;
            } else {
                if (W->left->color == BLACK) {
                    W->right->color = BLACK;
                    W->color = RED;
                    LeftRotate(W);
                    W = N->parent->left;
                }
                W->color = N->parent->color;
                N->parent->color = BLACK;
                W->left->color = BLACK;
                RightRotate(N->parent);
                N = this->root;
            }
        }
    }
    N->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node *N) {
    Node *X;
    // cout << "X->color" << X->color << endl;
    Node *Y = N;
    int y_original = Y->color;
    // cout << "y-origin" << y_original << endl;
    if (N->left == this->nil) {
        X = N->right;
        RB_Transplant(N, N->right);
    } else if (N->right == this->nil) {
        X = N->left;
        RB_Transplant(N, N->left);
    } else {
        Y = findMin(N->right);
        // cout << Y->color << endl;
        y_original = Y->color;
        X = Y->right;
        if (Y->parent == N) {
            X->parent = Y;
        } else {
            RB_Transplant(Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
        }
        RB_Transplant(N, Y);
        Y->left = N->left;
        Y->left->parent = Y;
        Y->color = N->color;
    }
    if (y_original == BLACK) {
        RB_DeleteFixUp(X);
    }
    delete N;
}
// Put Dict struct down here to go with compiler

Dictionary::Dictionary() { // Constructor for Dictionary.
    // Set Dictionary pointers.
    nil = new Node("\000", 0);
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;

    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(
    const Dictionary &D) { // Copy constructor for Dictionary.
    // Copy Dictionary pointers.
    nil = new Node("\000", 0);
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;

    root = nil;
    current = nil;
    num_pairs = 0;

    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() { // Destructor for Dictionary.
    postOrderDelete(root);

    root = nil;
    current = nil;
    num_pairs = 0;

    delete (nil);
}

// Access functions --------------------------------------------------------
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

// Manipulation procedures -------------------------------------------------
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
    if (search(root, k) != nil) {
        Node *N = search(root, k);
        N->val = v;
        return;
    }
    Node *Y = nil;
    Node *X = this->root;
    while (X != nil) {
        Y = X;
        if (k < X->key) {
            X = X->left;
        } else {
            X = X->right;
        }
        /*else {
            X->val = v;
            return;
        }
        */
    }
    Node *Z = new Node(k, v);
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
    }
    Z->color = RED;
    Z->left = this->nil;
    Z->right = this->nil;
    RB_InsertFixUp(Z);
    // cout << Z->key << endl;
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
    Node *K = search(this->root, k);
    if (K == current) {
        current = nil;
    }
    RB_Delete(K);
    num_pairs -= 1;
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

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key,
// value) pairs are separated by a newline "\n" character, and the items key
// and value are separated by the sequence space-colon-space " : ". The
// pairs are arranged in order, as defined by the order operator <.
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

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream &operator<<(std::ostream &stream, Dictionary &D) {
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals().
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
