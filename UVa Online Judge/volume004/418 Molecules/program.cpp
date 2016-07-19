// Molecules
// UVa ID: 418
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
vector<string> molecules;
vector<int> indexer(4);
int intersection[4][4][2];

void findIntersection(int i, int j)
{
    
}

int findMaxVacant()
{
    
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line), line.front() != 'Q')
    {
        molecules.clear();
        molecules.push_back(line);
        for (int i = 1; i <= 3; i++)
        {
            getline(cin, line);
            molecules.push_back(line);
        }
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 2; k++)
                    intersection[i][j][k] = -1;
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                if (i == j)
                    continue;
                    
                findIntersection();
            }
        
        iota(indexer.begin(), indexer.end(), 0);
        int max_counter = 0;
        do
        {
            int counter = findMaxVacant(indexer);
            max_counter = max(max_counter, counter);
        } while (next_permutation(indexer.begin(), indexer.end()));
        
        cout << max_counter << '\n';
    }
    
	return 0;
}
