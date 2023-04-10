// Gift From the Gods
// UVa ID: 12802
// Verdict: Accepted
// Submission Date: 2023-04-10
// UVa Run Time: 0.2330s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int pp[210], cnt = 0;
    for (int i = 2; i <= 1000000; i++) {
        int flag = 1;
        int top = sqrt(i);
        for (int j = 2; flag && j <= top; j++)
            if (i % j == 0)
                flag = 0;
        if (flag) {
            string s1 = to_string(i);
            string s2 = s1;
            reverse(s2.begin(), s2.end());
            if (s1 == s2) pp[cnt++] = i;
        }
    }
    int n;
    while (cin >> n) {
        cout << 2 * n << '\n';
        if (binary_search(pp, pp + cnt, n)) break;
    }
    return 0;
}
