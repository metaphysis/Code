// Permutations
// UVa ID: 941
// Verdict: Accepted
// Submission Date: 2017-03-06
// UVa Run Time: 0.280s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long int factor[21] = {1};
    
long long int getPermutations(string S)
{
    long long int T = factor[S.length()];

    int t = 0, c = 0;
    for (int i = 0; i < S.length(); i++)
    {
        if (c == S[i])
        {
            t++;
            continue;
        }
        if (t > 0) T /= factor[t];
        t = 1;
        c = S[i];
    }
    if (t > 0) T /= factor[t];

    return T;
}

void dfs(string S, long long int N)
{
    if (S.length() == 1)
    {
        cout << S;
        return;
    }

    long long int P = getPermutations(S.substr(1));

    if (N > P)
    {
        for (int j = 1; j < S.length(); j++)
            if (S[j] > S[0])
            {
                swap(S[0], S[j]);
                break;
            }    

        dfs(S, N - P);
    }
    else
    {
        cout << S[0];
        
        if (N == P)
        {
            for (int j = S.length() - 1; j > 0; j--)
                cout << S[j];
        }
        else
        {
            dfs(S.substr(1), N);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int C;
    long long int N;
    string S;

    for (int i = 1; i <= 20; i++) factor[i] = factor[i - 1] * i;

    cin >> C;
    for (int cases = 1; cases <= C; cases++)
    {
        cin >> S >> N;

        sort(S.begin(), S.end());
        long long int T = getPermutations(S);
        N %= T;
        N++;

        dfs(S, N);

        cout << '\n';
    }
    
    return 0;
}
