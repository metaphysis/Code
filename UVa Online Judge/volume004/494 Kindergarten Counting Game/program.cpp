// Kindergarten Counting Game
// UVa IDs: 494
// Verdict: Accepted
// Submission Date: 2016-07-12
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        int start = 0, counter = 0;
        while (start < line.length())
        {
            if (isalpha(line[start]))
            {
                counter++;
                while (start < line.length() && isalpha(line[start]))
                    start++;
                continue;
            }
            
            start++;
        }
        cout << counter << endl;
    }
    
	return 0;
}
