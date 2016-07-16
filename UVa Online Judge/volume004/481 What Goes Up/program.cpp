// What Goes Up
// UVa ID: 481
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

vector<int> numbers, parent;

int lis()
{
    fill(parent.begin(), parent.end(), -1);
    
    vector<int> m;
    m.push_back(numbers.front());
    
    for (int i = 1; i < numbers.size(); i++)
        if (numbers[i] > m.back())
            m.push_back(numbers[i]);
        else
        {
            int n = upper_bound(m.begin(), m.end(), numbers[i]) - m.begin();
            m[n] = numbers[i];
        }
    
    return m.size();
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int number;
    while (cin >> number) numbers.push_back(number);
    
    cout << lis() << '\n';
    cout << '-' << '\n'; 
        
	return 0;
}
