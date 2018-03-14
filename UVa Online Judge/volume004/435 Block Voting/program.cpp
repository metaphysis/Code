// Block Voting
// UVa ID: 435
// Verdict: Accepted
// Submission Date: 2016-07-22
// UVa Run Time: 0.120s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct party
{
    int label, members, id, power_index;
};

struct state
{
    int index, visited, members;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    for (int i = 1; i <= cases; i++)
    {
        vector<party> parties;
        int count_of_party, majority_of_total = 0;

        cin >> count_of_party;

        int members;
        for (int j = 1; j <= count_of_party; j++)
        {
            cin >> members;
            majority_of_total += members;
            parties.push_back((party){j, members, 1 << (count_of_party - j), 0});
        }
            
        majority_of_total = majority_of_total / 2 + (majority_of_total % 2);

        // generate all subsets which sum less than majority of total
        queue<state> unvisited;
        unvisited.push((state){0, 0, 0});
        while (!unvisited.empty())
        {
            state current = unvisited.front();
            unvisited.pop();
            
            if (current.members < majority_of_total)
            {
                for (int j = 0; j < count_of_party; j++)
                    if ((current.visited & parties[j].id) == 0 && current.members + parties[j].members >= majority_of_total)
                        parties[j].power_index++;
                    
                for (int binary_index = current.index; binary_index < count_of_party; binary_index++)
                    if ((current.visited & (1 << (count_of_party - binary_index - 1))) == 0)
                    {
                        int next_visited = current.visited | (1 << (count_of_party - binary_index - 1));
                        unvisited.push((state){binary_index + 1, next_visited, current.members + parties[binary_index].members});
                    }
            }
        }
        
        for (int j = 0; j < count_of_party; j++)
            cout << "party " << (j + 1) << " has power index " << parties[j].power_index << '\n';
        cout << '\n';
    }
    
	return 0;
}
