// AutoFish
// UVa ID: 10134
// Verdict: Accepted
// Submission Date: 2018-01-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string line;

    cin >> cases; cin.ignore(1024, '\n'); getline(cin, line);

    for (int T = 1; T <= cases; T++)
    {
        int fishes = 0, instruction = 0, fished = 0, baits = 0, cutted = 0, luck = 1;

        while (getline(cin, line), line.length() > 0)
        {
            instruction++;
            if (line.front() == 'f')
            {
                if (baits == 0) continue;
                fished++;
                if (luck || (instruction >= 7 && fished >= 3))
                {
                    luck = 0;
                    baits--;
                    fishes++;
                    fished = 0;
                    instruction = 0;
                }
            }
            else if (line.front() == 'b')
            {
                if (baits == 3) continue;
                cutted++;
                if (cutted == 2) baits++, cutted = 0;
            }
        }
        if (T > 1) cout << '\n';
        cout << fishes << '\n';
    }

    return 0;
}
