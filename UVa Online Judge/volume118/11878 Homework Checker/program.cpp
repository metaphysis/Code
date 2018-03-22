// Homework Checker
// UVa ID: 11878
// Verdict: Accepted
// Submission Date: 2018-03-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int correct = 0;
    string line;
    while (getline(cin, line))
    {
        int a = 0, b = 0, c = 0, sign = 1;
        int idx = 0;
        while (idx < line.length())
        {
            if (line[idx] == '+' || line[idx] == '-')
            {
                if (line[idx] == '-') sign = -1;
                idx++;
                break;
            }
            
            if (isdigit(line[idx]))
                a = a * 10 + line[idx] - '0';
            idx++;
        }
        
        while (idx < line.length())
        {
            if (line[idx] == '=')
            {
                idx++;
                break;
            }
            
            if (isdigit(line[idx]))
                b = b * 10 + line[idx] - '0';
            idx++;
        }
        
        bool no = false;
        while (idx < line.length())
        {
            if (line[idx] == '?')
            {
                no = true;
                break;
            }
            
            if (isdigit(line[idx]))
                c = c * 10 + line[idx] - '0';
            idx++;
        }
        
        if (!no)
        {
            correct += (a + sign * b == c);
        }
    }
    cout << correct << '\n';

    return 0;
}
