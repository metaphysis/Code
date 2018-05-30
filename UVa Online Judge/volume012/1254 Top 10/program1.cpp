// Top 10
// UVa ID: 1254
// Verdict: Accepted
// Submission Date: 2018-05-30
// UVa Run Time: 0.810s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct WORD
{
    int idx;
    string word;
    bool operator<(const WORD &w) const
    {
        if (word.length() != w.word.length()) return word.length() < w.word.length();
        if (word != w.word) return word < w.word;
        return idx < w.idx;
    }
};

vector<WORD> words;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, Q;
    string w;

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> w;
        words.push_back((WORD){i, w});
    }

    sort(words.begin(), words.end());

    cin >> Q;
    for (int i = 1; i <= Q; i++)
    {
        cin >> w;
        int cnt = 0;
        for (int j = 0; j < N; j++)
        {
            if (words[j].word.find(w) != string::npos)
            {
                if (cnt) cout << ' ';
                cout << words[j].idx;
                if (++cnt >= 10) break;
            }
        }
        if (cnt == 0) cout << "-1";
        cout << '\n';
    }

    return 0;
}
