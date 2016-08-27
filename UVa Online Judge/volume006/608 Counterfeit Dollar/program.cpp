// Counterfeit Dollar
// UVa ID: 608
// Verdict: Accepted
// Submission Date: 2016-08-27
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

    int cases = 0;
    cin >> cases;
    
    int coins[12], diff[4];
    string left[4], right[4], result[4];
    for (int c = 1; c <= cases; c++)
    {
        memset(coins, 0, sizeof(coins));
        
        for (int i = 1; i <= 3; i++)
        {
            cin >> left[i] >> right[i] >> result[i];
            if (result[i] == "even")
                diff[i] = 0;
            else if (result[i] == "up")
                diff[i] = 1;
            else
                diff[i] = -1;
        }
        
        for (int i = 0; i < 12; i++)
        {
            coins[i] = 1;
            bool valid = true;
            for (int j = 1; j <= 3; j++)
            {
                int left_balance = 0;
                for (int k = 0; k < left[j].length(); k++)
                    left_balance += coins[left[j][k] - 'A'];
                int right_balance = 0;
                for (int k = 0; k < right[j].length(); k++)
                    right_balance += coins[right[j][k] - 'A'];
                
                if ((left_balance - right_balance) != diff[j])
                {
                    valid = false;
                    break;
                }
            }
            
            if (valid)
            {
                cout << (char)('A' + i) << " is the counterfeit coin and it is ";
                cout << "heavy.\n";
                break;
            }
            
            coins[i] = -1;
            valid = true;
            for (int j = 1; j <= 3; j++)
            {
                int left_balance = 0;
                for (int k = 0; k < left[j].length(); k++)
                    left_balance += coins[left[j][k] - 'A'];
                int right_balance = 0;
                for (int k = 0; k < right[j].length(); k++)
                    right_balance += coins[right[j][k] - 'A'];

                if ((left_balance - right_balance) != diff[j])
                {
                    valid = false;
                    break;
                }
            }
            if (valid)
            {
                cout << (char)('A' + i) << " is the counterfeit coin and it is ";
                cout << "light.\n";
                break;
            }
            
            coins[i] = 0;
        }
    }
    
	return 0;
}
