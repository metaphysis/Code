// Sum It Up
// UVa ID: 574
// Verdict: Accepted
// Submission Date: 2016-08-17
// UVa Run Time: 0.040s
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

int number[12], visited[12], t, n, counter;
string text[12];
set<string> solutions;

void backtrack(int depth, int sum)
{
    if (sum == t)
    {
        string sequence;
        bool first_number = true;
        for (int i = 0; i < n; i++)
        {
            if (visited[i])
            {
                if (first_number)
                    first_number = false;
                else
                    sequence += '+';
                sequence += text[i];
            }
        }
        
        if (solutions.find(sequence) == solutions.end())
        {
            cout << sequence << '\n';
            solutions.insert(sequence);
        }
    }
    else
    {
        for (int i = depth; i < n; i++)
        {
            if (!visited[i] && sum + number[i] <= t)
            {
                visited[i] = 1;
                backtrack(depth + 1, sum + number[i]);
                visited[i] = 0;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> t >> n, t)
    {
        for (int i = 1; i <= n; i++)
        {
            cin >> number[i - 1];
            text[i - 1] = to_string(number[i - 1]);
        }
        
        cout << "Sums of " << t << ":\n";
        
        solutions.clear();
        memset(visited, 0, sizeof(visited));
        backtrack(0, 0);
        
        if (solutions.size() == 0)
            cout << "NONE\n";
    }
    
	return 0;
}
