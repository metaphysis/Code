// Help the Leaders
// UVa ID: 10475
// Verdict: Accepted
// Submission Date: 2017-11-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<string> topics;

int t, p, s;

bool cmp(string a, string b)
{
    if (a.length() != b.length()) return a.length() > b.length();
    return a < b;
}

int restricted[256][2], used[20];

void dfs(int depth, int idx, int mask)
{
    if (depth == s)
    {
        for (int i = 0; i < p; i++)
            if ((mask & (1 << restricted[i][0])) && (mask & (1 << restricted[i][1])))
                return;
        
        bool printed = false;
        for (int i = 0; i < t; i++)
            if (mask & (1 << i))
            {
                if (printed) cout << ' ';
                cout << topics[i];
                printed = true;
            }
        cout << '\n';
        return;
    }
    
    for (int i = idx; i < t; i++)
        if (!used[i])
        {
            used[i] = 1;
            dfs(depth + 1, i + 1, mask | (1 << i));
            used[i] = 0;
        }
}

string toupper(string a)
{
    for (int i = 0; i < a.length(); i++)
        a[i] = toupper(a[i]);
    return a;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        topics.clear();

        cin >> t >> p >> s;
        
        string t1, t2;
        for (int i = 0; i < t; i++)
        {
            cin >> t1;
            topics.push_back(toupper(t1));
        }
        
        sort(topics.begin(), topics.end(), cmp);

        for (int i = 0; i < p; i++)
        {
            cin >> t1 >> t2;
            t1 = toupper(t1), t2 = toupper(t2);
            
            restricted[i][0] = find(topics.begin(), topics.end(), t1) - topics.begin();
            restricted[i][1] = find(topics.begin(), topics.end(), t2) - topics.begin();
        }
        
        cout << "Set " << c << ":\n";
        memset(used, 0, sizeof(used));
        dfs(0, 0, 0);
        cout << '\n';
    }
    
    return 0;
}
