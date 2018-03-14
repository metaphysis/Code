// Fitting Text into Slides
// UVa ID: 10359
// Verdict: Accepted
// Submission Date: 2017-12-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int n;
        cin >> n; cin.ignore(1024, '\n');
        vector<string> lines;
        string line;
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            lines.push_back(line);
        }
        int X, Y;
        cin >> X >> Y;
        bool fitted = false;
        for (int p = 28; p >= 8; p--)
        {
            int height = 0;
            
            for (auto l : lines)
            {
                int width = 0;
                istringstream iss(l);
                string word;
                while (iss >> word)
                {
                    int span = word.length() * p;
                    if (span > X) { height = 2 * Y; break; }
                    if (width > 0) span += p;
                    if (width + span <= X) width += span;
                    else
                    {
                        width = word.length() * p;
                        height += p;
                    }
                }
                height += p;
                if (height > Y) break;
            }
            
            if (height <= Y)
            {
                cout << p << '\n';
                fitted = true;
                break;
            }
        }
        if (!fitted) cout << "No solution\n";
    }

    return 0;
}
