#include "trie.h"
#include <stdio.h>
#include "code.h"

// Done
TrieNode *trie_node_create(uint16_t index) {
    Trienode *t = (Trienode*) calloc(sizeof(Trienode));
    t -> code = index;
    return t;
}
// Done
void trie_node_delete(TrieNode *n) {
    if (n != NULL) {
        free(n);
    }
    return;
}

// Done
TrieNode *trie_create(void) {
    return trie_node_create(EMPTY_CODE);
}

// Unsure
void trie_reset(TrieNode *root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < ALPHABET; i += 1) {
        trie_delete(root -> children[i]);
        root -> children[i] = NULL;
    }
}

// Should be good
void trie_delete(TrieNode *n) {
    if (n == NULL) {
        return;
    }

    for (int i = 0; i < ALPHABET; i += 1) {
        trie_delete(n -> children[i]);
    }
    trie_node_delete(n);
}

// Done
TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    return n -> children[sym];
}

