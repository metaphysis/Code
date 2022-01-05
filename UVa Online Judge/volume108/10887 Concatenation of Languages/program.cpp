// Concatenation of Languages
// UVa ID: 10887
// Verdict: Accepted
// Submission Date: 2022-01-05
// UVa Run Time: 0.470s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, M, N, C = 1;
    string W1[1510], W2[1510];
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> M >> N;
        cin.ignore(256, '\n');
        for (int i = 0; i < M; i++) getline(cin, W1[i]);
        for (int i = 0; i < N; i++) getline(cin, W2[i]);
        set<string> W;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                W.insert(W1[i] + W2[j]);
        cout << "Case " << C++ << ": " << W.size() << '\n';
    }
    return 0;
}
