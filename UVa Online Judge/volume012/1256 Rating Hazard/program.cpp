// Rating Hazard
// UVa ID: 1256
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
bool verify(double r, string s) {
    stringstream ss;
    string n;
    ss << fixed << setprecision(s.length() - 2) << r + 1e-9;
    ss >> n;
    return n == s;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string s;
    int cases = 1;
    while (cin >> s) {
        if (s.front() == '-') break;
        cout << "Case " << cases++ << ": ";
        int m = 1;
        double r = stod(s);
        while (true) {
            double rr = r * m;
            double fr = floor(rr), cr = ceil(rr);
            if (verify(fr / m, s)) { cout << m << '\n'; break; }
            if (verify(cr / m, s)) { cout << m << '\n'; break; }
            m++;
        }
    }
    return 0;
}
