// The Base-1 Number System
// UVa ID: 11398
// Verdict: Accepted
// Submission Date: 2018-03-05
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

    char flag;
    string token, number;
    while (cin >> token)
    {
        if (token == "~") break;

        if (token == "#")
        {
            int n = 0;
            for (auto d : number) n = n * 2 + d - '0';
            cout << n << '\n';
            number.clear();
            continue;
        }

        if (token == "0") flag = '1';
        else if (token == "00") flag = '0';
        else
        {
            for (int i = 0; i < token.length() - 2; i++)
                number.push_back(flag);
        }
    }

    return 0;
}
