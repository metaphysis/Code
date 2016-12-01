// Fibinary Numbers
// UVa ID: 763
// Verdict: Accepted
// Submission Date: 2016-12-01
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

int cases = 0;

void adjust(string &number1)
{
    bool updated = false;
    do
    {
        updated = false;
        for (int j = number1.length() - 1; j > 0; j--)
            if (number1[j - 1] == '1' && number1[j] == '1')
            {
                int k = j - 1;
                while (number1[k] == '1' && number1[k + 1] == '1')
                {
                    number1[k] = number1[k + 1] = '0';
                    number1[k + 2] = '1';
                    k += 2;
                }
                
                updated = true;
                break;
            }
    } while (updated);
}

void add(string number1, string number2)
{
    int max_length = max(number1.length(), number2.length());
    max_length += 10;
    
    reverse(number1.begin(), number1.end());
    reverse(number2.begin(), number2.end());
    
    while (number1.length() < max_length) number1.push_back('0');
    while (number2.length() < max_length) number2.push_back('0');
    
    adjust(number1);
    adjust(number2);
    
    bool updated = false;
    do
    {
        updated = false;
        for (int i = 0; i < number2.length(); i++)
        {
            if (number2[i] == '0') continue;

            if (number1[i] == '1')
            {
                updated = true;
                if (i == 0)
                {
                    number2[i] = number1[i] = '0';
                    number1[i + 1] = '1';
                }
                else if (i == 1)
                {
                    number1[i + 1] = number1[i - 1] = '1';
                    number1[i] = number2[i] = '0';
                }
                else
                {
                    number2[i] = '0';
                    number2[i - 1] = number2[i - 2] = '1';
                }
            }
            else
            {
                updated = true;
                number1[i] = '1', number2[i] = '0';
            }
            
            if (updated)
            {
                adjust(number1);
                break;
            } 
        }

    } while (updated);
    
    while (number1.back() == '0' && number1.length() > 1)
        number1.erase(number1.end() - 1);
        
    reverse(number1.begin(), number1.end());
    
    if (cases++ > 0) cout << '\n';
    cout << number1 << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string number1, number2;
    while (cin >> number1 >> number2) add(number1, number2);
        
	return 0;
}
