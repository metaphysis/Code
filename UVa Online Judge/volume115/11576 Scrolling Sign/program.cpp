// Scrolling Sign
// UVa ID: 11576
// Verdict: Accepted
// Submission Date: 2018-03-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int k, w;
        cin >> k >> w;
        
        string last, word;
        int scrolling = 0;
        for (int i = 0; i < w; i++)
        {
            cin >> word;
            if (last.length() == 0)
                scrolling += k;
            else
            {
                for (int s = 0; s <= k; s++)
                {
                    bool same = true;
                    for (int a = s, b = 0; a < k; a++, b++)
                    {
                        if (last[a] != word[b])
                        {
                            same = false;
                            break;
                        }
                    }
                    if (same)
                    {
                        scrolling += s;
                        break;
                    }
                }
            }
            last = word;
        }
        
        cout << scrolling << '\n';
    }

    return 0;
}
