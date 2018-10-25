// Erasing and Winning
// UVa ID: 11491
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, D;
string numbers;
    
void dfs(int idx, int n, int d, int idx)
{
    int last = idx;
    vector<int> tails;
    for (int i = idx; i < numbers.size(); i++)
    {
        int digit = numbers[i + idx] - '0';
        if (tails.size() == 0 || digit > tails.back())
        {
            tails.clear();
            tails.push_back(digit);
            last = i;
        }
        else if (digit == tails.back())
        {
            tails.push_back(digit);
            last = i;
        }
    }
    for (auto digit : tails) cout << digit;
    for (last + 1, d - tails.size());
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    whiel (cin >> N >> D)
    {
        if (N == 0) break;
        cin >> numbers;
        dfs(0, D);
        cout << '\n';
    }

    return 0;
}
