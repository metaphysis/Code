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
<<<<<<< HEAD
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
=======
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

<<<<<<< HEAD
    int L, W, H;
    int x1, y1, z1, x2, y2, z2;
=======
    int cases = 0;
    cin >> cases;
    
    int L, W, H, x1, y1, z1, x2, y2, z2;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
    
    for (int c = 1; c <= cases; c++)
    {
<<<<<<< HEAD
        dist = 100000000;
=======
        cin >> L >> W >> H >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        
        if (debug) cout << L << ' ' << W << ' ' << H << ' ' << x1 << ' ' << y1 << ' ' << z1 << ' ' << x2 << ' ' << y2 << ' ' << z2 << '\n';
        
        int dist = 100000000;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        
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
<<<<<<< HEAD
            if (debug) cout << "top plane, left plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (y1 == 0) swap();
            dist = min(dist, curve(W, L, H, yy1, L - xx1, H, 0, L - xx2, zz2));
=======
            int zz1 = z1, zz2 = z2;
            if (z1 == H)
                zz1 = H + y1;
            else
                zz2 = H + y2;
            dist = min(dist, (x1 - x2) * (x1 - x2) + (zz1 - zz2) * (zz1 - zz2));
            
            if (debug) cout << "Top Left = " << dist << endl;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        }
        
        // top plane, right plane
        if ((z1 == H && y2 == W) || (y1 == W && z2 == H))
        {
<<<<<<< HEAD
            if (debug) cout << "top plane, right plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (y1 == W) swap();
            dist = min(dist, curve(W, L, H, W - yy1, xx1, H, 0, xx2, zz2));
=======
            int yy1 = y1, yy2 = y2;
            if (yy1 == W)
                yy1 = W + (H - z1);
            else
                yy2 = W + (H - z2);
            dist = min(dist, (x1 - x2) * (x1 - x2) + (yy1 - yy2) * (yy1 - yy2));
            
            if (debug) cout << "Top Right = " << dist << endl;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        }
        
        // top plane, front plane
        if ((z1 == H && x2 == L) || (x1 == L && z2 == H))
        {
<<<<<<< HEAD
            if (debug) cout << "top plane, front plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (x1 == L) swap();
            dist = min(dist, curve(L, W, H, L - xx1, W - yy1, H, 0, W - yy2, zz2));
=======
            int xx1 = x1, xx2 = x2;
            if (xx1 == L)
                xx1 = L + (H - z1);
            else
                xx2 = L + (H - z2);
            dist = min(dist, (xx1 - xx2) * (xx1 - xx2) + (y1 - y2) * (y1 - y2));
            
            if (debug) cout << "Top Front = " << dist << endl;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        }
        
        // top plane, back plane
        if ((z1 == H && x2 == 0) || (x1 == 0 && z2 == H))
        {
<<<<<<< HEAD
            if (debug) cout << "top plane, back plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (x1 == 0) swap();
            dist = min(dist, curve(L, W, H, xx1, yy1, H, 0, yy2, zz2));
=======
            int zz1 = z2, zz2 = z2;
            if (z1 == H)
                zz1 = H + x1;
            else
                zz2 = H + x2;
            dist = min(dist, (y1 - y2) * (y1 - y2) + (zz1 - zz2) * (zz1 - zz2));
            
            if (debug) cout << "Top Back = " << dist << endl;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        }
        
        // top plane, bottom plane
        if ((z1 == H && z2 == 0) || (z1 == 0 && z2 == H))
        {
<<<<<<< HEAD
            if (debug) cout << "top plane, bottom plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (z1 == 0) swap();
            dist = min(dist, curve(L, W, H, xx1, yy1, H, xx2, yy2, 0));
=======
            int yy1 = y1, yy2 = y2;
            if (z1 == H)
                yy1 = W + H + (W - y1);
            else
                yy2 = W + H + (W - y2);
            dist = min(dist, (x1 - x2) * (x1 - x2) + (yy1 - yy2) * (yy1 - yy2));
            
            yy1 = y1, yy2 = y2;
            if (z1 == H)
                yy1 = -(H + y1);
            else
                yy2 = -(H + y2);
            dist = min(dist, (x1 - x2) * (x1 - x2) + (yy1 - yy2) * (yy1 - yy2));
            
            int xx1 = x1, xx2 = x2;
            if (z1 == H)
                xx1 = L + H + (L - x1);
            else
                xx2 = L + H + (L - x2);
            dist = min(dist, (xx1 - xx2) * (xx1 - xx2) + (y1 - y2) * (y1 - y2));
            
            xx1 = x1, xx2 = x2;
            if (z1 == H)
                xx1 = -(H + x1);
            else
                xx2 = -(H + x2);
            dist = min(dist, (xx1 - xx2) * (xx1 - xx2) + (y1 - y2) * (y1 - y2));
            
            if (debug) cout << "Top Bottom = " << dist << endl;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        }
        
        // right plane, front plane
        if ((x1 == L && y2 == W) || (y1 == W && x2 == L))
        {
<<<<<<< HEAD
            if (debug) cout << "right plane, front plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (y1 == W) swap();
            dist = min(dist, curve(W, H, L, W - yy1, H - zz1, L, 0, H - zz2, xx2));
=======
            int yy1 = y1, yy2 = y2;
            if (y1 == W)
                yy1 = W + (L - x1);
            else
                yy2 = W + (L - x2);
            dist = min(dist, (yy1 - yy2) * (yy1 - yy2) + (z1 - z2) * (z1 - z2));
            
            if (debug) cout << "Right Front = " << dist << endl;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        }
        
        // right plane, back plane
        if ((y1 == W && x2 == 0) || (x1 == 0 && y2 == W))
        {
<<<<<<< HEAD
            if (debug) cout << "right plane, back plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (x1 == 0) swap();
            dist = min(dist, curve(L, H, W, xx1, H - zz1, W, 0, H - zz2, yy2));
=======
            int yy1 = y1, yy2 = y2;
            if (y1 == W)
                yy1 = W + x1;
            else
                yy2 = W + x2;
            dist = min(dist, (yy1 - yy2) * (yy1 - yy2) + (z1 - z2) * (z1 - z2));
            
            if (debug) cout << "Right Back = " << dist << endl;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        }
        
        // right plane, bottom plane
        if ((y1 == W && z2 == 0) || (z1 == 0 && y2 == W))
        {
<<<<<<< HEAD
            if (debug) cout << "right plane, bottom plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (z1 == 0) swap();
            dist = min(dist, curve(H, L, W, zz1, xx1, W, 0, xx2, yy2));
=======
            int yy1 = y1, yy2 = y2;
            if (y1 == W)
                yy1 = W + z1;
            else
                yy2 = W + z2;
            dist = min(dist, (x1 - x2) * (x1 - x2) + (yy1 - yy2) * (yy1 - yy2));
            
            if (debug) cout << "Right Bottom = " << dist << endl;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        }
        
        // right plane, left plane
        if ((y1 == W && y2 == 0) || (y1 == 0 && y2 == W))
        {
<<<<<<< HEAD
            if (debug) cout << "right plane, left plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (y1 == 0) swap();
            dist = min(dist, curve(H, L, W, zz1, xx1, W, zz2, xx2, 0));
=======
            int zz1 = z1, zz2 = z2;
            if (y1 == W)
                zz1 = H + W + (H - z1);
            else
                zz2 = H + W + (H - z2);
            dist = min(dist, (x1 - x2) * (x1 - x2) + (zz1 - zz2) * (zz1 - zz2));
            
            zz1 = z1, zz2 = z2;
            if (y1 == W)
                zz1 = -(W + z1);
            else 
                zz2 = -(W + z2);
                
            dist = min(dist, (x1 - x2) * (x1 - x2) + (zz1 - zz2) * (zz1 - zz2));
            
            int xx1 = x1, xx2 = x2;
            if (y1 == W)
                xx1 = L + W + (L - x1);
            else
                xx2 = L + W + (L - x2);
            dist = min(dist, (xx1 - xx2) * (xx1 - xx2) + (z1 - z2) * (z1 - z2));
            
            xx1 = x1, xx2 = x2;
            if (y1 == W)
                xx1 = -(W + x1);
            else
                xx2 = -(W + x2);
            dist = min(dist, (xx1 - xx2) * (xx1 - xx2) + (z1 - z2) * (z1 - z2));
            
            if (debug) cout << "Right Left = " << dist << endl;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        }
        
        // front plane, left plane
        if ((x1 == L && y2 == 0) || (y1 == 0 && x2 == L))
        {
<<<<<<< HEAD
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
=======
            int xx1 = x1, xx2 = x2;
            if (x1 == L)
                xx1 = L + y1;
            else
                xx2 = L + y2;
            dist = min(dist, (xx1 - xx2) * (xx1 - xx2) + (z1 - z2) * (z1 - z2));
            
            if (debug) cout << "Front Left = " << dist << endl;
        }
        
        // front plane, bottom plane
        if ((x1 == L && z2 == 0) || (x2 == L && z1 == 0))
        {
            int xx1 = x1, xx2 = x2;
            if (x1 == L)
                xx1 = L + z1;
            else
                xx2 = L + z2;
            dist = min(dist, (xx1 - xx2) * (xx1 - xx2) + (y1 - y2) * (y1 - y2));
            
            if (debug) cout << "Front Bottom = " << dist << endl;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        }
        
        // front plane, back plane
        if ((x1 == L && x2 == 0) || (x1 == 0 && x2 == L))
        {
<<<<<<< HEAD
            if (debug) cout << "front plane, back plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (x1 == 0) swap();
            dist = min(dist, curve(W, H, L, yy1, zz1, L, yy2, zz2, 0));
=======
            int zz1 = z1, zz2 = z2;
            if (x1 == L)
                zz1 = H + L + (H - z1);
            else
                zz2 = H + L + (H - z2);
            dist = min(dist, (y1 - y2) * (y1 - y2) + (zz1 - zz2) * (zz1 - zz2));
            
            zz1 = z1, zz2 = z2;
            if (x1 == L)
                zz1 = -(L + z1);
            else
                zz2 = -(L + z2);
            dist = min(dist, (y1 - y2) * (y1 - y2) + (zz1 - zz2) * (zz1 - zz2));
            
            int yy1 = y1, yy2 = y2;
            if (x1 == L)
                yy1 = W + L + (W - y1);
            else
                yy2 = W + L + (W - y2);
            dist = min(dist, (yy1 - yy2) * (yy1 - yy2) + (z1 - z2) * (z1 - z2));
            
            yy1 = y1, yy2 = y2;
            if (x1 == L)
                yy1 = -(L + y1);
            else
                yy2 = -(L + y2);
            dist = min(dist, (yy1 - yy2) * (yy1 - yy2) + (z1 - z2) * (z1 - z2));
            
            if (debug) cout << "Front Back = " << dist << endl;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        }
        
        // left plane, back plane
        if ((y1 == 0 && x2 == 0) || (x1 == 0 && y2 == 0))
        {
<<<<<<< HEAD
            if (debug) cout << "left plane, back plane" << '\n';
            copy(x1, y1, z1, x2, y2, z2);
            if (x1 == 0) swap();
            dist = min(dist, curve(L, H, W, xx1, zz1, W, 0, zz2, W - yy2));
=======
            int yy1 = y1, yy2 = y2;
            if (y1 == 0)
                yy1 = -x1;
            else
                yy2 = -x2;
            dist = min(dist, (yy1 - yy2) * (yy1 - yy2) + (z1 - z2) * (z1 - z2));
            
            if (debug) cout << "Left Back = " << dist << endl;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        }
        
        // left plane, bottom plane
        if ((y1 == 0 && z2 == 0) || (z1 == 0 && y2 == 0))
        {
<<<<<<< HEAD
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
=======
            int yy1 = y1, yy2 = y2;
            if (y1 == 0)
                yy1 = -z1;
            else
                yy2 = -z2;
            dist = min(dist, (x1 - x2) * (x1 - x2) + (yy1 - yy2) * (yy1 - yy2));
            
            if (debug) cout << "Left Bottom = " << dist << endl;  
        }
        
        // back plane, bottom plane
        if ((x1 == 0 && z2 == 0) || (x2 == 0 && z1 == 0))
        {
            int xx1 = x1, xx2 = x2;
            if (x1 == 0)
                xx1 = -z1;
            else
                xx2 = -z2;
            dist = min(dist, (xx1 - xx2) * (xx1 - xx2) + (y1 - y2) * (y1 - y2));
            
            if (debug) cout << "Back Bottom = " << dist << endl;
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
        }
        
        cout << dist << '\n';
    }
    
    return 0;
}
