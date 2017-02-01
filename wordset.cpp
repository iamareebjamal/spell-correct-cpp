#include <queue>
#include <iostream>
#include "wordset.h"

wordset::wordset(const string& filename) {
    ifstream input(filename);

    if (input.is_open()) {
        string line;
        while ( getline(input,line) ) {
            dictionary.insert(line);
        }
        input.close();
    }
}

/*
 * count method provides O(1) look-up instead of
 * finding the word in the hash set.
 */
bool wordset::contains(const string &word) {
    return dictionary.count(word) > 0;
}

void wordset::create_deletes(const string &word) {
    for (int i = 0; i < word.length(); ++i) {
        string temp = word;
        temp.erase(temp.begin()+i);
        edits.insert(temp);
    }
}

void wordset::create_transposes(const string &word) {
    for (int i = 0; i < word.length()-1; ++i) {
        string temp = word;
        swap(temp[i], temp[i+1]);
        edits.insert(temp);
    }
}

void wordset::create_replaces(const string &word) {
    for (int i = 0; i < word.length(); ++i) {
        for (char c : alphabet) {
            string temp = word;
            swap(temp[i], c);
            edits.insert(temp);
        }
    }
}

void wordset::create_inserts(const string &word) {
    for (int i = 0; i < word.length(); ++i) {
        for (char c : alphabet) {
            string temp = word;
            temp.insert(temp.begin()+i, c);
            edits.insert(temp);
        }
    }
}

set<string> wordset::create_double_edits(const string &word) {
    set<string> double_edits;

    for(string edit1 : create_edits(word)) {
        for (string edit2 : create_edits(edit1)) {
            double_edits.insert(edit2);
        }
    }

    return double_edits;
}

set<string> wordset::create_edits(const string &word) {
    edits.clear();

    if(contains(word))
        edits.insert(word);

    create_deletes(word);
    create_transposes(word);
    create_replaces(word);
    create_inserts(word);

    return edits;
}

vector<string> wordset::get_single_edits(const string &word){
    vector<string> single_edits;

    for(string str : create_edits(word)) {
        if(contains(str)) single_edits.push_back(str);
    }

    return single_edits;
}

vector<string> wordset::get_double_edits(const string &word){
    vector<string> double_edits;

    for(string str : create_double_edits(word)) {
        if(contains(str)) double_edits.push_back(str);
    }

    return double_edits;
}


int common_prefix_len(string a, string b) {
    int len = 0;
    while(a[len] == b[len++]);

    return len-1;
}


bool is_weak_anagram(string a, string b) {
    set<char> set1, set2;

    for_each(a.begin(), a.end(),
             [&set1] (char c) -> void {
                 set1.insert(c);
             });

    for_each(b.begin(), b.end(),
             [&set2] (char c) -> void {
                 set2.insert(c);
             });

    return set1 == set2;
}

void set_priority(vector<string>& v, const string& word){

    auto compare = [](pair<string, int> left, pair<string, int> right) {
        return right.second > left.second;
    };

    priority_queue<
            pair<string, int>,
            vector<pair<string, int>>,
            decltype(compare) >
    result(compare);

    for(string str : v) {
        int priority = 0;

        if(str == word)
            priority += 10;

        if(is_weak_anagram(str, word))
            priority += 5;

        if(str.length() == word.length())
            priority += 1;

        priority += 2*common_prefix_len(str, word);

        pair<string, int> compound = pair<string, int>(str, priority);
        result.push(compound);
    }

    v.clear();
    while(!result.empty()) {
        v.push_back(result.top().first);
        result.pop();
    }

};

vector<string> wordset::get_top_matches(const string &word, int limit) {
    vector<string> single_edits = get_single_edits(word);
    vector<string> double_edits = get_double_edits(word);

    for (string str : double_edits) {
        if(find(single_edits.begin(), single_edits.end(), str)==single_edits.end())
            single_edits.push_back(str);
    }

    set_priority(single_edits, word);

    if(single_edits.size() > limit)
        return vector<string>(single_edits.begin(), single_edits.begin()+limit);

    return single_edits;
}
