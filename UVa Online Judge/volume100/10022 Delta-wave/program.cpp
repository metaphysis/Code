// Delta-wave
// UVa ID: 10022
// Verdict: Accepted
// Submission Date: 2022-11-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

pair<int, int> getCoordinate(int n)
{
    int row = ceil(sqrt(n));
    int cln = n - (row * row - row + 1);
    return make_pair(row, cln);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int M, N;
        cin >> M >> N;
        if (M > N) swap(M, N);
        pair<int, int> c1 = getCoordinate(M), c2 = getCoordinate(N);
        int r = 0, up = (M % 2) != (c1.first % 2);
        while (c1.first < c2.first) {
            if (up) {
                if (c1.second < c2.second) c1.second += 1;
                else c1.second -= 1;
                up = 0;
            } else {
                up = 1;
                c1.first += 1;
            }
            r += 1;
        }
        r += abs(c1.second - c2.second);
        cout << r << '\n';
        if (T) cout << '\n';
    }

    return 0;
}
