// Train Tracks
// UVa ID: 11586
// Verdict: Accepted
// Submission Date: 2017-12-27
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

    int n;
    cin >> n;
    cin.ignore(1024, '\n');
    
    for (int i = 1; i <= n; i++)
    {
        string line;
        getline(cin, line);
        istringstream iss(line);
        string piece;
        
        int M = 0, F = 0;
        while (iss >> piece)
        {
            if (piece.front() == 'M') M++; else F++;
            if (piece.back() == 'M') M++; else F++;
        }
        if (M == F && M > 1) cout << "LOOP\n";
        else cout << "NO LOOP\n";
    }

    return 0;
}
