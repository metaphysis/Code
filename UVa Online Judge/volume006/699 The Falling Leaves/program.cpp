// The Falling Leaves
// UVa ID: 699
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

map<int, int> piles;

void parse(int leaves, int position)
{
    if (leaves != -1)
        piles[position] += leaves;
        
    cin >> leaves;
    if (leaves != -1)
        parse(leaves, position - 1);
    
    cin >> leaves;
    if (leaves != -1)
        parse(leaves, position + 1);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int leaves, cases = 0;
    while (cin >> leaves, leaves != -1)
    {
        piles.clear();
        parse(leaves, 0);
        
        cout << "Case " << ++cases << ":\n";
        int length = 0;
        for (auto pile : piles)
        {
            //string number = to_string(pile.second);
            
            //int next_length = length;
            //if (next_length > 0)
            //    next_length += 1 + number.length();
            //else
            //    next_length += number.length();
            //    
            //if (next_length > 80)
            //{
            //    cout << '\n';
            //    cout << number;
            //    length = number.length();
            //}
            //else
            //{
            //    if (length > 0)
            //        cout << ' ';
            //    cout << number;
            //    length = next_length;
            //}
            if (length++ > 0)
                cout << ' ';
            cout << pile.second;
        }
        cout << "\n\n";
    }
    
	return 0;
}
