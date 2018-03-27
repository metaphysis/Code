// The One-Handed Typist
// UVa ID: 10393
// Verdict: Accepted
// Submission Date: 2018-03-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const string finger[10] = {
    "qaz", "wsx", "edc", "rfvtgb", " ", " ", "yhnujm", "ik,", "ol.", "p;/"
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int F, f, N;
    while (cin >> F)
    {
        cin >> N;
        set<char> disabled;
        for (int i = 0; i < F; i++)
        {
            cin >> f;
            for (auto c : finger[f - 1])
                disabled.insert(c);
        }

        string word;
        set<string> longest;
        for (int i = 0; i < N; i++)
        {
            cin >> word;
            bool flag = true;
            for (auto c : word)
            {
                if (disabled.find(c) != disabled.end())
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                if (longest.size() == 0)
                {
                    longest.insert(word);
                }
                else
                {
                    string last = *(--longest.end());
                    if (word.length() == last.length())
                    {
                        longest.insert(word);
                    }
                    else if (word.length() > last.length())
                    {
                        longest.clear();
                        longest.insert(word);
                    }
                }
            }
        }

        cout << longest.size() << '\n';
        for (auto s : longest)
            cout << s << '\n';
    }

    return 0;
}
