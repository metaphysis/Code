#include <bits/stdc++.h>
using namespace std;

struct BookWord {
    string text;
    int mask;
};

bool isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

char toLowerChar(char ch) {
    if (ch >= 'A' && ch <= 'Z')
        return ch - 'A' + 'a';
    return ch;
}

int getMask(const string &word) {
    int mask = 0;
    for (char ch : word)
        if (ch >= 'a' && ch <= 'z')
            mask |= 1 << (ch - 'a');
    return mask;
}

void addWords(const string &line, vector<BookWord> &words, unordered_set<string> &seen) {
    string word;
    for (int i = 0; i <= (int)line.size(); i++) {
        char ch = i < (int)line.size() ? line[i] : ' ';
        if (isLetter(ch) || ch == '-' || ch == '\'') {
            word += toLowerChar(ch);
        } else {
            if (!word.empty() && isLetter(word.front()) && isLetter(word.back()) && seen.insert(word).second)
                words.push_back({word, getMask(word)});
            word.clear();
        }
    }
}

string changeWord(const string &word, char first, char second) {
    string result = word;
    for (char &ch : result) {
        if (ch == first)
            ch = second;
        else if (ch == second)
            ch = first;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int dictCount;
        cin >> dictCount;
        unordered_set<string> dict;
        dict.reserve(dictCount * 2 + 1);
        for (int i = 0; i < dictCount; i++) {
            string word;
            cin >> word;
            for (char &ch : word)
                ch = toLowerChar(ch);
            dict.insert(word);
        }
        int bookCount;
        cin >> bookCount;
        string line;
        getline(cin, line);
        for (int book = 0; book < bookCount; book++) {
            getline(cin, line);
            vector<BookWord> words;
            unordered_set<string> seen;
            seen.reserve(1024);
            while (getline(cin, line) && line != ".THE END.")
                addWords(line, words, seen);
            int goodCnt[325] = {};
            int pairFirst[325], pairSecond[325], pairCount = 0;
            for (int first = 0; first < 26; first++) {
                for (int second = first + 1; second < 26; second++) {
                    pairFirst[pairCount] = first;
                    pairSecond[pairCount] = second;
                    pairCount++;
                }
            }
            for (const BookWord &bookWord : words) {
                bool oldGood = dict.count(bookWord.text) > 0;
                for (int id = 0; id < 325; id++) {
                    int first = pairFirst[id], second = pairSecond[id];
                    if ((bookWord.mask & (1 << first)) == 0 && (bookWord.mask & (1 << second)) == 0)
                        continue;
                    string changed = changeWord(bookWord.text, char('a' + first), char('a' + second));
                    bool newGood = dict.count(changed) > 0;
                    if (!oldGood && newGood)
                        goodCnt[id]++;
                    else if (oldGood && !newGood)
                        goodCnt[id]--;
                }
            }
            int bestId = 0;
            for (int id = 1; id < 325; id++)
                if (goodCnt[id] > goodCnt[bestId])
                    bestId = id;
            cout << char('a' + pairFirst[bestId]) << ' ' << char('a' + pairSecond[bestId]) << '\n';
        }
    }
    return 0;
}
