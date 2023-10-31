// Implementation of all the set.h functions

#include "set.h"

#include "stats.h"

// assigns ints to each value , shell 0, quick 1..
typedef enum { SHELL, QUICK, HEAP, BATHCER, NUM_SORTS } SORTS;

Set set_empty(void) {
    return 0;
}

Set set_universal(void) {
    return set_complement(set_empty());
}

Set set_insert(Set s, uint8_t x) // x is the value that I want to shift left by
{ // Also set a uint32_t to 1
    uint32_t membership = 1;
    membership <<= x;
    return s | membership;
}

Set set_remove(Set s, uint8_t x) {
    uint32_t cancellation = 1 << x;
    return s & ~cancellation;
}
bool set_member(Set s, uint8_t x) {
    uint32_t membership_check = 1 << x;
    if (membership_check & s) {
        return true;
    }
    return false;
}
Set set_union(Set s, Set t) {
    return (s | t);
}
Set set_intersect(Set s, Set t) {
    return (s & t);
}
Set set_difference(Set s, Set t) {
    return (s & ~t);
}
Set set_complement(Set s) {
    return (~s);
}
