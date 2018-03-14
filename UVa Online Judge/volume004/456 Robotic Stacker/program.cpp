// Robotic Stacker
// UVa ID: 456
// Verdict: Accepted
// Submission Date: 2017-02-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metapackageshysis # yeah dot net
//
// greedy algorithm works, why?
//

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string s;
    while (cin >> s)
    {
        int bin[6] = { }, stacked = 0, boxes = 0;
        
        for (int i = 0; i < s.length(); i++, stacked++)
        {
            int packages = s[i] - '0';
            
            // 尝试将箱子水平放置在集装箱内。
            bool horizontal = false;
            for (int j = 0; j <= 6 - packages; j++)
            {
                if (bin[j] != 20)
                {
                    bool supported = true;
                    for (int k = 1; k < packages; k++)
                        if (bin[j + k] != bin[j])
                        {
                            supported = false;
                            break;
                        }

                    if (supported)
                    {
                        for (int k = 0; k < packages; k++)
                            bin[j + k]++;
                        horizontal = true;
                        break;
                    }
                }
            }
            
            // 水平放置成功。
            if (horizontal) 
            {
                boxes += packages;
                continue;
            }
            
            // 若水平放置不成功，尝试垂直放置。
            bool vertical = false;
            for (int j = 0; j < 6; j++)
            {
                if (bin[j] + packages <= 20)
                {
                    bin[j] += packages;
                    vertical = true;
                    break;
                }
            }
            
            // 若垂直放置不成功，表明该组箱子无法放置。
            if (!vertical) break;
            
            boxes += packages;
        }
        
        cout << stacked << ' ' << (120 - boxes) << '\n';
    }
    return 0;
}
