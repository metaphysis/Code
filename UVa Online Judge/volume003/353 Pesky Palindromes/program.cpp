// Pesky Palindromes
// UVa ID: 353
// Verdict: Accepted
// Submission Date: 2016-06-27
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
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    string line;
    while (cin >> line)
    {
        set<string> palindromes;
        
        for (int i = 0; i < line.length(); i++)
        {
            int left = i, right = i;
            while (left >= 0 && right < line.length() && line[left] == line[right])
            {
                palindromes.insert(line.substr(left, right - left + 1));
                left--;
                right++;
            }
            
            if (i > 0)
            {
                left = i - 1, right = i;
                while (left >= 0 && right < line.length() && line[left] == line[right])
                {
                    palindromes.insert(line.substr(left, right - left + 1));
                    left--;
                    right++;
                }
            }
        }
        
        cout << "The string '" << line << "' contains " << palindromes.size() << " palindromes." << endl;
    }
    
	return 0;
}
