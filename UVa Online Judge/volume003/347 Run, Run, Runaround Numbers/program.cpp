// Run, Run, Runaround Numbers
// UVa ID: 347
// Verdict: Accepted
// Submission Date: 2016-07-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string digits;
set < int >candidates;
vector < bool > used(10), visited(10);

void dfs(int depth, int position, int length)
{
    if (visited[position])
    {
        if (depth == length && position == 0)
            candidates.insert(stoi(digits));
    }
    else
    {
        for (int digit = 1; digit <= 9; digit++)
            if (used[digit] == false)
            {
                digits[position] = '0' + digit;
                used[digit] = true, visited[position] = true;
                dfs(depth + 1, (position + digit) % length, length);
                used[digit] = false, visited[position] = false;
            }
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n, cases = 0;
    for (int length = 2; length <= 7; length++)
    {
        digits.assign(length, '0');
        fill(visited.begin(), visited.end(), false);
        fill(used.begin(), used.end(), false);
        dfs(0, 0, length);
    }

    while (cin >> n, n)
        cout << "Case " << ++cases << ": " << (*candidates.lower_bound(n)) << endl;

    return 0;
}
