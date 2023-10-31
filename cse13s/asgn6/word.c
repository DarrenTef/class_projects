#include "word.h"
#include <stdlib.h>
#include "code.h"

// Done
Word *word_create(uint8_t *syms, uint32_t len) {
    Word *w = (Word *) malloc(sizeof(Word));
    if (w) {
        w->len = len;
        w->syms = malloc(len * sizeof(uint8_t));
        for (int i = 0; i < len; i += 1) {
            w->syms[i] = syms[i];
        }
    }
    return w;
}

// Call word create with w len + 1
// Set character at address w len to sym
// return new word
// Done
Word *word_append_sym(Word *w, uint8_t sym) {
    w = word_create(w -> syms, w->len + 1);
    w->syms[w->len] = sym;
    return w;
}

// Done
void word_delete(Word *w) {
    if (w != NULL) {
        free(w);
    }
    return;
}

// Done - Might need to return the word table?
WordTable *wt_create(void) {
    WordTable *wt = (WordTable *) malloc(MAX_CODE);
    wt[EMPTY_CODE] = word_create(NULL, 0);
}

// I loop through each word in the word table and free it
// But I would need to free every word's trie.
// Done
void wt_reset(WordTable *wt) {
for (int i = 0; i < MAX_CODE; i += 1) {
    word_delete(wt->word);
    wt->word = NULL;
    }
}

// for i in wordtable if words call word delete on words, then free the table. - Credit lev for wt create, and delete
// Done
void wt_delete(WordTable *wt) {
    for (int i = 0; i < MAX_CODE; i += 1) {
        if (wt[i]) {
            wt_delete(&wt[i]);
        }
    }
    free(wt);
}
