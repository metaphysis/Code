// Meta Editor
// UVa ID: 10438
// Verdict: Accepted
// Submission Date: 2026-07-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<string> words;
        string w;
        while (iss >> w) words.push_back(w);
        while (1) {
            bool changed = false;
            for (int i = 0; i < words.size(); i++)
                for (int w = 1; i + 2 * w <= words.size(); w++) {
                    bool same = true;
                    for (int k = 0; k < w; k++)
                        if (words[i + k] != words[i + w + k]) {
                            same = false;
                            break;
                        }
                    if (same) {
                        words.erase(words.begin() + i, words.begin() + i + w);
                        changed = true;
                        break;
                    }
                }
            if (!changed) break;
        }
        for (int i = 0; i < words.size(); i++) {
            if (i) cout << ' ';
            cout << words[i];
        }
        cout << '\n';
    }
    return 0;
}
