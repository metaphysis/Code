// Event Planning
// UVa ID: 11559
// Verdict: Accepted
// Submission Date: 2017-12-20
// UVa Run Time: 0.000s
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, B, H, W, p, a, c;
    
    while (cin >> N >> B >> H >> W)
    {
        int C = -1;
        for (int i = 0; i < H; i++)
        {
            cin >> p;
            for (int j = 0; j < W; j++)
            {
                cin >> a;
                if (a >= N)
                {
                    c = N * p;
                    if (c <= B && (C == -1 || c < C))
                        C = c;
                }
            }
        }
            
        if (C == -1) cout << "stay home\n";
        else cout << C << '\n';
    }

    return 0;
}
