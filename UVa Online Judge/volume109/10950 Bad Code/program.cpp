// Bad Code
// UVa ID: 10950
// Verdict: Accepted
// Submission Date: 2017-11-14
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct element
{
    char c;
    string code;
    
    bool operator<(element &e) const
    {
        return c < e.c;
    }
} elements[128];

int n, used[128], cnt, finished;
string encrypted;

void dfs(int depth, int idx, int normal)
{
    if (finished) return;
    
    if (idx >= encrypted.length())
    {
        if (!normal) return;
        cnt++;
        for (int i = 0; i < depth; i++)
            cout << elements[used[i]].c;
        cout << '\n';
        if (cnt == 100) finished = 1;
        return;
    }
    
    bool matched = false;
    for (int i = 0; i < n; i++)
    {
        if (elements[i].code == encrypted.substr(idx, 1))
        {
            used[depth] = i;
            dfs(depth + 1, idx + 1, 1);
            matched = true;
        }
        
        if (idx + 1 < encrypted.length())
        {
            if (elements[i].code == encrypted.substr(idx, 2))
            {
                used[depth] = i;
                dfs(depth + 1, idx + 2, 1);
                matched = true;
            }
        }
    }
    
    if (!matched && encrypted[idx] == '0') dfs(depth, idx + 1, 0);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            cin >> elements[i].c >> elements[i].code;
  
        sort(elements, elements + n);
        
        cin >> encrypted;
        
        cout << "Case #" << ++cases << '\n';
        
        memset(used, 0, sizeof(used));
        cnt = finished = 0;
        dfs(0, 0, 1);
        cout << '\n';
    }
    
    return 0;
}
