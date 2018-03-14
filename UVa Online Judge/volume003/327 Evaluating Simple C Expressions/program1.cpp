// Evaluating Simple C Expressions
// UVa ID: 327
// Verdict: Accepted
// Submission Date: 2016-07-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    char readed[1024];

    string line;
    while (getline(cin, line))
    {
        int variable[26] = { }, used[26] = { }, position = 0;

        int value = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ' || line[i] == '\t')
                continue;
            if (line[i] == '+' || line[i] == '-' || isalpha(line[i]))
            {
                readed[position++] = line[i];
                if (position >= 3 && isalpha(readed[position - 3]))
                {
                    if ((readed[position - 1] == '+' && readed[position - 2] == '+') ||
                        (readed[position - 1] == '-' && readed[position - 2] == '-'))
                    {
                        int sign = 1, letter = readed[position - 3] - 'a';
                        if (position >= 4 && readed[position - 4] == '-')
                            sign = -1;
                        value += (letter + 1) * sign;
                        used[letter] = 1;
                        variable[letter] = letter + (readed[position - 1] == '+' ? 2 : 0);
                        position -= (position >= 4 ? 4 : 3);
                    }
                }
                else if (position >= 3 && isalpha(readed[position - 1]))
                {

                    if ((readed[position - 2] == '+' && readed[position - 3] == '+') ||
                        (readed[position - 2] == '-' && readed[position - 3] == '-'))
                    {
                        int sign = 1, letter = readed[position - 1] - 'a';
                        if (position >= 4 && readed[position - 4] == '-')
                            sign = -1;
                        value += (letter + (readed[position - 2] == '+' ? 2 : 0)) * sign;
                        used[letter] = 1;
                        variable[letter] = letter + (readed[position - 2] == '+' ? 2 : 0);
                        position -= (position >= 4 ? 4 : 3);
                    }
                }
            }
        }

        for (int i = 0; i < position; i++)
            if (isalpha(readed[i]))
            {
                used[readed[i] - 'a'] = 1;
                variable[readed[i] - 'a'] = readed[i] - 'a' + 1;
                int sign = 1;
                if (i > 0 && readed[i - 1] == '-')
                    sign = -1;
                value += sign * variable[readed[i] - 'a'];
            }

        cout << "Expression: " << line << "\n";
        cout << "    value = " << value << "\n";
        for (int i = 0; i < 26; i++)
            if (used[i])
                cout << "    " << (char)('a' + i) << " = " << variable[i] << "\n";
    }

    return 0;
}
