// A Mid-Summer Night's Dream
// UVa ID: 10057
// Verdict: Accepted
// Submission Date: 2018-01-12
// UVa Run Time: 0.120s
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

    int n, numbers[1000010];
    
    while (cin >> n)
    {
        for (int i = 0; i < n; i++) cin >> numbers[i];

        sort(numbers, numbers + n);

        if (n & 1)
        {
            int middle = numbers[n / 2];
            int cnt = count(numbers, numbers + n, middle);
            int total = 1;
            cout << middle << ' ' << cnt << ' ' << total << '\n';
        }
        else
        {
            int left = numbers[n / 2 - 1], right = numbers[n / 2];
            int cnt = 0;
            for (int i = 0; i < n; i++)
            {
                if (numbers[i] < left) continue;
                if (numbers[i] > right) break;
                cnt++;
            }
            int total = right - left + 1;
            cout << left << ' ' << cnt << ' ' << total << '\n';
        }
    }

    return 0;
}
