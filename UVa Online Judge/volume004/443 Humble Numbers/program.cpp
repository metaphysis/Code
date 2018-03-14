// Humble Numbers
// UVa ID: 443
// Verdict: Accepted
// Submission Date: 2016-07-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

typedef long long int bigNumber;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int factors[4] = {2, 3, 5, 7};
    set<bigNumber> uglyNumbers;
    map<int, bigNumber> humbleNumbers;
    priority_queue<bigNumber, vector<bigNumber>, greater<bigNumber>> candidates;

    candidates.push(1);

    for (int i = 1; i <= 5842; i++)
    {
        bigNumber top;
        do
        {
            top = candidates.top();
            candidates.pop();
        } while (uglyNumbers.count(top) > 0);

        humbleNumbers[i] = top;
        uglyNumbers.insert(top);
        
        for (int j = 0; j < 4; j++)
        {
            bigNumber next = top * factors[j];
            if (uglyNumbers.count(next) == 0)
                candidates.push(next);
        }
    }

    int n;
    while (cin >> n, n)
    {
        int number = humbleNumbers[n];
        if ((n % 100) >= 10 && (n % 100) <= 20) cout << "The " << n << "th";
        else 
        {
            if ((n % 10) == 1) cout << "The " << n << "st";
            else
            {
                if ((n % 10) == 2) cout << "The " << n << "nd";
                else
                {
                    if ((n % 10) == 3) cout << "The " << n << "rd";
                    else cout << "The " << n << "th";
                }
            }
        }
        
        cout << " humble number is " << humbleNumbers[n] << ".\n";
    }
    
    return 0;
}
