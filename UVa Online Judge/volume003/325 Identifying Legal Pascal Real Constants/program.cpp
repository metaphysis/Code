// Identifying Legal Pascal Real Constants
// UVa IDs: 325
// Verdict: Accepted
// Submission Date: 2016-06-30
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
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    //string pattern = "^\\s*[\\+|-]?\\d+(\\.\\d+(e[\\+|-]?\\d+)?|e[\\+|-]?\\d+)\\s*$";
    string pattern = R"(^\s*[\+|-]?\d+(\.\d+(e[\+|-]?\d+)?|e[\+|-]?\d+)\s*$)";
    regex e(pattern, regex_constants::icase);
        
    string line;
    while (getline(cin, line))
    {
        if (line == "*")
            break;

        int left = 0, right = line.length() - 1;
        while (left < line.length() && isblank(line[left])) left++;
        while (right >= 0 && isblank(line[right])) right--;
        
        for (int i = left; i <= right; i++)
            cout << line[i];
            
        if (regex_match(line, e))
            cout << " is legal." << endl;
        else
            cout << " is illegal." << endl;
    }
    
	return 0;
}
