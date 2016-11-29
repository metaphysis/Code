// Network Connections
// UVa ID: 793
// Verdict: Accepted
// Submission Date: 2016-11-29
// UVa Run Time: 0.020s
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

const int MAX_N = 10010;

int parent[MAX_N], ranks[MAX_N];

void makeSet()
{
    for (int i = 0; i < MAX_N; i++)
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
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        int n;
        cin >> n;
        
        makeSet();
        
        char form_of_pair;
        int i, j, success = 0, failed = 0;
        
        while (cin >> form_of_pair)
        {
            if (form_of_pair == 'c' || form_of_pair == 'q')
            {
                cin >> i >> j;
                
                if (form_of_pair == 'c')
                {
                    if (findSet(i) != findSet(j))
                        unionSet(i, j);
                }
                else
                {
                    if (findSet(i) == findSet(j))
                        success++;
                    else
                        failed++;
                }
            }
            else
            {
                cin.putback(form_of_pair);
                break;
            }
        }
        
        cout << success << ',' << failed << '\n';
    }
    
	return 0;
}
