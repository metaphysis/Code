#include <bits/stdc++.h>
using namespace std;

using Uid = int;
using Key = pair<string, vector<Uid>>;
map<Key, Uid> mp;
Uid tot;

Uid parse(const string &s, int &pos) {
    int st = pos;
    while (pos < s.size() && isalpha(s[pos])) pos++;
    string name = s.substr(st, pos - st);
    vector<Uid> subs;
    if (pos < s.size() && s[pos] == '(') {
        pos++;
        while (true) {
            subs.push_back(parse(s, pos));
            if (s[pos] == ')') break;
            pos++;
        }
        pos++;
    }
    Key k = make_pair(name, subs);
    if (!mp.count(k)) mp[k] = ++tot;
    return mp[k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    while (getline(cin, s)) {
        mp.clear();
        tot = 0;
        int pos = 0;
        parse(s, pos);
        cout << tot << '\n';
    }
    return 0;
}
