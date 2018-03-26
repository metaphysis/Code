// Automatic Poetry
// UVa ID: 10361
// Verdict: Accepted
// partmission Date: 2018-03-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    size_t pos;
    string line1, line2, empty;

    cin >> cases; cin.ignore(1024, '\n');
    for (int c = 1; c <= cases; c++)
    {
        getline(cin, line1); getline(cin, line2);

        string part = line1.substr(line1.find('<'));
        while ((pos = line1.find('<')) != line1.npos) line1.replace(pos, 1, empty);
        while ((pos = line1.find('>')) != line1.npos) line1.replace(pos, 1, empty);
        cout << line1 << '\n';

        size_t l1 = part.find_first_of("<"), l2 = part.find_last_of("<");
        size_t r1 = part.find_first_of(">"), r2 = part.find_last_of(">");
        cout << line2.substr(0, line2.rfind("..."));
        cout << part.substr(l2 + 1, r2 - l2 - 1);
        cout << part.substr(r1 + 1, l2 - r1 - 1);
        cout << part.substr(l1 + 1, r1 - l1 - 1);
        cout << part.substr(r2 + 1) << '\n';
    }
    
    return 0;
}
