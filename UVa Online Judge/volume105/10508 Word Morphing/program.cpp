// Word Morphing
// UVa ID: 10508
// Verdict: Accepted
// Submission Date: 2018-03-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, L;
string start, last, intermediate;

bool cmp(string &s1, string &s2)
{
    int diff1 = 0, diff2 = 0;
    for (int i = 0; i < L; i++)
    {
        if (s1[i] != start[i]) diff1++;
        if (s2[i] != start[i]) diff2++;
    };
    return diff1 < diff2;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N >> L)
    {
        cin >> start >> last;
        vector<string> words(N);
        words[0] = start, words[1] = last;
        for (int i = 2; i < N; i++)
            cin >> words[i];
        sort(words.begin(), words.end(), cmp);
        for (auto w : words)
            cout << w << '\n';
    }

    return 0;
}
