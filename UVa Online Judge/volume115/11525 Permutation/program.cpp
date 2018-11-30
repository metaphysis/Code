// Permutation
// UVa ID: 11525
// Verdict: Accepted
// Submission Date: 2018-11-30
// UVa Run Time: 0.500s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, K, k;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> K;
        vector<int> seq;
        for (int i = 1; i <= K; i++) seq.push_back(i);
        for (int i = 0; i < K; i++)
        {
            if (i) cout << ' ';
            cin >> k;
            cout << seq[k];
            seq.erase(seq.begin() + k);
        }
        cout << '\n';
    }

    return 0;
}
