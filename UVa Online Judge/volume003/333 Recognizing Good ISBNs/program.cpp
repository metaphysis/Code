// Recongnizing Good ISBNs
// UVa IDs: 333
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.050s
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
    ios::sync_with_stdio(false);
    
    string line;
    while (getline(cin, line))
    {
        int term = 0, sum = 0;
        bool correct = true;
        int counter = 0, indexer = 0, digitIndex = -1, xIndex = -1;
        
        for (auto c : line)
        {
            indexer++;
            
            if (isdigit(c))
            {
                counter++;
                digitIndex = indexer;
                term += c - '0';
                sum += term;
            }
            else if (c == 'X')
            {
                counter++;
                if (xIndex == -1)
                    xIndex = indexer;
                else
                {
                    correct = false;
                    break;
                }
                
                term += 10;
                sum += term;
            }
            
            if (counter > 10)
                break;
        }
        
        if (counter != 10 || (xIndex > 0 && xIndex < digitIndex))
            correct = false;
        
        int left = 0, right = line.length() - 1;
        while (left < line.length() && isblank(line[left])) left++;
        while (right >= 0 && isblank(line[right])) right--;
        
        for (int i = left; i <= right; i++)
            cout << line[i];

        if (!correct) cout << " is incorrect.\n";
        else if (sum % 11 == 0) cout << " is correct.\n";
        else cout << " is incorrect.\n";
    }
    
	return 0;
}
