// Word Scramble
// UVa ID: 483
// Verdict: Accepted
// Submission Date: 2016-07-13
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
        int index  = 0;
        while (index < line.length())
        {
            if (isblank(line[index]))
                cout << line[index];
            else
            {
                string block;
                while (index < line.length() && isblank(line[index]) == false)
                {
                    block += line[index];
                    index++;
                }
                
                reverse(block.begin(), block.end());
                cout << block;
                continue;
            }
            index++;
        }
        cout << endl;
    }
    
	return 0;
}
