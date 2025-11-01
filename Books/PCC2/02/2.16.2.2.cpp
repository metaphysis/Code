#include <bits/stdc++.h>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

rope<char> r;

int cursor = 0;

void insert() {
    int n;
    cin >> n;
    string s, line;
    cin.ignore(256, '\n');
    while (n > 0) {
        getline(cin, line);
        while (line.back() < 32 || line.back() > 126) line.pop_back();
        s += line;
        n -= line.length();
    }
    r.insert(cursor, s.c_str());
}

int main(int argc, char *argv[]) {
    int t, n;
    cin >> t;
    string cmd;
    for (int i = 1; i <= t; i++) {
        cin >> cmd;
        if (cmd == "Insert")        insert();
        else if (cmd == "Delete")   { cin >> n; r.erase(cursor, n); }
        else if (cmd == "Get")      { cin >> n; cout << r.substr(cursor, n) << '\n'; }
        else if (cmd == "Move")     cin >> cursor;
        else if (cmd == "Prev")     cursor--;
        else if (cmd == "Next")     cursor++;
    }
    return 0;
}
