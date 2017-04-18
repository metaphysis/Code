// Parallelepiped walk
// UVa ID: 503
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

bool debug = true;
int xx1, yy1, zz1, xx2, yy2, zz2;
int dist = 100000000;

void copy(int x1, int y1, int z1, int x2, int y2, int z2)
{
    xx1 = x1, yy1 = y1, zz1 = z1, xx2 = x2, yy2 = y2, zz2 = z2;
}

void swap()
{
    swap(xx1, xx2), swap(yy1, yy2), swap(zz1, zz2);
}

int curve(int L, int W, int H, int x1, int y1, int z1, int x2, int y2, int z2)
{
    // top plane, back plane
    if (z1 == H && x2 == 0)
    {
        dist = min(dist, (y1 - y2) * (y1 - y2) + (H + x1 - z2) * (H + x1 - z2));
        if (debug) cout << "1 = " << dist << '\n';
        dist = min(dist, (x1 + y2) * (x1 + y2) + (H + y1 - z2) * (H + y1 - z2));
        if (debug) cout << "2 = " << dist << '\n';
        dist = min(dist, (x1 + (W - y2)) * (x1 + (W - y2)) + (H + (W - y1) - z2) * (H + (W - y1) - z2));
        if (debug) cout << "3 = " << dist << '\n';
    }
    
    // top plane, bottom plane
    if (z1 == H && z2 == 0)
    {
        dist = min(dist, (x1 - x2) * (x1 - x2) + (W + H + (W - y1) - y2) * (W + H + (W - y1) - y2));
        dist = min(dist, (x1 - x2) * (x1 - x2) + (-(H + y1) - y2) * (-(H + y1) - y2));
        dist = min(dist, (L + H + (L - x1) - x2) * (L + H + (L - x1) - x2) + (y1 - y2) * (y1 - y2));
        dist = min(dist, (-(H + x1) - x2) * (-(H + x1) - x2) + (y1 - y2) * (y1 - y2));
    }
    
    return dist;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int L, W, H;
    int x1, y1, z1, x2, y2, z2;
    
    while (cin >> L >> W >> H >> x1 >> y1 >> z1 >> x2 >> y2 >> z2)
    {
        dist = 100000000;
        
        if (L == 0 || W == 0 || H == 0 ||
            (x1 == x2 && (x1 == L || x1 == 0)) ||
            (y1 == y2 && (y1 == W || y1 == 0)) ||
            (z1 == z2 && (z1 == H || z1 == 0)))
        {
            dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);
            cout << dist << '\n';
            continue;
        }
        
        // top plane, left plane
        if ((z1 == H && y2 == 0) || (y1 == 0 && z2 == H))
        {
            if (debug) cout << "top plane, left plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (y1 == 0) swap();
            dist = min(dist, curve(W, L, H, yy1, L - xx1, H, 0, L - xx2, zz2));
        }
        
        // top plane, right plane
        if ((z1 == H && y2 == W) || (y1 == W && z2 == H))
        {
            if (debug) cout << "top plane, right plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (y1 == W) swap();
            dist = min(dist, curve(W, L, H, W - yy1, xx1, H, 0, xx2, zz2));
        }
        
        // top plane, front plane
        if ((z1 == H && x2 == L) || (x1 == L && z2 == H))
        {
            if (debug) cout << "top plane, front plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (x1 == L) swap();
            dist = min(dist, curve(L, W, H, L - xx1, W - yy1, H, 0, W - yy2, zz2));
        }
        
        // top plane, back plane
        if ((z1 == H && x2 == 0) || (x1 == 0 && z2 == H))
        {
            if (debug) cout << "top plane, back plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (x1 == 0) swap();
            dist = min(dist, curve(L, W, H, xx1, yy1, H, 0, yy2, zz2));
        }
        
        // top plane, bottom plane
        if ((z1 == H && z2 == 0) || (z1 == 0 && z2 == H))
        {
            if (debug) cout << "top plane, bottom plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (z1 == 0) swap();
            dist = min(dist, curve(L, W, H, xx1, yy1, H, xx2, yy2, 0));
        }
        
        // right plane, front plane
        if ((x1 == L && y2 == W) || (y1 == W && x2 == L))
        {
            if (debug) cout << "right plane, front plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (y1 == W) swap();
            dist = min(dist, curve(W, H, L, W - yy1, H - zz1, L, 0, H - zz2, xx2));
        }
        
        // right plane, back plane
        if ((y1 == W && x2 == 0) || (x1 == 0 && y2 == W))
        {
            if (debug) cout << "right plane, back plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (x1 == 0) swap();
            dist = min(dist, curve(L, H, W, xx1, H - zz1, W, 0, H - zz2, yy2));
        }
        
        // right plane, bottom plane
        if ((y1 == W && z2 == 0) || (z1 == 0 && y2 == W))
        {
            if (debug) cout << "right plane, bottom plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (z1 == 0) swap();
            dist = min(dist, curve(H, L, W, zz1, xx1, W, 0, xx2, yy2));
        }
        
        // right plane, left plane
        if ((y1 == W && y2 == 0) || (y1 == 0 && y2 == W))
        {
            if (debug) cout << "right plane, left plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (y1 == 0) swap();
            dist = min(dist, curve(H, L, W, zz1, xx1, W, zz2, xx2, 0));
        }
        
        // front plane, left plane
        if ((x1 == L && y2 == 0) || (y1 == 0 && x2 == L))
        {
            if (debug) cout << "front plane, left plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (y1 == 0) swap();
            dist = min(dist, curve(W, H, L, yy1, zz1, L, 0, zz2, xx2));
        }
        
        // front plane, bottom plane
        if ((x1 == L && z2 == 0) || (z1 == 0 && x2 == L))
        {
            if (debug) cout << "front plane, bottom plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (z1 == 0) swap();
            dist = min(dist, curve(H, W, L, zz1, W - yy1, L, 0, W - yy2, xx2));
        }
        
        // front plane, back plane
        if ((x1 == L && x2 == 0) || (x1 == 0 && x2 == L))
        {
            if (debug) cout << "front plane, back plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (x1 == 0) swap();
            dist = min(dist, curve(W, H, L, yy1, zz1, L, yy2, zz2, 0));
        }
        
        // left plane, back plane
        if ((y1 == 0 && x2 == 0) || (x1 == 0 && y2 == 0))
        {
            if (debug) cout << "left plane, back plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (x1 == 0) swap();
            dist = min(dist, curve(L, H, W, xx1, zz1, W, 0, zz2, W - yy2));
        }
        
        // left plane, bottom plane
        if ((y1 == 0 && z2 == 0) || (z1 == 0 && y2 == 0))
        {
            if (debug) cout << "left plane, bottom plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (z1 == 0) swap();
            dist = min(dist, curve(H, L, W, zz1, L - xx1, W, 0, L - xx2, W - yy2));
        }
        
        // back plane, bottom plane
        if ((x1 == 0 && z2 == 0) || (z1 == 0 && x2 == 0))
        {
            if (debug) cout << "back plane, bottom plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (z1 == 0) swap();
            dist = min(dist, curve(H, W, L, zz1, yy1, L, 0, yy2, L - xx2));
        }
        
        cout << dist << '\n';
    }
    
    return 0;
}
