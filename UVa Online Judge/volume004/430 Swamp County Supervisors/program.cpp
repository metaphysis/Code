// Swamp County Supervisors
// UVa ID: 430
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
    int label, members, id, power_index;
};

struct state
{
    int index, visited, members;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        vector<party> parties;
        int majority_of_total = 0, members, count_of_party = 0;

        istringstream iss(line);
        iss >> majority_of_total;

        while (iss >> members)
        {
            parties.push_back((party){count_of_party, members, 1 << count_of_party, 0});
            count_of_party++;
        }
        
        for (int j = 1; j <= count_of_party; j++)
            parties[j - 1].id = 1 << (count_of_party - j);
        
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
            cout << (j > 0 ? " " : "") << parties[j].power_index;
        cout << '\n';
    }
    
	return 0;
}
