// Entropy Text Analyzer
// UVa ID: 860
// Verdict: Accepted
// Submission Date: 2018-03-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string line, word;
    string separators = ",.:;!?\"() ";
    int total = 0;
    map<string, int> freq;
    while (getline(cin, line)) {
        if (line == "****END_OF_INPUT****") break;
        if (line == "****END_OF_TEXT****") {
            if (total > 0) {
                double entropy = 0.0;
                for (auto &p : freq) {
                    double pi = p.second;
                    entropy += pi * (log10(total) - log10(pi));
                }
                entropy /= total;
                double rel = entropy / log10(total) * 100.0;
                cout << total << ' ' << fixed << setprecision(1) << entropy << ' ' << int(rel + 0.5) << '\n';
                freq.clear();
                total = 0;
            }
            continue;
        }
        word.clear();
        for (char c : line) {
            if (separators.find(c) == string::npos) word += tolower(c);
            else {
                if (!word.empty()) {
                    freq[word]++;
                    total++;
                    word.clear();
                }
            }
        }
        if (!word.empty()) {
            freq[word]++;
            total++;
        }
    }
    return 0;
}
