// Delta-wave
// UVa ID: 10022
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
    while (T--)
    {
        int M, N;
        cin >> M >> N;
        if (M > N) swap(M, N);
        pair<int, int> c1 = getCoordinate(M), c2 = getCoordinate(N);
        int r = abs(c1.first - c2.first) + abs(c1.second - c2.second);
        r += (M % 2) != (c1.first % 2);
        r += (N % 2) == (c2.first % 2);
        cout << r << '\n';
        if (T) cout << '\n';
    }
    
    return 0;
}
