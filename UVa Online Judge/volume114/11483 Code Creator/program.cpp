// Code Creator
// UVa ID: 11483
// Verdict: Accepted
// Submission Date: 2018-03-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    string line;
    
    while (getline(cin, line))
    {
        n = stoi(line);
        if (n == 0) break;
        cout << "Case " << ++cases << ":\n";
        cout << "#include<string.h>\n";
        cout << "#include<stdio.h>\n";
        cout << "int main()\n";
        cout << "{\n";
        for (int i = 0; i < n; i++)
        {
            getline(cin, line);
            cout << "printf(\"";
            for (auto c : line)
            {
                if (c == '\"') cout << "\\\"";
                else if (c == '\\') cout << "\\\\";
                else cout << c;
            }
            cout << "\\n\");\n";
        }
        cout << "printf(\"\\n\");\n";
        cout << "return 0;\n";
        cout << "}\n";
    }

    return 0;
}
