// A Flea on a Chessboard
// UVa ID: 10620
// Verdict: Accepted
// Submission Date: 2016-08-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int S, x, y, dx, dy;
    while (cin >> S >> x >> y >> dx >> dy)
    {
        if (S == 0) break;
        
        int step = 0;
        while (true)
        {
            if ((x / S + y / S) % 2 == 1 && (x % S > 0) && (y % S > 0))
            {
                cout << "After " << step << " jumps the flea lands at (" << x << ", " << y << ").\n";
                break;
            }
            
            step++, x += dx, y += dy;
            
            if (step >= 2 * S)
            {
                cout << "The flea cannot escape from black squares.\n";
                break;
            }
        }
    }
    
	return 0;
}
