// Bender B. Rodriguez Problem
// UVa ID: 11507
// Verdict: Accepted
// Submission Date: 2017-12-27
// UVa Run Time: 0.020s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int L;
    string decision;

    while (cin >> L, L > 0)
    {
        string direction = "+x";
        for (int i = 1; i < L; i++)
        {
            cin >> decision;

            if (decision == "No") continue;
            if (decision == "+y")
            {
                if (direction == "+x") direction = "+y";
                else if (direction == "-x") direction = "-y";
                else if (direction == "+y") direction = "-x";
                else if (direction == "-y") direction = "+x";
                else if (direction == "+z") direction = "+z";
                else if (direction == "-z") direction = "-z";
            }
            else if (decision == "-y")
            {
                if (direction == "+x") direction = "-y";
                else if (direction == "-x") direction = "+y";
                else if (direction == "+y") direction = "+x";
                else if (direction == "-y") direction = "-x";
                else if (direction == "+z") direction = "+z";
                else if (direction == "-z") direction = "-z";
            }
            else if (decision == "+z")
            {
                if (direction == "+x") direction = "+z";
                else if (direction == "-x") direction = "-z";
                else if (direction == "+y") direction = "+y";
                else if (direction == "-y") direction = "-y";
                else if (direction == "+z") direction = "-x";
                else if (direction == "-z") direction = "+x";
            }
            else if (decision == "-z")
            {
                if (direction == "+x") direction = "-z";
                else if (direction == "-x") direction = "+z";
                else if (direction == "+y") direction = "+y";
                else if (direction == "-y") direction = "-y";
                else if (direction == "+z") direction = "+x";
                else if (direction == "-z") direction = "-x";
            }
        }
        cout << direction << '\n';
    }

    return 0;
}
