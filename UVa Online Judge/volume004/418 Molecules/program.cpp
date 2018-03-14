// Molecules
// UVa ID: 418
// Verdict: Accepted
// Submission Date: 2016-07-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<string> molecules;
vector<int> indexer(4);
vector<pair<int, int>> intersection[4][4];

void findIntersection(int i, int j)
{
    for (int x = 1; x < molecules[i].size() - 1; x++)
        for (int y = 1; y < molecules[j].size() - 1; y++)
            if (molecules[i][x] == molecules[j][y])
                intersection[i][j].push_back(make_pair(x, y));
}

int findMaxVacant()
{
    int counter = 0;
    for (auto p1 : intersection[indexer[0]][indexer[1]])
    {
        for (auto p2 : intersection[indexer[0]][indexer[2]])
        {
            if (p2.first > p1.first)
            {
                for (auto p3 : intersection[indexer[1]][indexer[3]])
                {
                    if (p3.first > p1.second)
                    {
                        int width = p2.first - p1.first;
                        int height = p3.first - p1.second;
                        
                        if (p3.second + width < molecules[indexer[3]].size() - 1 &&
                            p2.second + height < molecules[indexer[2]].size() - 1 &&
                            molecules[indexer[3]][p3.second + width] == molecules[indexer[2]][p2.second + height])
                        {
                            counter = max(counter, (width - 1) * (height - 1));
                        }
                    }
                }
            }
        }
    }
    
    return counter;
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
                    intersection[i][j].clear();
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                if (i == j)
                    continue;
                    
                findIntersection(i, j);
            }
        
        iota(indexer.begin(), indexer.end(), 0);
        int max_counter = 0;
        do
        {
            int counter = findMaxVacant();
            max_counter = max(max_counter, counter);
        } while (next_permutation(indexer.begin(), indexer.end()));
        
        cout << max_counter << '\n';
    }
    
	return 0;
}
