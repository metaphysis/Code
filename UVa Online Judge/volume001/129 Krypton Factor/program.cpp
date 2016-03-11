// Krypton Factor
// UVa IDs: 129
// Verdict: Accepted
// Submission Date: 2015-12-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

bool isValid(string line)
{
    if (line.length() == 1)
        return true;

    for (int j = 1; j <= line.length() / 2; j++)
        for (int i = 0; i < line.length() - j; i++)
            if (line.substr(i, j) == line.substr(i + j, j))
                return false;
    
    return true;
}

void display(string line)
{
    bool newLinePrinted = false;
    for (int i = 1; i <= line.length(); i++)
    {
        cout << line[i - 1];
        if (i % 64 == 0)
        {
            cout << endl;
            newLinePrinted = true;
        }
        else if (i % 4 == 0 && i < line.length())
        {
            cout << " ";
            newLinePrinted = false;
        }
    }
    
    if (newLinePrinted == false)
        cout << endl;
        
    cout << line.length() << endl;
}

void lexicographical(int n, int L)
{
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string line = "A";
    int counter = 1, start = 0;
        
    while (counter < n)
    {
        bool found = false;
        for (int i = start; i < L; i++)
        {
            if (alpha[i] == line[line.length() - 1])
                continue;
            else if (isValid(line + alpha[i]))
            {
                found = true;
                start = 0;
                counter++;
                line += alpha[i];
                break;
            }
        }
        
        if (found == false)
        {
            start = line[line.length() - 1] - 'A' + 1;
            line.erase(line.length() - 1, 1);
        }
    }
    
    display(line);
}

int main(int ac, char *av[])
{
    int n, L;
    while (cin >> n >> L, n || L)
        lexicographical(n, L);
    
	return 0;
}
