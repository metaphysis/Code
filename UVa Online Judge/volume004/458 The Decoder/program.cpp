// The Decoder
// UVa ID: 458
// Verdict: Accepted
// Submission Date: 2016-07-12
// UVa Run Time: 0.010s
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    cin.unsetf(ios::skipws);
    char letter;
    while (cin >> letter)
    {
        if (letter != '\n')
            cout << (char)(letter - 7);
        else
            cout << letter;
    }
    
	return 0;
}
