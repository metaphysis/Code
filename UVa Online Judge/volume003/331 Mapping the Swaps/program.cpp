// Mapping the Swaps
// UVa IDs: 331
// Verdict: Accepted
// Submission Date: 2016-06-29
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

vector<int> number;
int counter = 0;

void dfs()
{
    bool sorted = true;
    for (int i = 0; i < number.size() - 1; i++)
    {
        if (number[i] > number[i + 1])
        {
            sorted = false;
            swap(number[i], number[i + 1]);
            dfs();
            swap(number[i], number[i + 1]);
        }
    }
    if (sorted)
        counter++;
}

int main(int argc, char *argv[])
{
    int n, cases = 0;
    while (cin >> n, n)
    {
        number.clear();
        for (int i = 1; i <= n; i++)
        {
            int integer;
            cin >> integer;
            number.push_back(integer);
        }
        
        counter = 0;
        
        bool sorted = true;
        for (int i = 0; i < number.size() - 1; i++)
            if (number[i] > number[i + 1])
            {
                sorted = false;
                break;
            }
        
        if (!sorted)    
            dfs();
        
        cout << "There are " << counter;
        cout << " swap maps for input data set " << ++cases << "." << endl;
    }
    
	return 0;
}
