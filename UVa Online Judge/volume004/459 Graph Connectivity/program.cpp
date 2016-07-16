// Graph Connectivity
// UVa ID: 459
// Verdict: Accepted
// Submission Date: 016-07-15
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

int parent[26], ranks[26];

void makeSet()
{
    for (int i = 0; i < 26; i++)
    {
        parent[i] = i;
        ranks[i] = 0;
    }
}

// 带路径压缩的查找，使用递归实现。
int findSet(int x)
{
    return (x == parent[x] ? x : parent[x] = findSet(parent[x]));
}

//  集合的按秩合并。
void unionSet(int x, int y)
{
    x = findSet(x);
    y = findSet(y);
    
    if (x == y)
        return;
        
    if (ranks[x] > ranks[y])
        parent[y] = x;
    else
    {
        parent[x] = y;
        if (ranks[x] == ranks[y])
            ranks[y]++;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    cin.ignore(1024, '\n');
    
    string line;
    getline(cin, line);
    
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << endl;
        
        makeSet();

        int maxIndex = 0;
        while (getline(cin, line), line.length() > 0)
        {
            if (line.length() == 1)
            {
                maxIndex = line.front() - 'A';
                continue;
            }
            for (int i = 1; i < line.length(); i++)
                unionSet(line[i] - 'A', line.front() - 'A'); 
        }
        
        int counter = 0;
        for (int i = 0; i <= maxIndex; i++)
            if (parent[i] == i)
                counter++;
        cout << counter << endl;
    }
    
	return 0;
}
