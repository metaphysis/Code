#include <bits/stdc++.h>
using namespace std;

int solve() {
    unordered_map<string, long long> spamCnt, hamCnt;
    long long spamTot = 0, hamTot = 0;
    string line, word;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        string type = line;
        vector<string> words;
        while (getline(cin, line) && line != "==") {
            stringstream ss(line);
            while (ss >> word) {
                for (char &ch : word) ch = tolower(ch);
                words.push_back(word);
            }
        }
        if (type == "MESSAGE SPAM") {
            for (const string &cur : words) {
                spamCnt[cur]++;
                spamTot++;
            }
        } else if (type == "MESSAGE HAM") {
            for (const string &cur : words) {
                hamCnt[cur]++;
                hamTot++;
            }
        } else {
            long double score = 0;
            for (const string &cur : words) {
                long double prob;
                bool inSpam = spamCnt.count(cur);
                bool inHam = hamCnt.count(cur);
                if (!inSpam && !inHam) {
                    prob = 0.4L;
                } else {
                    long double spamProb = inSpam && spamTot > 0 ? (long double)spamCnt[cur] / spamTot : 0;
                    long double hamProb = inHam && hamTot > 0 ? (long double)hamCnt[cur] / hamTot : 0;
                    prob = spamProb / (spamProb + hamProb);
                    if (prob < 0.01L) prob = 0.01L;
                    if (prob > 0.99L) prob = 0.99L;
                }
                score += log(prob / (1 - prob));
            }
            long double prob;
            if (score >= 0) {
                prob = 1 / (1 + expl(-score));
            } else {
                long double value = expl(score);
                prob = value / (1 + value);
            }
            if (prob >= 0.6L) {
                cout << "Spam\n";
            } else if (prob <= 0.4L) {
                cout << "Ham\n";
            } else {
                cout << "Unsure\n";
            }
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
