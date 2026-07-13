// Chat Rooms
// UVa ID: 1186
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

bool isConsonant(char c) {
    if (!isalpha(c)) return false;
    char low = tolower(c);
    return !(low == 'a' || low == 'e' || low == 'i' || low == 'o' || low == 'u' || low == 'y');
}

bool hasExceedFiveConsecutive(const string &s) {
    int cnt = 0;
    for (char c : s) {
        if (isConsonant(c)) {
            ++cnt;
            if (cnt > 5) return true;
        } else cnt = 0;
    }
    return false;
}

bool hasWordWithMoreThanFourConsecutive(const string &s) {
    int i = 0, len = s.size();
    while (i < len) {
        if (isalpha(s[i])) {
            int j = i;
            while (j < len && isalpha(s[j])) ++j;
            int cnt = 0, maxCnt = 0;
            for (int k = i; k < j; ++k) {
                if (isConsonant(s[k])) {
                    ++cnt;
                    if (cnt > maxCnt) maxCnt = cnt;
                } else cnt = 0;
            }
            if (maxCnt > 4) return true;
            i = j;
        } else i++;
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    deque<pair<string, bool>> history;
    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        bool hasFive = hasExceedFiveConsecutive(line);
        bool hasFour = hasWordWithMoreThanFourConsecutive(line);
        int badCount = 0;
        for (auto &p : history) if (p.second) ++badCount;
        int duplicate = 0;
        for (auto &p : history) if (p.first == line) duplicate++;
        if (hasFive || (hasFour && badCount > 2) || duplicate >= 2) cout << 'n';
        else cout << 'y';
        cout << '\n';
        history.push_back({line, hasFive || hasFour});
        while (history.size() > 10) history.pop_front();
    }
    return 0;
}
