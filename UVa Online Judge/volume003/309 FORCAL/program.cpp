// FORCAL
// UVa IDs: 309
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

    bool error = false;
    string line;
    while (getline(cin, line))
    {
        if (line.length() == 0)
        {
            cout << endl;
            error = false;
            continue;
        }
        
        if (error) continue;
        
        int position = 0;
        while (position < line.length())
        {
            if (line[position] == '(' || line[position] == ')' ||
                line[position] == '+' || line[position] == ';' ||
                line[position] == ',')
            {
                cout << line[position] << endl;
            }
            else if (line[position] == '-' && position + 1 < line.length() && line[position + 1] == '-')
            {
                break;
            }
            else if (line[position] == '-')
            {
                cout << line[position] << endl;
            }
            else if (line[position] == ':')
            {
                if (position + 1 < line.length() && line[position + 1] == '=')
                    cout << ":=" << endl;
                else
                {
                    cout << "TOKEN ERROR" << endl;
                    error = true;
                    break;
                }
            }
            else if (isblank(line[position]) == false)
            {
                string block, lower_block;
                while (position < line.length())
                {
                    if (isalpha(line[position]) || isdigit(line[position]) || line[position] == '_')
                    {
                        block += line[position];
                        lower_block += tolower(line[position]);
                    }
                    else
                    {
                        position--;
                        break;
                    }
                }
                if (lower_block == "begin" || lower_block == "end" ||
                    lower_block == "read" || lower_block == "write"}
                {
                }
            }
            
            position++;
        }
    }
    
	return 0;
}
