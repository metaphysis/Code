// Count the eWords
// UVa ID: 10352
// Verdict: Accepted
// Submission Date: 2025-11-23
// UVa Run Time: 0.070s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

string getKey(string s) {
    if (s.length() > 2) s[2] = ' ';
    return s.substr(0, 5);
}

int main() {
    int cases = 1;
    string word;
    map<string, vector<string>> groups;
    while (cin >> word) {
        if (word == "#") {
            cout << "Set #" << cases++ << ":" << '\n';
            for (auto& g : groups) 
                cout << g.second.back().substr(0, 5) << ' ' << g.second.size() << '\n';
            cout << '\n';
            groups.clear();
            continue;
        }
        groups[getKey(word)].push_back(word);
    }
    return 0;
}
