// Age Sort
// UVa ID: 11462
// Verdict: Accepted
// Submission Date: 2017-02-27
// UVa Run Time: 0.200s
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
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    int bucket[100], n, number;
    
    while (cin >> n, n)
    {
        memset(bucket, 0, sizeof(bucket));
        for (int i = 1; i <= n; i++)
        {
            cin >> number;
            bucket[number]++;
        }
        
        int start = 1;
        while (!bucket[start]) start++;
        cout << start;
        bucket[start]--;

        for (int i = start; i < 100; i++)
            while (bucket[i]-- > 0)
                cout << ' ' << i;
        cout << '\n';
    }
    
    return 0;
}
