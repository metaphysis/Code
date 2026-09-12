#include <bits/stdc++.h>
using namespace std;

vector<string> getAll() {
    vector<long long> fib;
    vector<string> all;
    set<string> st;
    long long a = 1, b = 1, c;
    fib.push_back(a);
    fib.push_back(b);
    while (b <= LLONG_MAX - a) {
        c = a + b;
        fib.push_back(c);
        a = b;
        b = c;
    }
    for (int i = 0; i < (int)fib.size(); i++) {
        for (int j = 0; j < (int)fib.size(); j++) {
            if (i != j) st.insert(to_string(fib[i]) + to_string(fib[j]));
        }
    }
    for (set<string>::iterator it = st.begin(); it != st.end(); it++) all.push_back(*it);
    return all;
}

bool isSub(const string &t, const vector<vector<int> > &pos) {
    int cur = -1, d;
    for (char ch : t) {
        d = ch - '0';
        vector<int>::const_iterator it = upper_bound(pos[d].begin(), pos[d].end(), cur);
        if (it == pos[d].end()) return false;
        cur = *it;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> all = getAll();
    string s;
    while (cin >> s) {
        vector<vector<int> > pos(10);
        int ans = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            if (isdigit(s[i])) pos[s[i] - '0'].push_back(i);
        }
        for (int i = 0; i < (int)all.size(); i++) {
            if (isSub(all[i], pos)) ans++;
        }
        cout << ans << '\n';
    }
    return 0;
}
