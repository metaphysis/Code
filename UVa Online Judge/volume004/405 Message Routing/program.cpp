// Message Routing
// UVa ID: 405
// Verdict: Accepted
// Submission Date: 2016-08-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct entry
{
    string mta, country, admd, prmd, o;
};

map<string, vector<entry>> tables;

void routing(entry r)
{
    set<string> routed;
    
    while (true)
    {
        bool mta_found = false;
        for (auto t : tables[r.mta])
        {
            bool matched = t.country == r.country || t.country == "*";
            matched = matched && (t.admd == r.admd || t.admd == "*");
            matched = matched && (t.prmd == r.prmd || t.prmd == "*");
            matched = matched && (t.o == r.o || t.o == "*");
            
            if (matched)
            {
                mta_found = true;
                if (routed.find(t.mta) != routed.end())
                {
                    cout << "circular routing detected by " << t.mta << '\n';
                    return;
                }
                else if (t.mta == r.mta)
                {
                    cout << "delivered to " << r.mta << '\n';
                    return;
                }
                else
                {
                    routed.insert(r.mta);
                    r.mta = t.mta;
                }
                break;
            }
        }
        
        if (mta_found == false)
        {
            cout << "unable to route at " << r.mta << '\n';
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int M, I, N, cases = 0;
    string mta, next_mta, country, admd, prmd, o;
    
    while (cin >> M)
    {
        tables.clear();
        for (int i = 1; i <= M; i++)
        {
            cin >> mta >> I;
            for (int j = 1; j <= I; j++)
            {
                cin >> next_mta >> country >> admd >> prmd >> o;
                tables[mta].push_back((entry){next_mta, country, admd, prmd, o});
            }
        }
        
        cout << "Scenario # " << ++cases << '\n';

        cin >> N;
        for (int i = 1; i <= N; i++)
        {
            cin >> next_mta >> country >> admd >> prmd >> o;
            cout << i << " -- ";
            
            routing((entry){next_mta, country, admd, prmd, o});
        }

        cout << '\n';
    }
    
	return 0;
}
