// Rating Hazard
// UVa ID: 1256
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include<bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string s;
    int cases = 1;
    while (cin >> s) {
        if (s.front() == '-') break;
        cout << "Case " << cases++ << ": ";
        int p = (int)(s.find('.'));
        long long n = stoll(s.substr(p + 1)) * 10;
        long long ln = n - 5, hn = n + 5;
        long long c = pow(10, s.substr(p + 1).length() + 1);
        long long lb = 1;
        while (true) {
            int flag = 0;
            long long lx = 0, hx = lb - 1, mx;
            while (lx <= hx) {
                mx = (lx + hx) >> 1;
                if (ln * lb <= c * mx && c * mx < hn * lb) { flag = 1; break; }
                if (c * mx < ln * lb) lx = mx + 1;
                if (c * mx >= hn * lb) hx = mx - 1;
            }
            if (flag) break;
            lb++;
        }
        cout << lb << '\n';
    }
}
