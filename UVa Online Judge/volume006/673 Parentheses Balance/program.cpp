// Parentheses Balance
// UVa ID: 673
// Verdict: Accepted
// Submission Date: 2016-08-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    int n = stoi(line);

    for (int i = 1; i <= n; i++)
    {
        getline(cin, line);
        
        bool error = false;
        stack<char> bank;
        for (int j = 0; j < line.length(); j++)
            if (line[j] == '(' || line[j] == '[')
                bank.push(line[j]);
            else if (line[j] == ')')
            {
                if (bank.empty() || bank.top() != '(')
                {
                    error = true;
                    break;
                }
                else
                    bank.pop();
            }
            else if (line[j] == ']')
            {
                if (bank.empty() || bank.top() != '[')
                {
                    error = true;
                    break;
                }
                else
                    bank.pop();
            }
        
        if (bank.size() > 0)
            error = true;
            
        cout << (error ? "No\n" : "Yes\n");
    }
    
	return 0;
}
