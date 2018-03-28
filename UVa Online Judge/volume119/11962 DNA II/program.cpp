// DNA II
// UVa ID: 11962
// Verdict: Accepted
// Submission Date: 2018-03-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long permutation[32] = {1};
    for (int i = 1; i <= 30; i++)
        permutation[i] = 4 * permutation[i - 1];
    map<char, int> multiply = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};

    int cases;
    string dna;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> dna;
        cout << "Case " << c << ": (" << dna.length() << ':';
        long long idx = 0;
        for (int i = 1; i <= dna.length(); i++)
        {
            int rightPart = dna.length() - i;
            if (rightPart)
                idx += multiply[dna[i - 1]] * permutation[rightPart];
            else
                idx += multiply[dna[i - 1]] + 1;
        }
        cout << (idx - 1) << ")\n";
    }

    return 0;
}
