// Double Decker
// UVa ID: 13071
// Verdict: Accepted
// Submission Date: 2022-10-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int A, N, M;
    cin >> A;
    for (int cs = 1; cs <= A; cs++)
    {
        cin >> N >> M;
        cout << (1 + N + M) * (N + M) / 2 + N + 1 << '\n';
    }    
    
    return 0;
}
