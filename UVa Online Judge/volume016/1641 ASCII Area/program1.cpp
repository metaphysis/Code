// ASCII Area
// UVa ID: 1641
// Verdict: Accepted
// Submission Date: 2021-12-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int h, w;
    char c;
    while (cin >> h >> w)
    {
        int area = 0;
        for (int i = 1; i <= h; i++)
            for (int j = 1; j <= w; j++)
            {
                cin >> c;
                if (c == '\\' || c == '/') area += 1;
                if (c == '.' && (area & 1)) area += 2;
            }
        cout << area / 2 << '\n';
    }

    return 0;
}
