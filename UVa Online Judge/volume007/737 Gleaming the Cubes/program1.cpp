// Gleaming the Cubes
// UVa ID: 737
// Verdict: Accepted
// Submission Date: 2017-12-18
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct cube {
    int x1, y1, z1, x2, y2, z2;
}cubes[1010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, r;
    
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> cubes[i].x1 >> cubes[i].y1 >> cubes[i].z1 >> r;
            cubes[i].x2 = cubes[i].x1 + r;
            cubes[i].y2 = cubes[i].y1 + r;
            cubes[i].z2 = cubes[i].z1 + r;
        }
        
        int lowx = cubes[0].x1, lowy = cubes[0].y1, lowz = cubes[0].z1;
        int upx = cubes[0].x2, upy = cubes[0].y2, upz = cubes[0].z2;
        
        for (int i = 1; i < n; i++)
        {
            lowx = max(lowx, cubes[i].x1);
            lowy = max(lowy, cubes[i].y1);
            lowz = max(lowz, cubes[i].z1);
            upx = min(upx, cubes[i].x2);
            upy = min(upy, cubes[i].y2);
            upz = min(upz, cubes[i].z2);
        }
        
        if (lowx >= upx || lowy >= upy || lowz >= upz) cout << 0 << '\n';
        else cout << (upx - lowx) * (upy - lowy) * (upz - lowz) << '\n';
    }

    return 0;
}
