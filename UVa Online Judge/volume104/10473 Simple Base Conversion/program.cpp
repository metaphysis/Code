// Simple Base Conversion
// UVa ID: 10473
// Verdict: Accepted
// Submission Date: 2018-03-02
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

    string line;
    while (getline(cin, line), line.front() != '-')
    {
        long long n = stoll(line, 0, 0);
        if (line[1] == 'x')
        {
            cout << dec << n << '\n';
        }
        else
        {
            cout << "0x" << hex << uppercase << n << '\n';
        }
    }

    return 0;
}
