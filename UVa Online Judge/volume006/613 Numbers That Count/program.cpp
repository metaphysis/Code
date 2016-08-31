// Numbers That Count
// UVa ID: 613
// Verdict: Accepted
// Submission Date: 2016-08-31
// UVa Run Time: 0.020s
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

string getNext(string &number)
{
    map<char, int> digits;
    for (int j = 0; j < number.length(); j++)
        digits[number[j]]++;
  
    string next;
    for (auto digit : digits)
    {
        next += to_string(digit.second);
        next += digit.first;
    }

    return next;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string number;
    while (cin >> number, number != "-1")
    {
        cout << number << ' ';
        
        bool determinated = false;
        map<string, int> cache = {{number, 0}};
        
        for (int i = 1; i <= 15; i++)
        {
            string next = getNext(number);

            if (cache.find(next) == cache.end())
                cache[next] = i;
            else
            {
                determinated = true;
                int start = cache[next], loop = i - cache[next];
                if (loop > 1)
                    cout << "enters an inventory loop of length " << loop << '\n';
                else if (start == 0)
                    cout << "is self-inventorying\n";
                else
                    cout << "is self-inventorying after " << start << " steps\n";
                break;
            }
            
            number = next;
        }
        
        if (!determinated)
        {
            string next = getNext(number);
            if (number == next)
                cout << "is self-inventorying after 15 steps\n";
            else
                cout << "can not be classified after 15 iterations\n";
        }
    }
    
	return 0;
}
