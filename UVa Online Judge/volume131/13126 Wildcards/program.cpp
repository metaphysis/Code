// Wildcards
// UVa ID: 13126
// Verdict: Accepted
// Submission Date: 2026-08-05
// UVa Run Time: 0.300s

#include <bits/stdc++.h>
using namespace std;

vector<int> buildPi(const string &part) {
    int m = (int)part.size();
    vector<int> pi(m);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && part[i] != part[j]) j = pi[j - 1];
        if (part[i] == part[j]) j++;
        pi[i] = j;
    }
    return pi;
}

void matchPart(const string &text, const string &part, const vector<int> &pi, int offset, vector<int> &seen, int tag, int limit) {
    int n = (int)text.size(), m = (int)part.size();
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && text[i] != part[j]) j = pi[j - 1];
        if (text[i] == part[j]) j++;
        if (j == m) {
            int start = i - m + 1 - offset;
            if (start >= 0 && start < limit) seen[start] = tag;
            j = pi[j - 1];
        }
    }
}

int solve(const string &text, const string &word) {
    int n = (int)text.size(), m = (int)word.size();
    int limit = n - m + 1;
    if (limit <= 0) return 0;
    vector<pair<int, string>> parts;
    for (int i = 0; i < m;) {
        if (word[i] == '?') {
            i++;
            continue;
        }
        int start = i;
        while (i < m && word[i] != '?') i++;
        parts.push_back({start, word.substr(start, i - start)});
    }
    if (parts.empty()) return limit;
    vector<char> valid(limit, 1);
    vector<int> seen(limit, 0);
    int tag = 0;
    for (const pair<int, string> &item : parts) {
        tag++;
        vector<int> pi = buildPi(item.second);
        matchPart(text, item.second, pi, item.first, seen, tag, limit);
        for (int i = 0; i < limit; i++)
            if (valid[i] && seen[i] != tag) valid[i] = 0;
    }
    int answer = 0;
    for (int i = 0; i < limit; i++)
        if (valid[i]) answer++;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string text, word;
    while (cin >> text >> word) cout << solve(text, word) << '\n';
    return 0;
}
