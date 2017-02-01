#include <iostream>
#include "wordset.h"
using namespace std;

int main() {
    wordset dictionary("wordlist.txt");

    bool run = true;
    while(run) {
        cout << "Enter a word in lower case : " << endl;
        string word;
        cin >> word;

        int limit;
        cout << "Enter how many words to suggest?" << endl;
        cin >> limit;

        for (string s : dictionary.get_top_matches(word, limit)) {
            cout << s << endl;
        }

        cout << "Do you want to run again? (Y/N)" << endl;
        char c;
        cin >> c;
        if (c != 'Y' && c != 'y')
            run = false;
    }
    return 0;
}