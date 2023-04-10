// Mother's Jam Puzzle
// UVa ID: 12849
// Verdict: Accepted
// Submission Date: 2023-04-10
// UVa Run Time: 0.020s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

double get(double a[][3]) {
    return a[0][0] * a[1][1] * a[2][2] +
        a[0][1] * a[1][2] * a[2][0] +
        a[0][2] * a[1][0] * a[2][1] -
        a[2][0] * a[1][1] * a[0][2] -
        a[2][1] * a[1][2] * a[0][0] -
        a[1][0] * a[0][1] * a[2][2];
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    cout << fixed << setprecision(2);
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ':';
        double a[3][3], b[3][3], c[3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                cin >> a[i][j];
            cin >> c[i];
        }
        double D = get(a);
        for (int j = 0; j < 3; j++) {
            memcpy(b, a, sizeof a);
            for (int i = 0; i < 3; i++) b[i][j] = c[i];
            cout << ' ' << get(b) / D;
        }
        cout << '\n';
    }
    return 0;
}
