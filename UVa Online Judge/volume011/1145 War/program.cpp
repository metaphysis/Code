#include <bits/stdc++.h>
using namespace std;

int getVal(char c) {
    if (c >= '7' && c <= '9') return c - '7';
    if (c == 'T') return 3;
    if (c == 'J') return 4;
    if (c == 'Q') return 5;
    if (c == 'K') return 6;
    return 7;
}

string getDeck(const deque<char> &d) {
    string s;
    for (char c : d) s += c;
    return s;
}

string getKey(const deque<char> &a, const deque<char> &b) {
    return getDeck(a) + '#' + getDeck(b);
}

int simGame(string sa, string sb) {
    deque<char> a(sa.begin(), sa.end()), b(sb.begin(), sb.end());
    unordered_set<string> seen;
    while (true) {
        if (a.empty() && b.empty()) return 0;
        if (a.empty()) return 2;
        if (b.empty()) return 1;
        string key = getKey(a, b);
        if (seen.count(key)) return 3;
        seen.insert(key);
        vector<pair<char, char>> ties;
        while (true) {
            if (a.empty() && b.empty()) return 0;
            if (a.empty()) return 2;
            if (b.empty()) return 1;
            char x = a.front(), y = b.front();
            a.pop_front();
            b.pop_front();
            if (x == y) {
                ties.push_back(make_pair(x, y));
                continue;
            }
            deque<char> *win;
            if (getVal(x) > getVal(y)) win = &a;
            else win = &b;
            if (getVal(x) > getVal(y)) {
                win->push_back(x);
                win->push_back(y);
            } else {
                win->push_back(y);
                win->push_back(x);
            }
            for (int i = static_cast<int>(ties.size()) - 1; i >= 0; --i) {
                win->push_back(ties[i].first);
                win->push_back(ties[i].second);
            }
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string a, b;
    while (cin >> a >> b) {
        int ans = simGame(a, b);
        if (ans == 1) cout << "A wins\n";
        else if (ans == 2) cout << "B wins\n";
        else if (ans == 0) cout << "draw game\n";
        else cout << "play forever\n";
    }
    return 0;
}
