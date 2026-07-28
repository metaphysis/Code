// Hehe
// UVa ID: 12936
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163260297

#include <bits/stdc++.h>
using namespace std;

bool isHeheVariant(const string& word) {
    int len = word.size();
    if (len < 4 || len % 2 != 0) return false;
    for (int i = 0; i < len; i += 2)
        if (word[i] != 'h' || word[i + 1] != 'e') return false;
    return true;
}

bool sentenceEndsWithHehe(const string& sentence) {
    string processed;
    for (char c : sentence) {
        if (isalpha(c)) processed.push_back(tolower(c));
        else processed.push_back(' ');
    }
    stringstream ss(processed);
    string word;
    while (ss >> word)
        if (isHeheVariant(word)) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    map<pair<string, string>, vector<string>> conversations;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        size_t colon = line.find(':');
        if (colon == string::npos) continue;
        string left = line.substr(0, colon);
        string right = line.substr(colon + 1);
        string clean;
        for (char c : left)
            if (!isspace(c)) clean.push_back(c);
        size_t arrow = clean.find("->");
        if (arrow == string::npos) continue;
        string sender = clean.substr(0, arrow);
        string receiver = clean.substr(arrow + 2);
        string p1 = sender, p2 = receiver;
        if (p1 > p2) swap(p1, p2);
        auto key = make_pair(p1, p2);
        conversations[key].push_back(right);
    }
    int total = conversations.size();
    int heheCount = 0;
    for (auto& entry : conversations) {
        auto& msgs = entry.second;
        if (msgs.empty()) continue;
        if (sentenceEndsWithHehe(msgs.back())) heheCount++;
    }
    int ans = (heheCount * 100 + total / 2) / total;
    cout << ans << "%\n";
    return 0;
}
