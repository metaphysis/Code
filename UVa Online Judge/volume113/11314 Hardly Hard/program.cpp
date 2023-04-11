// Hardly Hard
// UVa ID: 11314
// Verdict: Accepted
// Submission Date: 2023-04-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    cout << fixed << setprecision(3);
    double ax, ay, bx, by;
    for (int cs = 1; cs <= T; cs++) {
        cin >> ax >> ay >> bx >> by;
        cout << hypot(ax - bx, ay - by) + hypot(ax + bx, ay + by) << '\n';
    }
    return 0;
}
