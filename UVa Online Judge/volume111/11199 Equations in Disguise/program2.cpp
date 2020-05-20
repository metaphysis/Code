// Equations in Disguise
// UVa ID: 11199
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string exps[24];

int evaluate(string &s)
{
    vector<int> r;
    int number = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '*')
        {
            r.push_back(number);
            r.push_back(-1);
            number = 0;
        }
        else if (s[i] == '+')
        {
            r.push_back(number);
            r.push_back(-2);
            number = 0;
        }
        else
        {
            number = number * 10 + s[i] - '0';
        }
    }
    r.push_back(number);
    while (true)
    {
        bool updated = false;
        for (int i = 0; i < r.size(); i++)
            if (r[i] == -1)
            {
                r[i - 1] *= r[i + 1];
                r.erase(r.begin() + i);
                r.erase(r.begin() + i);
                updated = true;
            }
        if (!updated) break;
    }
    while (r.size() > 1)
    {
        for (int i = 0; i < r.size(); i++)
            if (r[i] == -2)
            {
                r[i - 1] += r[i + 1];
                r.erase(r.begin() + i);
                r.erase(r.begin() + i);
            }
    }
    return r.front();
}


int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ": ";
        for (int i = 0; i < n; i++) cin >> exps[i];
        // 查找可能为等号的字母。
        vector<char> equal_letter;
        for (int i = 'a'; i <= 'm'; i++)
        {
            bool flag = true;
            for (int j = 0; j < n && flag; j++)
            {
                if (exps[j].front() == i || exps[j].back() == i)
                {
                    flag = false;
                    break;
                }
                int cnt = 0;
                for (int k = 0; k < exps[j].length() && cnt < 2; k++)
                    if (exps[j][j] == i) cnt++;
                flag = cnt == 1;
            }
            if (flag) equal_letter.push_back((char)i);
        }
    }

    return 0;
}
