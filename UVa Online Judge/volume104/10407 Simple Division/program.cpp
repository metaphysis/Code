// Simple Division
// UVa ID: 10407
// Verdict: Accepted
// Submission Date: 2017-03-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    vector<int> ns;

    while (cin >> n, n != 0) {
        ns.push_back(n);
        while (cin >> n, n != 0) ns.push_back(n);

        sort(ns.begin(), ns.end());
        ns.erase(unique(ns.begin(), ns.end()), ns.end());

        if (ns.size() == 1) cout << abs(ns.front()) << '\n';
        else {
            int g = ns[1] - ns[0];
            for (int i = 2; i < ns.size(); i++)
                g = __gcd(g, ns[i] - ns[i - 1]); 
            cout << g << '\n';
        }
        ns.clear();
    }

    return 0;
}
