// Persistent Numbers
// UVa ID: 10527
// Verdict: Accepted
// Submission Date: 2018-03-10
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

string divide(string &number, int i)
{
    string r;
    int carry = 0;
    for (auto d : number)
    {
        carry = carry * 10 + d - '0';
        r += (char)('0' + carry / i);
        carry %= i;
    }
    if (carry) r.clear();
    else
    {
        while (r.size() > 0 && r.front() == '0')
            r.erase(r.begin());
    }
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string number;

    while (cin >> number)
    {
        if (number == "-1") break;

        if (number.length() == 1)
        {
            cout << '1' << number << '\n';
            continue;
        }

        string best;
        while (number != "1")
        {
            bool divided = false;
            for (int i = 9; i >= 2; i--)
            {
                string r = divide(number, i);
                if (r.length() > 0)
                {
                    best += (char)('0' + i);
                    divided = true;
                    number = r;
                    break;
                }
            }
            if (!divided) break;
        }
        
        if (number == "1")
        { 
            reverse(best.begin(), best.end());
            cout << best << '\n';
        }
        else cout << "There is no such number.\n";
    }

    return 0;
}
