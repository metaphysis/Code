// Global Raining at Bididibus
// UVa ID: 11786
// Verdict: Accepted
// Submission Date: 2021-12-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{   
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        string line;
        cin >> line;
        int highest = 0, highestIdx = 0, height = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '/') height++;
            if (line[i] == '\\') height--;
            if (height > highest)
            {
                highest = height;
                highestIdx = i;
            }
        }
        int units = 0;
        highest = 0, height = 0;
        for (int i = 0; i <= highestIdx; i++)
        {
            if (line[i] == '/')
            {
                if (height < highest) units += 2 * (highest - height) - 1;
                height++;
            }
            else if (line[i] == '\\')
            {
                height--;
                if (height < highest) units += 2 * (highest - height) - 1;
            }
            else
            {
                if (height < highest) units += 2 * (highest - height);
            }
            if (height > highest) highest = height;
        }
        highest = 0, height = 0;
        for (int i = line.length() - 1; i > highestIdx; i--)
        {
            if (line[i] == '\\')
            {
                if (height < highest) units += 2 * (highest - height) - 1;
                height++;
            }
            else if (line[i] == '/')
            {
                height--;
                if (height < highest) units += 2 * (highest - height) - 1;
            }
            else
            {
                if (height < highest) units += 2 * (highest - height);
            }
            if (height > highest) highest = height;
        }
        cout << units / 2 << '\n';
    }

    return 0;
}
