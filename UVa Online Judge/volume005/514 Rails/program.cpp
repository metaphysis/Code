// Rails
// UVa ID: 514
// Verdict: Accepted
// Submission Date: 2016-08-09
// UVa Run Time: 0.010s
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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line), line != "0")
    {
        int n = stoi(line);
        while (getline(cin, line), line != "0")
        {
            int number, current = 1;
            stack<int> rails;
            istringstream iss(line);
            
            bool yes = true;
            while (iss >> number)
            {
                if (number == current)
                {
                    current++;
                }
                else if (rails.empty() == false && number == rails.top())
                {
                    rails.pop();
                }
                else if (number > current)
                {
                    while (current < number)
                    {
                        rails.push(current);
                        current++;
                    }
                    current++;
                }
                else
                {
                    yes = false;
                    break; 
                }
            }
            
            cout << (yes ? "Yes\n" : "No\n");
        }
        cout << '\n';
    }
    
	return 0;
}
