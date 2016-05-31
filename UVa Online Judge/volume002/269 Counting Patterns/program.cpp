// Counting Patterns
// UVa IDs: 269
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstring>
#include <stack>
#include <map>
#include <queue>
#include <set>

using namespace std;

vector <int> number;
set<string> memory;
int n, k;
vector<int> pattern;
vector< vector<int> > answer;

void backtrack(int depth)
{
    if (depth == n)
    {
        int sum = 0;
        for (int i = 0; i < pattern.size(); i++)
            sum += pattern[i];
            
        if (sum == 0)
        {
            cout << "(";
            for (int i = 0; i < pattern.size(); i++)
                cout << pattern[i] << ",";
            cout << ")" << endl;
        }
    }
    else
    {
        for (int i = 0; i < number.size(); i++)
        {
            pattern[depth] = number[i];
            backtrack(depth + 1);
        }
    }
}

int main(int argc, char *argv[])
{
    bool first = true;
    while (cin >> n >> k)
    {
        if (first)
            first = false;
        else
            cout << endl;
        
        number.clear();    
        for (int i = -k; i <= k; i++)
            number.push_back(i);
        
        pattern.resize(n);
        memory.clear();   
        backtrack(0);
    }
    
	return 0;
}
