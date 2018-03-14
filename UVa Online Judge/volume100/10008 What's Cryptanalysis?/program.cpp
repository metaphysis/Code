// What's Cryptanalysis?
// UVa ID: 10008
// Verdict: Accepted
// Submission Date: 2018-02-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct frequency
{
    char letter;
    int cnt;
    bool operator<(const frequency &f) const
    {
        if (cnt != f.cnt) return cnt > f.cnt;
        return letter < f.letter;
    }
} fs[26];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    string line;

    cin >> n;
    cin.ignore(1024, '\n');
    for (int i = 0; i < 26; i++)
    {
        fs[i].letter = 'A' + i;
        fs[i].cnt = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        getline(cin, line);
        for (auto c : line)
            if (isalpha(c))
                fs[toupper(c) - 'A'].cnt++;
    }

    sort(fs, fs + 26);
    for (int i = 0; i < 26; i++)
        if (fs[i].cnt)
            cout << fs[i].letter << ' ' << fs[i].cnt << '\n';
        else break;

    return 0;
}
