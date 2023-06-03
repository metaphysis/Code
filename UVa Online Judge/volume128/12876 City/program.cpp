// City
// UVa ID: 12876
// Verdict: Accepted
// Submission Date: 2023-06-01
// UVa Run Time: 0.300s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        int d, even = 0, odd = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) {
                cin >> d;
                if (d >= 0) {
                    if ((i + j) & 1) even += d;
                    else odd += d;
                }
            }
        cout << abs(even - odd) << '\n';
    }
    return 0;
}
