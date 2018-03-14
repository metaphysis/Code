// FORCAL
// UVa ID: 309
// Verdict: Accepted
// Submission Date: 2016-11-10
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    bool error = false;

    string line;
    while (getline(cin, line))
    {
        if (line.length() == 0)
        {
            cout << '\n';
            error = false;
            continue;
        }

        if (error)
            continue;

        int position = 0;
        while (position < line.length())
        {
            if (line[position] == '(' || line[position] == ')' || line[position] == '+'
                || line[position] == ';' || line[position] == ',')
            {
                cout << line[position] << '\n';
                position++;
            }
            else if (line[position] == '-' && position + 1 < line.length()
                && line[position + 1] == '-')
            {
                break;
            }
            else if (line[position] == '-')
            {
                cout << line[position] << '\n';
                position++;
            }
            else if (line[position] == ':')
            {
                if (position + 1 < line.length() && line[position + 1] == '=')
                {
                    cout << ":=" << '\n';
                    position += 2;
                }
                else
                {
                    error = true;
                }
            }
            else if (isalpha(line[position]) || isdigit(line[position]) || line[position] == '_')
            {
                string block;
                bool all_are_digits = true;
                while (position < line.length())
                {
                    if (isalpha(line[position]) || isdigit(line[position]) || line[position] == '_')
                    {
                        block += line[position];
                        if (all_are_digits)
                            all_are_digits = isdigit(line[position]);
                    }
                    else
                    {
                        break;
                    }

                    position++;
                }

                if ((!all_are_digits && block.length() > 32) || (all_are_digits && block.length() > 8))
                {
                    error = true;
                }
                else
                {
                    cout << block << '\n';
                }
            }
            else if (!isblank(line[position]))
            {
                error = true;
            }
            else
            {
                position++;
            }

            if (error)
            {
                cout << "TOKEN ERROR\n";
                break;
            }
        }
    }

    return 0;
}
