// Berry Picking
// UVa ID: 858
// Verdict: Accepted
// Submission Date: 2017-12-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
}vertices[10010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        double threshold, linex;
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> vertices[i].x >> vertices[i].y;
        cin >> threshold >> linex;
        
        int ny = 0;
        double intersection[10010];
        for (int i = 0; i < n; i++)
        {
            int j = (i + 1) % n;
            if (linex > min(vertices[i].x, vertices[j].x) && linex < max(vertices[i].x, vertices[j].x))
            {
                intersection[ny++] = vertices[i].y + (linex - vertices[i].x) * (vertices[j].y - vertices[i].y) / (vertices[j].x - vertices[i].x);
            }
        }
        sort(intersection, intersection + ny);
        double internal = 0;
        for (int i = 0; i < ny - 1; i += 2)
        {
            internal += intersection[i + 1] - intersection[i];
        }
        
        if (internal >= threshold) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
