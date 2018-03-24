// Broken Keyboard
// UVa ID: 10761
// Verdict: Accepted
// Submission Date: 2018-03-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cout << "+----------+----------------+-----------------------------+\n";
    cout << "| Keyboard | # of printable | Additionally, the following |\n";
    cout << "|          |      lines     |  letter keys can be broken  |\n";
    cout << "+----------+----------------+-----------------------------+\n";

    int cases = 0;
    string broken, line;
    while (getline(cin, broken))
    {
        if (broken == "finish") break;

        int printed = 0;
        set<char> needed;
        while (getline(cin, line))
        {
            bool good = true;
            for (auto c : broken)
            {
                char cu = toupper(c), cl = tolower(c);
                if (line.find(cu) != line.npos || line.find(cl) != line.npos)
                {
                    good = false;
                    break;
                }
            }
            if (good)
            {
                printed++;
                for (auto c : line)
                    if (isalpha(c))
                        needed.insert(tolower(c));
            }
            if (line == "END") break;
        }
        
        cout << '|' << setw(6) << right << ++cases << "    |";
        cout << setw(9) << right << printed << "       | ";
        string letters;
        for (char c = 'a', C = 'A'; c <= 'z'; c++, C++)
            if (needed.find(c) == needed.end())
            {
                if (broken.find(c) == broken.npos && broken.find(C) == broken.npos)
                {
                    letters += c;
                }
            }
        cout << letters;
        for (int i = 0; i < 28 - letters.length(); i++)
            cout << ' ';
        cout << "|\n";
        cout << "+----------+----------------+-----------------------------+\n";
    }
    return 0;
}
