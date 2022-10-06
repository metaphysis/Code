// Add Again
// UVa ID: 11076
// Verdict: Accepted
// Submission Date: 2022-10-06
// UVa Run Time: 0.020s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long getP(vector<int> S, int idx)
{
    S.erase(S.begin() + idx);
    long long n = 1;
    for (int i = 2; i <= S.size(); i++) n *= i;
    int d = 1;
    for (int i = 1, j = 0; i < S.size(); i++)
    {
        if (S[i] == S[j]) n /= ++d;
        else d = 1, j = i;
    }
    return n;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N;
    while (cin >> N, N)
    {
        vector<int> S;
        for (int i = 0, d; i < N; i++)
        {
            cin >> d;
            S.push_back(d);
        }
        sort(S.begin(), S.end());
        long long p = S[0] * getP(S, 0);
        for (int i = 1, j = 0; i < N; i++)
        {
            if (S[i] == S[j]) continue;
            p += S[i] * getP(S, i);
            j = i;
        }
        long long r = 0;
        for (int i = 0; i < N; i++) r = r * 10 + 1;
        cout << p * r << '\n';
    }

    return 0;
}
