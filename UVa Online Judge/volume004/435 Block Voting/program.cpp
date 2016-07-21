// Block Voting
// UVa ID: 435
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

struct party
{
    int label, members;
    
    bool operator<(const party& another) const
    {
        if (members != another.members) return members < another.members;
        return label < another.label;
    }
};

struct state
{
    int label, visited, members;
};

vector<party> parties;
vector<int> power_label;
int count_of_party, majority_of_total = 0;

// generate all subsets which sum is less majority of total, it is not efficient
void findPowerIndex(int pre_party, int pre_visited, int pre_members)
{
    queue<state> unvisited;
    
    unvisited.push((state){0, pre_visited, 0});
    
    while (!unvisited.empty())
    {
        state current = unvisited.front();
        unvisited.pop();
        
        if (current.members < majority_of_total)
        {
            if (current.members + pre_members >= majority_of_total)
                power_label[pre_party]++;
                
            for (int binary_label = current.label; binary_label < count_of_party; binary_label++)
                if ((current.visited & (1 << (count_of_party - binary_label - 1))) == 0)
                {
                    int next_visited = current.visited | (1 << (count_of_party - binary_label - 1));
                    unvisited.push((state){binary_label + 1, next_visited, current.members + parties[binary_label].members});
                }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    for (int i = 1; i <= cases; i++)
    {
        cin >> count_of_party;

        majority_of_total = 0;
        parties.clear();
        power_label.resize(count_of_party + 1);

        int members;
        for (int j = 1; j <= count_of_party; j++)
        {
            cin >> members;
            majority_of_total += members;
            parties.push_back((party){j, members});
        }
        
        power_label.resize(count_of_party + 1);
        fill(power_label.begin(), power_label.end(), 0);
        
        sort(parties.begin(), parties.end());
        
        majority_of_total = majority_of_total / 2 + (majority_of_total % 2);
        
        for (int j = 0; j < count_of_party; j++)
            findPowerIndex(parties[j].label, 1 << (count_of_party - j - 1), parties[j].members);
        
        for (int j = 1; j <= count_of_party; j++)
            cout << "party " << j << " has power_label label " << power_label[j] << '\n';
        cout << '\n';
    }
    
	return 0;
}
