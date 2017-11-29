// The Playboy Chimp
// UVa ID: 10611
// Verdict: Accepted
// Submission Date: 2017-11-29
// UVa Run Time: 0.010s
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

    int N, height[50010], Q, H;
    
    while (cin >> N)
    {
        for (int i = 0; i < N; i++) cin >> height[i];
        cin >> Q;
        for (int i = 0; i < Q; i++)
        {
            cin >> H;
            int a = lower_bound(height, height + N, H) - height;
            int b = upper_bound(height, height + N, H) - height;

            if (a == 0 || a == N) cout << 'X'; else cout << height[a - 1];
            cout << ' ';
            if (b == N) cout << 'X'; else cout << height[b];
            cout << '\n';
        }
    }

    return 0;
}
