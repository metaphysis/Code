// Kindergarten Counting Game
// UVa ID: 494
// Verdict: Accepted
// Submission Date: 2017-12-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    string pattern = R"([a-zA-Z]+)";
    regex e(pattern, regex_constants::icase);

    string line;
    while (getline(cin, line))
    {
        regex_iterator<string::iterator> it(line.begin(), line.end(), e);
        regex_iterator<string::iterator> end;
        int count = 0;
        while (it != end)
        {
            count++;
            it++;
        }
        cout << count << '\n';
    }

    return 0;
}
