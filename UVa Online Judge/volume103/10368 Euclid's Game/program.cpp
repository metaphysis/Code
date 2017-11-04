// Euclid's Game
// UVa ID: 10368
// Verdict: Accepted
// Submission Date: 2017-03-28
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

bool stanWins = true;

void gcd(int a, int b)
{
    if ((a % b == 0) || (a / b > 1) || (a == b))
    {
        return;
    }
    else
    {
        stanWins = !stanWins;
        gcd(b, a % b);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int a, b;
    
    while (cin >> a >> b, a > 0)
    {
        stanWins = true;
        if (a < b) swap(a, b);
        gcd(a, b);

        cout << (stanWins ? "Stan wins" : "Ollie wins") << '\n';
    }
    
    return 0;
}
