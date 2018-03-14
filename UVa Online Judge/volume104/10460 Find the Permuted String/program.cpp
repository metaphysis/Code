// Find the Permuted String
// UVa ID: 10460
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n;
string sequence;

string permutation(int idx, int depth)
{
    if (depth == 1) return sequence.substr(0, 1);
    
    string previous = permutation(idx / depth, depth - 1);
    int i = idx % depth;
    if (i < previous.length()) previous.insert(i, sequence.substr(depth - 1, 1));
    else previous.push_back(sequence[depth - 1]);

    return previous;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> sequence >> n;
        cout << permutation(n - 1, sequence.length()) << '\n';
    }

    return 0;
}
