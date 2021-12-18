// Acronyms
// UVa ID: 13093
// Verdict: Accepted
// Submission Date: 2021-12-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        string word, a1, a2;
        while (iss >> word) a1 += word.front();
        getline(cin, line);
        iss.clear();
        iss.str(line);
        while (iss >> word) a2 += word.front();
        cout << (a1 == a2 ? "yes" : "no") << '\n';
    }

    return 0;
}
