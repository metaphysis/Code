// TaxicabNumbers Numbers
// UVa ID: 962
// Verdict: Accepted
// Submission Date: 2017-03-08
// UVa Run Time: 0.210s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    long long cubes[2000];
    
    for (int i = 0; i < 1010; i++) cubes[i] = i * i * i;

    unordered_map<long long, int> cabNumbers;
    
    for (int i = 1; i < 1010; i++)
        for (int j = i + 1; j < 1010; j++)
            cabNumbers[cubes[i] + cubes[j]]++;
    
    int counter = 0;
    for (auto cab : cabNumbers)
        if (cab.second >= 2)
            cubes[counter++] = cab.first;

    long long nl, rg;
    while (cin >> nl >> rg)
    {
        rg += nl;

        int printed = 0;
        for (int i = 0; i < counter; i++)
        {
            if (cubes[i] >= nl && cubes[i] <= rg)
            {
                cout << cubes[i] << '\n';
                printed++;
            }
        }
        if (printed == 0) cout << "None\n";
    }
    
    return 0;
}
