// 498-Bis
// UVa ID: 10268
// Verdict: Accepted
// Submission Date: 2018-03-01
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long x, ai, t, result;
    vector<long long> an;
    string line;
    while (cin >> x)
    {
        cin.ignore(1024, '\n');
        getline(cin, line);
        istringstream iss(line);
        an.clear();
        while (iss >> ai) an.push_back(ai);
        reverse(an.begin(), an.end());

        result = 0, t = 1;
        for (int i = 1; i < an.size(); i++)
        {
            result += an[i] * i * t;
            t *= x;
        }
        cout << result << '\n';
    }

    return 0;
}
