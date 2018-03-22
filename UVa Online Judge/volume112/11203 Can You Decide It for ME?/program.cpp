// Can You Decide It for ME?
// UVa ID: 11203
// Verdict: Accepted
// Submission Date: 2018-03-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool validate(string &line)
{
    int length = line.length();
    if (length < 6) return false;
    if (count(line.begin(), line.end(), 'M') != 1) return false;
    if (count(line.begin(), line.end(), 'E') != 1) return false;
    if (count(line.begin(), line.end(), '?') != (length - 2)) return false;
    int mi = line.find('M'), ei = line.find('E');
    if (ei < mi) return false;
    int cnt1 = mi, cnt2 = ei - mi - 1, cnt3 = (length - 1) - ei;
    if (cnt1 < 1 || cnt2 < 1 || cnt3 < 2) return false;
    if (cnt3 <= cnt2) return false;
    return cnt1 == (cnt3 - cnt2);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string line;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> line;
        if (validate(line)) cout << "theorem\n";
        else cout << "no-theorem\n";
    }

    return 0;
}
