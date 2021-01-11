// Box
// UVa ID: 1587
// Verdict: Accepted
// Submission Date: 2020-11-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct rectangle
{
    int shortEdge, longEdge;
    bool operator<(const rectangle &r) const
    {
        if (shortEdge != r.shortEdge) return shortEdge < r.shortEdge;
        return longEdge < r.longEdge;
    }
} rect[6];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int shortEdge, longEdge;
    while (cin >> shortEdge >> longEdge)
    {
        if (shortEdge > longEdge) swap(shortEdge, longEdge);
        rect[0].shortEdge = shortEdge;
        rect[0].longEdge = longEdge;
        
        for (int i = 1; i < 6; i++)
        {
            cin >> shortEdge >> longEdge;
            if (shortEdge > longEdge) swap(shortEdge, longEdge);
            rect[i].shortEdge = shortEdge;
            rect[i].longEdge = longEdge;
        }
        
        // 排序，短边在前，长边在后
        sort(rect, rect + 6);
        
        // 一定要有三对面
        bool flag = true;
        for (int i = 0; i < 6; i += 2)
        if (rect[i].shortEdge != rect[i + 1].shortEdge || rect[i].longEdge != rect[i + 1].longEdge)
        {
            flag = false;
            break;
        }
        if (!flag)
        {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        
        // 检查后续两对面的长边是否相等，如果不同，不可能与第一对面适配
        if (rect[2].longEdge != rect[4].longEdge)
        {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        // 检查后续两对面的短边是否和第一对面的相应边适配
        if (rect[0].shortEdge != rect[2].shortEdge || rect[0].longEdge != rect[4].shortEdge)
        {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        cout << "POSSIBLE\n";
    }

    return 0;
}
