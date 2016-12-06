// Ordering
// UVa ID: 872
// Verdict: Accepted
// Submission Date: 2016-12-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net


#include <iostream>
#include <cstring>
#include <sstream>
#include <algorithm>

using namespace std;

const int MAXN = 20;

int visited[MAXN], nChar, value[2 * MAXN], nLimit;
char output[MAXN], input[MAXN], limit[MAXN][2];
bool outputed = false;

void print()
{
    outputed = true;

    for (int i = 0; i < nChar; i++)
    {
        if (i > 0) cout << ' ';
        cout << (char)(output[i] + 'A');
    }
    cout << '\n';
}

bool is_valid()
{
    for (int i = 0; i < nLimit; i++)
        if (value[limit[i][0]] >= 0 && value[limit[i][1]] >= 0 && value[limit[i][0]] > value[limit[i][1]])
            return false;
    return true;
}

void lexicographical(int current)
{
    if (current >= 2 && !is_valid()) return;
        
    if (current == nChar)
    {
        print();
        return;
    }
        
    for (int i = 0; i < nChar; i++)
        if (!visited[i])
        {
            visited[i] = 1;
            output[current] = input[i];
            value[input[i]] = current;

            lexicographical(current + 1);

            value[input[i]] = -1;
            visited[i] = 0;
        }
}

bool cmp(char a, char b)
{
    return a < b;
}

int main(int ac, char *av[])
{
    string line;
    int cases = 0;
    
    getline(cin, line);
    cases = stoi(line);

    for (int c = 1; c <= cases; c++)
    {
        getline(cin, line);

        if (c > 1) cout << '\n';
        
        getline(cin, line);
        istringstream first(line);
        
        nChar = 0;
        while (first >> input[nChar])
        {
            input[nChar] -= 'A';
            output[nChar] = 0;
            visited[nChar] = 0;
            nChar++;
        }
        
        for (int i = 0; i < 2 * MAXN; i++)
            value[i] = -1;
            
        sort(input, input + nChar, cmp);
        
        // 读取限制。
        nLimit = 0;
        getline(cin, line);
        for (int i = 0; i < line.length(); i++)
            if (line[i] == '<')
                line[i] = ' ';

        istringstream next(line);
        while (next >> limit[nLimit][0] >> limit[nLimit][1])
        {
            limit[nLimit][0] -= 'A';
            limit[nLimit][1] -= 'A';
            nLimit++;
        }
        
        // 使用回溯生成字典序排列然后检查是否符合限制条件。
        outputed = false;
        lexicographical(0);
        
        if (!outputed) cout << "NO\n";
    }

	return 0;
}
