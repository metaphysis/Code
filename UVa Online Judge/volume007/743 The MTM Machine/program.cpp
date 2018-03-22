// The MTM Machine
// UVa ID: 743
// Verdict: Accepted
// Submission Date: 2018-03-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const string empty;

string parse(string number)
{
    if (number.front() == '2')
    {
        if (number.length() > 1)
            return number.substr(1);
        else
            return empty;
    }
    else if (number.front() == '3')
    {
        if (number.length() == 1) return empty;
        string next = parse(number.substr(1));
        if (next == empty) return empty;
        return next + "2" + next;
    }
    else return empty;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        if (line == "0") break;
        if (count(line.begin(), line.end(), '0') > 0)
        {
            cout << "NOT ACCEPTABLE\n";
            continue;
        }

        string result = parse(line);
        if (result != empty) cout << result << '\n';
        else cout << "NOT ACCEPTABLE\n";
    }

    return 0;
}
