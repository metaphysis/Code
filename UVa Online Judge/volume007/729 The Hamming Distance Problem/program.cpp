// The Hamming Distance Problem
// UVa ID: 729
// Verdict: Accepted
// Submission Date: 2016-11-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, N, H;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        cin >> N >> H;
        
        string hamming = string(N - H, '0') + string(H, '1');
        do
        {
            cout << hamming << '\n';
        } while (next_permutation(hamming.begin(), hamming.end()));
    }
    
	return 0;
}
