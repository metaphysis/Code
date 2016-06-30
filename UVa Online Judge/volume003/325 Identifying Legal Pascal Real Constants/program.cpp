// Identifying Legal Pascal Real Constants
// UVa IDs: 325
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
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        if (line == "*")
            break;
        
        // remove the blank character    
        while (isblank(line.front()))
            line.erase(line.begin());
        while (isblank(line.back()))
            line.erase(line.end() - 1);
            
        if (line.find(' ') != line.npos || line.find('\t') != line.npos)
        {
            cout << line << " is illegal." << endl;
            continue;
        }
        
        if (line.find('e') == line.npos && line.find('E') == line.npos && line.find('.') == line.npos)
        {
            cout << line << " is illegal." << endl;
            continue;
        }
        
        string pattern = R"(^[\+|-]?([1-9]\\d*\.\d+([e|E](\+|-)?[1-9]\d*)?|[1-9]\d*[e|E](\+|-)?[1-9]\d*)$)";
        
        if (regex_match(line, regex(pattern, regex_constants::extended)))
            cout << line << " is legal." << endl;
        else
            cout << line << " is illegal." << endl;
    }
    
	return 0;
}
