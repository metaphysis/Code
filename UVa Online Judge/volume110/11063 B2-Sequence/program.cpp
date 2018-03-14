// B2-Sequence
// UVa ID: 11063
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, number[110], cases = 0;
    while (cin >> n)
    {
        cout << "Case #" << ++cases << ": ";

        bool flag = true;
        for (int i = 0; i < n; i++)
        {
            cin >> number[i];
            if (number[i] < 1) flag = false;
            if (i && number[i] <= number[i - 1])
                flag = false;
        }
        
        if (flag)
        {
            set<int> exist;
            for (int i = 0; i < n; i++)
                for (int j = i; j < n; j++)
                {
                    if (exist.find(number[i] + number[j]) != exist.end())
                    {
                        flag = false;
                        goto print;
                    }
                    else exist.insert(number[i] + number[j]);
                }
        }
        
        print:
        if (flag) cout << "It is a B2-Sequence.\n";
        else cout << "It is not a B2-Sequence.\n";
        cout << '\n';
    }

    return 0;
}
