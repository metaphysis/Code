// Cantor
// UVa ID: 11701
// Verdict: Accepted
// Submission Date: 2018-01-27
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

    int a, b;
    string line;

    while (getline(cin, line))
    {
        if (line == "END") break;

        a = b = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '.')
            {
                for (int j = i + 1; j < line.length(); j++)
                    if (isdigit(line[j]))
                        b = b * 10 + line[j] - '0';
                break;
            }
            else
            {
                if (isdigit(line[i]))
                    a = a * 10 + line[i] - '0';
            }
        }

        set<int> memory;
        int r = 10, member = 1;
        
        while (b > r) r *= 10;

        while (true)
        {
            if (memory.find(b) != memory.end())
                break;
            else
                memory.insert(b);
            b *= 3;
            if (b / r == 1)
            {
                member = 0;
                break;
            }
            b %= r;
        }
        
        cout << (member ? "MEMBER" : "NON-MEMBER") << '\n';
    }

    return 0;
}
