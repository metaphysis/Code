// Search the Khoj
// UVa ID: 13026
// Verdict: Accepted
// Submission Date: 2021-12-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Case " << cs << ":\n";
        int n;
        cin >> n;
        string list, number;
        for (int i = 0; i < n; i++)
        {
            cin >> number;
            list += number;
        }
        cin >> number;
        for (int i = 0; i < list.length(); i += number.length())
        {
            int diff = 0;
            for (int j = 0; j < number.length() && diff <= 1; j++)
                if (list[i + j] != number[j])
                    diff++;
            if (diff <= 1) cout << list.substr(i, number.length()) << '\n';
        }
    }

    return 0;
}
