// Modern Art
// UVa ID: 432
// Verdict: Accepted
// Submission Date: 2016-08-05
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, p, q, x, y;;
    cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        cin >> p >> q >> x >> y;

        vector<pair<int, int>> Tpq;
        Tpq.push_back(make_pair(x, 0));
        Tpq.push_back(make_pair(x / 2, y / 2));
        Tpq.push_back(make_pair(x + x / 2, y / 2));
        Tpq.push_back(make_pair(x, 0));
        
        for (int j = 2; j <= 10; j++)
        {
            int xx = Tpq[0].first, yy = Tpq[1].second;
    
            Tpq.insert(Tpq.begin(), make_pair(xx / 2, 0));
            Tpq.insert(Tpq.begin(), make_pair(3 * xx / 4, yy / 2));
            Tpq.insert(Tpq.begin(), make_pair(xx / 4, yy / 2));
            Tpq.insert(Tpq.begin(), make_pair(xx / 2, 0));
            
            Tpq.push_back(make_pair(2 * x - xx / 2, 0));
            Tpq.push_back(make_pair(2 * x - 3 * xx / 4, yy / 2));
            Tpq.push_back(make_pair(2 * x - xx / 4, yy / 2));
            Tpq.push_back(make_pair(2 * x - xx / 2, 0));
        }
        
        for (int i = 1; i <= 4 * (10 - p); i++)
            Tpq.erase(Tpq.begin());
            
        for (int i = 1; i <= 4 * (10 - q) && Tpq.size() > 0; i++)
            Tpq.erase(Tpq.end() - 1);

        Tpq.insert(Tpq.begin(), make_pair(0, 0));
        Tpq.insert(Tpq.begin(), make_pair(x, y));
        Tpq.push_back(make_pair(2 * x, 0));
        Tpq.push_back(make_pair(x, y));
        
        for (int i = 0; i < Tpq.size() - 1; i++)
        {
            cout << '(' << Tpq[i].first << ',' << Tpq[i].second << ')';
            cout << '(' << Tpq[i + 1].first << ',' << Tpq[i + 1].second << ')';
            cout << '\n';
        }
        cout << '\n';
    }
    
	return 0;
}
