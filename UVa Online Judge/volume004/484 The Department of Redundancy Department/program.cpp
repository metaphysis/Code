// The Department of Redundancy Department
// UVa ID: 484
// Verdict: Accepted
// Submission Date: 2016-06-17
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

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    vector<int> number;
    set<int> appeared;
    map<int, int> counter;
    
    int n;
    while (cin >> n)
    {
        if (appeared.find(n) == appeared.end())
        {
            number.push_back(n);
            appeared.insert(n);
        }
        counter[n]++;
    }
    
    for (auto i : number)
        cout << i << " " << counter[i] << endl;
        
	return 0;
}
