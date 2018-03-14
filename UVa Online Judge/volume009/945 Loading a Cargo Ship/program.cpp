// Loading a Cargo Ship
// UVa ID: 945
// Verdict: Accepted
// Submission Date: 2017-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, container;
    
    while (cin >> container)
    {
        vector<vector<int>> cargo(container);
        vector<int> capacity(container);
        vector<int> usedWeight(container, 0);

        int totalCapacity = 0;
        for (int i = 0; i < container; i++)
        {
            cin >> capacity[i];
            totalCapacity += capacity[i];
        }
            
        int package, weight;
        int totalWeight = 0, cargoWeight = 0, unusedWeight = 0, unloadedWeight = 0;
        bool working = true;

        cin >> package;
        for (int i = 0; i < package; i++)
        {
            cin >> weight;
            
            totalWeight += weight;
            
            if (working)
            {
                int best = 0;
                for (int j = 1; j < container; j++)
                {
                    if (cargo[j].size() < cargo[best].size()) best = j;
                    else
                    {
                        if (cargo[j].size() == cargo[best].size())
                            if (capacity[j] > capacity[best])
                                best = j;
                    }
                }
                
                if (capacity[best] >= weight)
                {
                    cargo[best].push_back(weight);
                    capacity[best] -= weight;
                    cargoWeight += weight;
                }
                else
                {
                    unloadedWeight += weight;
                    working = false;
                }
            }
            else unloadedWeight += weight;
        }

        if (cases++ > 0) cout << '\n';
        
        int maxPackage = 0;
        for (int i = 0; i < container; i++)
            maxPackage = max(maxPackage, (int)cargo[i].size());
        
        for (int i = maxPackage - 1; i >= 0; i--)
        {
            for (int j = 0; j < container; j++)
            {
                if (j > 0) cout << ' ';
                if (i < cargo[j].size())
                    cout << cargo[j][i];
                else
                    cout << ':';
            }
            cout << '\n';
        }
        
        for (int i = 1; i <= (2 * container - 1); i++)
            cout << '=';
        cout << '\n';
        
        for (int i = 1; i <= container; i++)
        {
            if (i > 1) cout << ' ';
            cout << i;
        }
        cout << '\n';
        
        cout << '\n';
        
        cout << "cargo weight: " << cargoWeight << '\n';
        cout << "unused weight: " << (totalCapacity - cargoWeight) << '\n';
        cout << "unloaded weight: " << unloadedWeight << '\n';
    }
    
    return 0;
}
