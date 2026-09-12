#include <bits/stdc++.h>
using namespace std;

int n, nextId;
unordered_map<string, int> wordId;
unordered_set<string> known, gram;

string lowerWord(string s) {
    for (char &c : s) c = tolower((unsigned char)c);
    return s;
}

int getId(const string &s) {
    string t = lowerWord(s);
    if (!wordId.count(t)) wordId[t] = nextId++;
    return wordId[t];
}

string getKey(const vector<int> &ids, int l, int r) {
    string key;
    for (int i = l; i < r; i++) {
        key += to_string(ids[i]);
        key += ',';
    }
    return key;
}

void addSentence(const vector<string> &words) {
    int m = words.size();
    vector<int> ids(m);
    for (int i = 0; i < m; i++) {
        ids[i] = getId(words[i]);
        known.insert(lowerWord(words[i]));
    }
    for (int len = 1; len <= n; len++)
        for (int i = 0; i + len <= m; i++)
            gram.insert(getKey(ids, i, i + len));
}

bool understandSentence(const vector<string> &words) {
    int m = words.size();
    vector<int> ids(m);
    for (int i = 0; i < m; i++) ids[i] = getId(words[i]);
    for (int len = 2; len <= n; len++)
        for (int i = 0; i + len <= m; i++)
            if (!gram.count(getKey(ids, i, i + len))) return false;
    return true;
}

void printSentence(const vector<string> &words) {
    cout << "What does the sentence \"";
    for (int i = 0; i < (int)words.size(); i++) {
        if (i) cout << ' ';
        cout << words[i];
    }
    cout << "\" mean?\n";
}

void processToday(vector<string> &words) {
    if (words.empty()) return;
    for (const string &word : words) {
        string t = lowerWord(word);
        if (!known.count(t)) {
            cout << "What does the word \"" << word << "\" mean?\n";
            known.insert(t);
        }
    }
    if (!understandSentence(words)) printSentence(words);
    addSentence(words);
    words.clear();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cas = 0;
    string token;
    while (cin >> n) {
        wordId.clear();
        known.clear();
        gram.clear();
        nextId = 0;
        known.insert("joe");
        vector<string> words;
        while (cin >> token) {
            if (token == "*") {
                if (!words.empty()) {
                    addSentence(words);
                    words.clear();
                }
                break;
            }
            if (token == "." || token == "," || token == ":" || token == ";" || token == "?" || token == "!") {
                addSentence(words);
                words.clear();
            } else words.push_back(token);
        }
        if (cas++) cout << '\n';
        cout << "Learning case " << cas << '\n';
        while (cin >> token) {
            if (token == "#") {
                processToday(words);
                break;
            }
            if (token == "." || token == "," || token == ":" || token == ";" || token == "?" || token == "!") {
                processToday(words);
            } else words.push_back(token);
        }
    }
    return 0;
}
