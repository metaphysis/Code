// L-system
// UVa ID: 310
// Verdict: Accepted
// Submission Date: 2016-11-22
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

set<string> produced;

string u, v, w, z;

bool get(string current)
{
    if (produced.find(current) != produced.end()) return false;
    
    produced.insert(current);

    string next;
    for (int i = 0; i < current.length(); i++)
        if (current[i] == 'a') next += u;
        else next += v;

    if (next.length() <= z.length()) get(next);
    else
    {
        for (int i = 0; i <= next.length() - z.length(); i++)
            get(next.substr(i, z.length()));
    }
    
    return true;
}

bool find()
{
    for (auto it = produced.begin(); it != produced.end(); it++)
        if ((*it).find(z) != string::npos)
            return true;
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> u >> v >> w >> z)
    {
        if (u.find(z) != string::npos || v.find(z) != string::npos)
            cout << "YES\n";
        else
        {
            produced.clear();
            get(w);
            cout << (find() ? "YES" : "NO") << '\n';
        }
    }
    
	return 0;
}
