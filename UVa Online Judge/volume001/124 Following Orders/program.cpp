// Following Orders
// UVa ID: 124
// Verdict: Accepted
// Submission Date: 2015-11-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>

using namespace std;

#define MAXN 20

bool visited[MAXN];
int nChar, value[2 * MAXN], nLimit;
char output[MAXN], input[MAXN], limit[MAXN][2];

void print()
{
    for (int i = 0; i < nChar; i++)
        cout << output[i];
    cout << endl;
}

bool isValid()
{
    for (int i = 0; i < nLimit; i++)
        if (value[limit[i][0] - 'a'] >= 0 &&
            value[limit[i][1] - 'a'] >= 0 &&
            value[limit[i][0] - 'a'] > value[limit[i][1] - 'a'])
            return false;
    return true;
}

void lexicographical(int current)
{
    if (current >= 2 && !isValid())
        return;
        
    if (current == nChar)
    {
        print();
        return;
    }
        
    for (int i = 0; i < nChar; i++)
        if (!visited[i])
        {
            visited[i] = true;
            output[current] = input[i];
            value[input[i] - 'a'] = current;
            lexicographical(current + 1);
            value[input[i] - 'a'] = -1;
            visited[i] = false;
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
    
    while (getline(cin, line), line.length() > 0)
    {
        // 输出间隔空行。
        if (cases > 0)
            cout << endl;
            
        // 读取字符，初始化相关变量。
        istringstream first(line);
        
        nChar = 0;
        while (first >> input[nChar])
        {
            output[nChar] = 0;
            visited[nChar] = false;
            nChar++;
        }
        
        for (int i = 0; i < 2 * MAXN; i++)
            value[i] = -1;
            
        sort(input, input + nChar, cmp);
        
        // 读取限制。
        nLimit = 0;
        getline(cin, line);
        istringstream next(line);
        while (next >> limit[nLimit][0])
            next >> limit[nLimit++][1];
        
        // 使用回溯生成字典序排列然后检查是否符合限制条件。
        lexicographical(0);
        
        cases++;
    }
    
	return 0;
}
