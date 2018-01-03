// Alaska
// UVa ID: 11850
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

void countingSort(int data[], int n, int C)
{
    int *bucket = new int[C]();

    for (int i = 0; i < n; i++) bucket[data[i]]++;
    
    for (int i = 0, index = 0; i < C; i++)
        while (bucket[i]-- > 0)
            data[index++] = i;

    delete [] bucket;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, station[2000];
    
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++) cin >> station[i];

        //sort(station, station + n);
        countingSort(station, n, 1500);

        bool safe = true;
        for (int i = 1; i < n; i++)
            if (station[i] - station[i - 1] > 200)
            {
                safe = false;
                break;
            }

        // Check the driver can go back or not.
        if (2 * (1422 - station[n - 1]) > 200) safe = false;

        if (safe) cout << "POSSIBLE\n";
        else cout << "IMPOSSIBLE\n";
    }

    return 0;
}
