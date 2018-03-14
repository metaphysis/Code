// Bundling Newspapers
// UVa ID: 598
// Verdict: Accepted
// Submission Date: 2016-08-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int papers[12], used[12], name_count;
string names[12];

void backtrack(int depth, int last, int n)
{
    if (depth == n)
    {
        for (int i = 0; i < n; i++)
        {
            if (i > 0)
                cout << ", ";
            cout << names[papers[i]];
        }
        cout << '\n';
    }
    else
    {
        for (int i = last; i < name_count - (n - 1) + depth; i++)
        {
            used[i] = 1;
            papers[depth] = i;
            backtrack(depth + 1, i + 1, n);
            used[i] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    
    int M = stoi(line);
    getline(cin, line);

    for (int cases = 1; cases <= M; cases++)
    {
        if (cases > 1)
            cout << '\n';
            
        string range;
        getline(cin, range);
        
        name_count = 0;
        while (getline(cin, line), line.length() > 0)
            names[name_count++] = line;
        
        int a, b;
        if (range.front() == '*')
            a = 1, b = name_count;
        else
        {
            istringstream iss(range);
            iss >> a;
            if (!(iss >> b))
                b = a;
        }
        
        //cout << "a = " << a << " b = " << b << '\n';
        
        for (int i = a; i <= b; i++)
        {
            cout << "Size " << i << '\n';
            memset(papers, -1, sizeof(papers));
            memset(used, 0, sizeof(used));
            backtrack(0, 0, i);
            cout << '\n';
        }
    }
    
	return 0;
}
