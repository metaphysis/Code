// Disputed Claims
// UVa ID: 12843
// Verdict: Accepted
// Submission Date: 2023-04-09
// UVa Run Time: 0.090s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct triangle { int a, b, c; };

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, A;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ": ";
        vector<triangle> ts;
        cin >> A;
        A *= 2;
        int top = sqrt(A);
        for (int i = 1; i <= top; i++) {
            if (A % i == 0) {
                int j = A / i;
                int k = sqrt(1LL * i * i + 1LL * j * j);
                if (1LL * k * k == 1LL * i * i + 1LL * j * j) ts.push_back(triangle{i, j, k});
            }
        }
        cout << ts.size() << '\n';
        for (auto t : ts) cout << '(' << t.a << ',' << t.b << ',' << t.c << ')' << '\n';
    }
    return 0;
}
