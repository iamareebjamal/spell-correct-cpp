/**
 * Implementation of a spell corrector using the guidance of
 * algorithm provided by Peter Norvig of Google using Levenshtein
 * Damerau edit distance between strings
 */

#ifndef FUZZYSEARCH_WORDSET_H
#define FUZZYSEARCH_WORDSET_H

#include <set>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

namespace {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
}


class wordset {
private:
    /* unordered_set used for O(1) look-up time */
    unordered_set<string> dictionary;
    set<string> edits;

    void create_deletes(const string& word);
    void create_transposes(const string& word);
    void create_replaces(const string& word);
    void create_inserts(const string& word);

    set<string> create_edits(const string& word);

    set<string> create_double_edits(const string& word);

public:
    /*
     * Takes a filename of dictionary and inserts all words from it in
     * the unordered set which is practically a hash set.
     */
    explicit wordset(const string& filename);

    /*
     * Checks if the word passed as argument exists in the word set.
     */
    bool contains(const string& word);

    vector<string> get_single_edits(const string& word);
    vector<string> get_double_edits(const string& word);

    vector<string> get_top_matches(const string& word, int limit);

};


#endif //FUZZYSEARCH_WORDSET_H
