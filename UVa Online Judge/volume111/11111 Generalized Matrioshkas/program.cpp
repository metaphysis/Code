// Generalized Matrioshkas
// UVa ID: 11111
// Verdict: Accepted
// Submission Date: 2018-04-06
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);

        int n, flag = 1;
        stack<int> toys, sizes;
        while (iss >> n)
        {
            if (n < 0)
            {
                toys.push(abs(n));
                sizes.push(abs(n));
            }
            else
            {
                if (toys.empty())
                {
                    flag = 0;
                    break;
                }
                if (n != toys.top())
                {
                    flag = 0;
                    break;
                }
                if (sizes.top() <= 0)
                {
                    flag = 0;
                    break;
                }
                toys.pop(); sizes.pop();
                if (!toys.empty())
                {
                    sizes.top() -= n;
                }
            }
        }

        if (toys.size() > 0) flag = 0;

        if (flag) cout << ":-) Matrioshka!\n";
        else cout << ":-( Try again.\n";
    }

    return 0;
}
