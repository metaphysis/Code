// Mobile Casanova
// UVa ID: 12085
// Verdict: Accepted
// Submission Date: 2018-01-04
// UVa Run Time: 0.030s
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

void printRange(int begin, int end)
{
    if (begin == end) cout << '0' << begin << '\n';
    else
    {
        cout << '0' << begin << '-';
        string head = to_string(begin), tail = to_string(end);
        for (int i = 0; i < head.length(); i++)
        {
            if (head[i] == tail[i]) continue;
            for (int j = i; j < head.length(); j++)
                cout << tail[j];
            break;
        }
        cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ":\n";

        int begin, end, current;
        cin >> current;
        begin = end = current;
        
        for (int i = 1; i < n; i++)
        {
            cin >> current;
            if (current - end == 1) end = current;
            else 
            {
                printRange(begin, end);
                begin = end = current;
            }
        }
        printRange(begin, end);
        cout << '\n';
    }

    return 0;
}
