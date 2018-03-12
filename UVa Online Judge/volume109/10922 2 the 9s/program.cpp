// 2 the 9s
// UVa ID: 10922
// Verdict: Accepted
// Submission Date: 2018-03-12
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
    while (getline(cin, line))
    {
        if (line == "0") break;
        
        cout << line << ' ';
        int sum = 0;
        for (auto c : line) sum += c - '0';
        if (sum % 9 != 0)
        {
            cout << "is not a multiple of 9.\n";
        }
        else
        {
            cout << "is a multiple of 9 and has 9-degree ";
            int degree = 1;
            while (sum != 9)
            {
                degree++;
                int nextSum = 0;
                while (sum) nextSum += sum % 10, sum /= 10;
                sum = nextSum;
            }
            cout << degree << ".\n";
        }
    }
    
    return 0;
}
