// Finding words
// UVa ID: 892
// Verdict: Accepted
// Submission Date: 2016-12-13
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

    bool hyphen = false;
    char input, last;
    string line, buffer;

    while (getline(cin, line), line != "#")
    {
        line += '\n';
        for (int i = 0; i < line.length(); i++)
        {
            input = line[i];
            if (!isalpha(input))
            {
                if (isblank(input))
                {
                    if (hyphen)
                    {
                        cout << buffer << '\n';
                        cout << input;
                        buffer.clear();
                        hyphen = false;
                    }
                    else
                    {
                        cout << buffer;
                        cout << input;
                        buffer.clear();
                    }
                }
                else
                {
                    if (last == '-' && input == '\n')
                    {
                        cout << '\n';
                        hyphen = true;
                    }

                    if (input == '\n' && !hyphen)
                    {
                        cout << buffer;
                        buffer.clear();
                        cout << '\n';
                    }
                }
                
                last = input;
            }
            else buffer += input;
        }
    }
    
	return 0;
}
