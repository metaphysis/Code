// Mischievous Children
// UVa ID: 10338
// Verdict: Accepted
// Submission Date: 2018-03-08
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long fact[21];
    fact[0] = 1;
    for (long long i = 1; i <= 20; i++)
        fact[i] = fact[i - 1] * i;

    int cases, cnt[26];
    string word;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> word;
        long long r = fact[word.length()];
        memset(cnt, 0, sizeof(cnt));
        for (auto letter : word)
            cnt[letter - 'A']++;
        for (int i = 0; i < 26; i++)
            if (cnt[i] > 1)
                r /= fact[cnt[i]];
        cout << "Data set " << c << ": " << r << '\n';
    }

    return 0;
}
