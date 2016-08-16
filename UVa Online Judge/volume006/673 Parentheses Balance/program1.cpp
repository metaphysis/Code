// Parentheses Balance
// UVa ID: 673
// Verdict: Accepted
// Submission Date: 2016-08-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    int n = stoi(line);

    char bank[200];

    for (int i = 1; i <= n; i++)
    {
        getline(cin, line);
        
        bool error = false;
        int top = 0;
        for (int j = 0; j < line.length(); j++)
            if (line[j] == '(' || line[j] == '[')
                bank[top++] = line[j];
            else if (line[j] == ')')
            {
                if (top > 0 && bank[top - 1] == '(')
                    top--;
                else
                {
                    error = true;
                    break;
                }
            }
            else if (line[j] == ']')
            {
                if (top > 0 && bank[top - 1] == '[')
                    top--;
                else
                {
                    error = true;
                    break;
                }
            }
        
        if (top > 0)
            error = true;
            
        cout << (error ? "No\n" : "Yes\n");
    }
    
	return 0;
}
