// Request for Proposal
// UVa ID: 10141
// Verdict: Accepted
// Submission Date: 2017-12-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, p, cases = 0;
    string line;

    while (cin >> n >> p, n > 0)
    {
        cin.ignore(1024, '\n');
        for (int i = 1; i <= n; i++)
            getline(cin, line);
            
        string name, bestName;
        double price, bestPrice = 0;
        int met, bestMet = -1;

        for (int i = 0; i < p; i++)
        {
            getline(cin, name);
            cin >> price >> met;
            if (met > bestMet || (met == bestMet && price < bestPrice))
            {
                bestName = name;
                bestPrice = price;
                bestMet = met;
            }
            cin.ignore(1024, '\n');
            for (int i = 1; i <= met; i++)
                getline(cin, line);
        }
        if (cases > 0) cout << '\n';
        cout << "RFP #" << ++cases << '\n';
        cout << bestName << '\n';
    }

    return 0;
}
