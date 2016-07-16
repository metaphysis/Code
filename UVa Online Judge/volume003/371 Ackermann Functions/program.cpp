// Ackermann Functions
// UVa ID: 371
// Verdict: Accepted
// Submission Date: 2016-06-25
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

int cache[500010] = { 0 };

int counter(long long int number)
{
	if (number & 1) number += (number << 1) + 1;
	else number >>= 1;
	
	if (number == 1) return 1;
	
	if (number <= 500000)
	{
	    if (!cache[number])
		    cache[number] = counter(number);
	    return 1 + cache[number];
	}
		
	return 1 + counter(number);
}
	
int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    for (int i = 1; i <= 500000; i++)
        cache[i] = counter(i);
        
	int first, second, start, end;
	while (cin >> first >> second, first && second)
	{
		start = min(first, second);
		end = max(first, second);
		
		int result = 0, steps, maxi;
		for (int i = start; i <= end; i++)
		{
		    long long int temp = i;
		    int steps = 0;
		    
		    while (temp > 500000)
		    {
		        if (temp & 1) temp += (temp << 1) + 1;
	            else temp >>= 1;
	            steps++;
		    }
		    
		    steps += cache[temp];
		    
			if (steps  > result)
			{
				result = steps;
				maxi = i;
			}
		}

		cout << "Between " << start << " and " << end;
		cout << ", " << maxi << " generates the longest sequence of " << result << " values." << endl;
	}
	
	return 0;
}
