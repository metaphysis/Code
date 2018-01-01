// Musical Loop
// UVa ID: 11496
// Verdict: Accepted
// Submission Date: 2018-01-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

    int N, H[10010];
    
    while (cin >> N, N > 0)
    {
        for (int i = 0; i < N; i++) cin >> H[i];
        int peaks = 0;
        for (int i = 0; i < N; i++)
        {
            int pre = (i - 1 + N) % N, next = (i + 1) % N;
            if (H[pre] < H[i] && H[i] > H[next]) peaks++;
            if (H[pre] > H[i] && H[i] < H[next]) peaks++;
        }
        cout << peaks << '\n';
    }
    
    return 0;
}
