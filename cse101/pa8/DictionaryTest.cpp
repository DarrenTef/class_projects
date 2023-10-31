/* Darren Lee, dlee181
 * 2023 Spring CSE101 PA8
 *·DictionaryTest.cpp
 * RBT Dictionary ADT test
 */

#include <iostream>
#include <stdexcept>
#include <string>

#include "Dictionary.h"
using namespace std;

int main() {
    string S[] = {
        "a",     "about",  "after",  "all",   "also",  "an",      "and",
        "any",   "are",    "as",     "at",    "be",    "because", "been",
        "but",   "by",     "can",    "come",  "could", "day",     "do",
        "even",  "for",    "from",   "get",   "give",  "go",      "good",
        "have",  "he",     "her",    "him",   "his",   "how",     "I",
        "if",    "in",     "into",   "is",    "it",    "its",     "just",
        "know",  "like",   "little", "long",  "look",  "make",    "man",
        "many",  "may",    "me",     "more",  "most",  "much",    "must",
        "my",    "new",    "no",     "not",   "now",   "of",      "on",
        "one",   "only",   "or",     "other", "our",   "out",     "over",
        "own",   "people", "say",    "see",   "she",   "so",      "some",
        "take",  "than",   "that",   "the",   "their", "them",    "then",
        "there", "these",  "they",   "thing", "think", "this",    "those",
        "time",  "to",     "two",    "up",    "use",   "very",    "want",
        "way",   "we",     "well",   "what",  "when",  "which",   "who",
        "will",  "with",   "would",  "year",  "you",   "your"};

    string T[] = {"across",  "always", "amount", "answer",  "around",  "asleep",
                  "assume",  "attack", "attend", "author",  "before",  "behind",
                  "belong",  "beside", "beyond", "bottle",  "brave",   "bridge",
                  "bright",  "burden", "butter", "camera",  "candle",  "carpet",
                  "castle",  "center", "choice", "church",  "circle",  "closer",
                  "coffee",  "colour", "common", "cookie",  "corner",  "cosmic",
                  "cotton",  "cousin", "credit", "curious", "damage",  "danger",
                  "decade",  "defend", "demand", "desire",  "device",  "dinner",
                  "distant", "doctor", "dollar", "donkey",  "double",  "dreams",
                  "driver",  "easily", "effect", "effort",  "either",  "eleven",
                  "emerge",  "empire", "endure", "enough",  "escape",  "evenly",
                  "exceed",  "except", "excite", "expand",  "expect",  "expert",
                  "extreme", "famous", "father", "feather", "fellow",  "fierce",
                  "figure",  "flower", "follow", "forest",  "forget",  "friend",
                  "future",  "garden", "gather", "gentle",  "gesture", "giant",
                  "glance",  "guitar"};

    cout << endl;

    Dictionary s;
    Dictionary t;

    for (int i = 0; i < 100; i += 1) {
        s.setValue(S[i], i + 1);
        t.setValue(T[i], i + 1);
    }

    // size()
    cout << "s.size() = \t" << s.size() << endl;
    cout << "Dictionary s = \n" << s << endl;
    cout << "t.size() = \t" << t.size() << endl;
    cout << "Dictionary t = \n" << t << endl;

    cout << endl;

    // contains()
    cout << s.contains("across") << endl;
    cout << t.contains("across") << endl;

    cout << endl;

    cout << s.contains("time") << endl;
    cout << t.contains("time") << endl;

    cout << endl;

    // getValue()
    cout << s.getValue("time") << endl;
    cout << t.getValue("across") << endl;

    cout << endl;

    // hasCurrent()
    cout << s.hasCurrent() << endl;
    cout << t.hasCurrent() << endl;

    // currentKey()
    if (!s.hasCurrent()) {
        cout << "s has no current" << endl;
    }
    else {
        cout << s.currentKey() << endl;
    }

    if (!(t.hasCurrent())) {
        cout << "t has no current" << endl;
    }
    else {
        cout << t.currentKey() << endl;
    }

    cout << endl;

    // clear()
    cout << "s\n" << s << endl;
    s.clear();
    cout << "cleared\n" << s << endl;

    cout << endl;

    // remove()
    cout << "t\n" << t << endl;
    t.remove("across");
    cout << "t.remove(\"across\")\n" << t << endl;

    cout << endl;

    // next()
    // t.next();
    // cout << "current after t.next() at the end\t" << t.currentKey() << endl;

    cout << endl;

    // begin
    // cout << "t-current\t\t" << t.currentKey() << endl;
    // t.begin();
    // cout << "current after t.begin\t" << t.currentKey() << endl;

    cout << endl;
    /*
    // end();
    t.end();
    cout << "current after t.end()\t" << t.currentKey() << endl;

    cout << endl;


    // begin()
    t.begin();
    t.next();
    cout << "current after t.begin() and t.next()\t" << t.currentKey() << endl;
    */
    // overloaders
    Dictionary a = t;
    cout << "a = t" << endl;
    cout << "a\n" << a << endl;
    cout << "t\n" << t << endl;
    cout << "a == t" << endl;
    if (a == t) {
        cout << "a equals t" << endl;
    }
    else {
        cout << "a doesnt equal t" << endl;
    }
    return 0;




}

