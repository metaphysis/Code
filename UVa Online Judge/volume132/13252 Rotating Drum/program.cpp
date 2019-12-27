// Rotating Drum
// UVa ID: 13252
// Verdict: Accepted
// Submission Date: 2019-12-27
// UVa Run Time: 0.360s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<string, int> last;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int k, n;
    while (cin >> k >> n)
    {
        if (k == 1)
        {
            for (int i = 1; i <= n; i++) cout << 'A';
            cout << '\n';
            continue;
        }
        if (n == 1)
        {
            for (int i = 0; i < k; i++) cout << (char)('A' + i);
            cout << '\n';
            continue;
        }

        last.clear();
        string s = string(n - 1, 'A');
        stack<string> path;
        path.push(s);
        vector<char> circuit;
        while (!path.empty())
        {
            int e = last[s];
            if (e < k)
            {
                last[s]++;
                path.push(s);
                s += char('A' + e);
                s.erase(s.begin());
            }
            else
            {
                circuit.push_back(s.front());
                s = path.top();
                path.pop();
            }
        }
        for (int i = (int)circuit.size() - 1; i >= 1; i--) cout << circuit[i];
        cout << '\n';
    }

    return 0;
}
