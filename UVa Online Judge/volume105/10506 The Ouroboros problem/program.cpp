// The Ouroboros problem
// UVa ID: 10506
// Verdict: Accepted
// Submission Date: 2017-08-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int m, n;
map<string, int> edges;

void dfs(string u)
{
    if (edges.find(u) != edges.end()) return;
    edges.insert(make_pair(u, 0));
 
    for (int i = 0; i < n; i++)
        dfs(u.substr(1) + (char)('0' + i));
}

void hierholzer()
{
    stack<string> path;
    vector<string> circuit;

    string u = string(m - 1, '0');
    path.push(u);

    while (!path.empty())
    {
	    if (edges[u] < n)
        {
        	path.push(u);
	        string v = u.substr(1) + (char)('0' + edges[u]);
	        edges[u]++;
	        u = v;
        }
	    else
	    {
		    circuit.push_back(u);
		    u = path.top();
		    path.pop();
	    }
    }

    string sequence = circuit.back();
    for (int i = circuit.size() - 2; i >= 0; i--)
	    sequence += circuit[i].back();
	cout << sequence.substr(0, pow(n, m)) << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> m >> n)
    {
        if (n == 1)
        {
            cout << "0\n";
            continue;
        }
        
        if (m == 1)
        {
            for (int i = 0; i < n; i++) cout << i;
            cout << '\n';
            continue;
        }
        
        edges.clear();
        dfs(string(m - 1, '0'));
        hierholzer();
    }
    
    return 0;
}
