// Gray Code
// UVa ID: 10455
// Verdict: Accepted
// Submission Date: 2026-07-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long G[7];

string insertChar(const string& s, int pos, char c) {
    return s.substr(0, pos) + c + s.substr(pos);
}

vector<string> solve(int n, const string& start, long long idx) {
    vector<string> res;
    if (n == 1) {
        res.push_back(start);
        res.push_back(start[0] == '0' ? "1" : "0");
        return res;
    }
    long long half = G[n - 1];
    long long block = half * half;
    long long pos = (idx - 1) / block;                 // 固定位的位置，0 ~ n-1
    long long inBlock = (idx - 1) % block + 1;         // 块内编号
    long long i = (inBlock - 1) / half + 1;            // 上半部分编号
    long long j = (inBlock - 1) % half + 1;            // 下半部分编号
    char bit = start[pos];
    char invBit = (bit == '0' ? '1' : '0');
    string rest = start.substr(0, pos) + start.substr(pos + 1);
    vector<string> upper = solve(n - 1, rest, i);
    string lastRest = upper.back();
    vector<string> lower = solve(n - 1, lastRest, j);
    for (auto& s : upper) res.push_back(insertChar(s, pos, bit));
    for (auto& s : lower) res.push_back(insertChar(s, pos, invBit));
    return res;
}

int main() {
    G[1] = 1;
    for (int i = 2; i <= 6; ++i) G[i] = i * G[i - 1] * G[i - 1];
    int N;
    cin >> N;
    bool first = true;
    while (N--) {
        string start;
        long long idx;
        cin >> start >> idx;
        int n = (int)start.size();
        vector<string> ans = solve(n, start, idx);
        if (!first) cout << '\n';
        first = false;
        for (auto& s : ans) cout << s << '\n';
    }
    return 0;
}
