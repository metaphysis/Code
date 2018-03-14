// Unique Snowflakes
// UVa ID: 11572
// Verdict: Accepted
// Submission Date: 2018-01-13
// UVa Run Time: 0.260s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int n, integer, mark = -1, maximum = 0;
        cin >> n;
        map<int, int> snowflake;
        for (int i = 0; i < n; i++)
        {
            cin >> integer;
            if (snowflake.find(integer) != snowflake.end())
                mark = max(mark, (int)snowflake[integer]);
            maximum = max(maximum, i - mark);
            snowflake[integer] = i;
        }
        cout << maximum << '\n';
    }

    return 0;
}
