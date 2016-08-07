// Box of Bricks
// UVa ID: 591
// Verdict: Accepted
// Submission Date: 2016-08-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n, n)
    {
        vector<int> bricks(n);

        int total = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> bricks[i];
            total += bricks[i];
        }
        
        int height = total / n;
        total = 0;
        for (int i = 0; i < n; i++)
            if (bricks[i] < height)
                total += (height - bricks[i]);
                
        cout << "Set #" << ++cases << '\n';
        cout << "The minimum number of moves is " << total << ".\n\n";
    }
    
	return 0;
}
