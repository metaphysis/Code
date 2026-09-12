#include <bits/stdc++.h>
using namespace std;

struct Page {
    vector<string> words;
};

struct Result {
    int score, pageId;
};

string toLowerCase(string word) {
    for (char &ch : word)
        ch = tolower(ch);
    return word;
}

int getScore(const vector<string> &pageWords, const vector<string> &queryWords) {
    int score = 0;
    for (int i = 0; i < (int)queryWords.size(); i++) {
        for (int j = 0; j < (int)pageWords.size(); j++) {
            if (queryWords[i] == pageWords[j]) {
                score += (8 - i) * (8 - j);
                break;
            }
        }
    }
    return score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<Page> pages;
    string line;
    int queryId = 0;
    cout << "Query Pages\n";
    while (getline(cin, line)) {
        if (line.empty())
            continue;
        stringstream ss(line);
        char code;
        ss >> code;
        if (code == 'E')
            break;
        vector<string> words;
        string word;
        while (ss >> word)
            words.push_back(toLowerCase(word));
        if (code == 'P') {
            Page page;
            page.words = words;
            pages.push_back(page);
        } else if (code == 'Q') {
            queryId++;
            vector<Result> results;
            for (int i = 0; i < (int)pages.size(); i++) {
                int score = getScore(pages[i].words, words);
                if (score > 0)
                    results.push_back({score, i + 1});
            }
            sort(results.begin(), results.end(), [](const Result &a, const Result &b) {
                if (a.score != b.score)
                    return a.score > b.score;
                return a.pageId < b.pageId;
            });
            cout << "Q" << queryId << ":  ";
            int limit = min(5, (int)results.size());
            for (int i = 0; i < limit; i++)
                cout << " P" << results[i].pageId;
            cout << '\n';
        }
    }
    return 0;
}
