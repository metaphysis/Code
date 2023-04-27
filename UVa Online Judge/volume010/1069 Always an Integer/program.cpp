// Always an Integer
// UVa ID: 1069
// Verdict: Accepted
// Submission Date: 2023-04-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
struct __TERM {
    int C, E;
} T[110];
void parse(string s, int cnt) {
    int sign = s.front() == '+' ? 1 : -1;
    int idx = 1;
    if (isdigit(s[idx])) {
        T[cnt].C = 0;
        while (isdigit(s[idx])) {
            T[cnt].C = T[cnt].C * 10 + s[idx] - '0';
            idx++;
        }
    } else T[cnt].C = 1;
    T[cnt].C *= sign;
    if (idx >= s.length()) T[cnt].E = 0;
    else {
        if (idx + 1 >= s.length()) T[cnt].E = 1;
        else T[cnt].E = stoi(s.substr(idx + 2));
    }
}
long long powd(int x, int e, long long D) {
    long long r = 1, y = x;
    while (e) {
        if (e & 1) r *= y, r %= D;
        y *= y, y %= D, e >>= 1;
    }
    return r;
}
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string line;
    int cases = 1;
    while (getline(cin, line)) {
        if (line.front() == '.') break;
        long long D = stoll(line.substr(line.find(')') + 2));
        string P = line.substr(1, line.find(')') - 1);
        if (P.front() != '-') P.insert(P.begin(), '+');
        P.push_back('+');
        int cnt = 0;
        string blk;
        for (int i = 0; i < P.length(); i++) {
            if (P[i] == '-' || P[i] == '+') {
                if (blk.size()) {
                    parse(blk, cnt++);
                    blk.clear();
                }
            }
            blk += P[i];
        }
        int flag = 1;
        for (int i = 1; flag && i <= T[0].E + 1; i++) {
            long long r = 0;
            for (int j = 0; j < cnt; j++)
                r += 1LL * T[j].C * powd(i, T[j].E, D) % D;
            if (r % D != 0) flag = 0;
        }
        cout << "Case " << cases++ << ": ";
        cout << (flag ? "Always an integer" : "Not always an integer");
        cout << '\n';
    }
    return 0;
}
