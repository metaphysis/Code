// Super Divisible Numbers
// UVa ID: 995
// Verdict: Accepted
// Submission Date: 2017-03-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int number[60], current[60], longest[60], digits[20], counter, base, best;

bool bigmod(int k)
{
    int sum = 0;
    for (int i = 0; current[i] >= 0; i++)
    {
        sum = sum * base + current[i];
        if (sum >= k) sum %= k;
    }
    return (sum == 0);
}

void dfs(int k)
{
    for (int i = 0; i < counter; i++)
    {
        if (k == 0 && digits[i] == 0) continue;

        current[k] = digits[i];
        if (bigmod(k + 1))
        {
            number[k] = digits[i];
            if ((k + 1) > best)
            {
                copy(number, number + 60, longest);
                best = k + 1;
            }
            
            dfs(k + 1);
            number[k] = -1;
        }
        current[k] = -1;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    string list;

    while (cin >> base >> list)
    {
        counter = 0;
        for (int i = 0; i < list.length(); i++)
            digits[counter++] = list[i] - '0';
        sort(digits, digits + counter, greater<int>());
        counter = unique(digits, digits + counter) - digits;
        
        memset(number, -1, sizeof(number));
        memset(current, -1, sizeof(current));
        best = 0;
        
        dfs(0);
        
        for (int i = 0; longest[i] >= 0; i++)
            cout << longest[i];
        cout << '\n';
    }
    
    return 0;
}
