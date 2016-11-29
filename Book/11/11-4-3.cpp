#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void lcs(string& s, string& t)
{
    if (s.length() == 0 || t.length() == 0)
        return;

    int max_length = 0, max_start = 0;
    int memo[s.length() + 1][t.length() + 1];

    memset(memo, 0, sizeof(memo));

    for (int i = 1; i <= s.length(); i++)
        for (int j = 1; j <= t.length(); j++)
        {
            if (s[i - 1] == t[j - 1])
                memo[i][j] = memo[i - 1][j - 1] + 1;
            else
                memo[i][j] = 0;
                
            if (memo[i][j] > max_length)
            {
                max_length = memo[i][j];
                max_start = i - memo[i][j];
            }
        }

    cout << s.substr(max_start, max_length) << '\n';
}

int main(int argc, char *argv[])
{
    string s, t;
    while (cin >> s >> t) lcs(s, t);

    return 0;
}
