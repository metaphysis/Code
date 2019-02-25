// Mobile SMS
// UVa ID: 12896
// Verdict: Accepted
// Submission Date: 2019-02-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string keypad[] = {
        " ", ".,?\"", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    int cases;
    int L, numbers[110], press;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> L;
        for (int i = 0; i < L; i++) cin >> numbers[i];
        for (int i = 0; i < L; i++)
        {
            cin >> press;
            int s = keypad[numbers[i]].length();
            cout << keypad[numbers[i]][(press - 1) % s];
        }
        cout << '\n';
    }

    return 0;
}
