// A Node Too Far
// UVa ID: 336
// Verdict: Accepted
// Submission Date: 2016-06-26
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int distances[40][40];
    map<int, int> indexer;
    int cases = 0;
    
    int n;
    while (cin >> n, n)
    {
        for (int i = 0; i < 40; i++)
            for (int j = 0; j < 40; j++)
                distances[i][j] = 100000;
                
        indexer.clear();
        for (int i = 1; i <= n; i++)
        {
            int start, end;
            cin >> start >> end;
            
            if (indexer.find(start) == indexer.end())
                indexer[start] = indexer.size();
            if (indexer.find(end) == indexer.end())
                indexer[end] = indexer.size();
            
            distances[indexer[start]][indexer[end]] = 1;
            distances[indexer[end]][indexer[start]] = 1;
        }
        
        int N = indexer.size();
        
        for (int i = 1; i <= N; i++)
            distances[i][i] = 0;
            
        // floyd-warshall
        for (int k = 1; k <= N; k++)
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++)
                    if (distances[i][k] + distances[k][j] < distances[i][j])
                        distances[i][j] = distances[i][k] + distances[k][j];  
          
        int node, ttl;
        while (cin >> node >> ttl, node || ttl)
        {
            int counter = 0;
            for (int i = 1; i <= N; i++)
                if (distances[indexer[node]][i] > ttl)
                    counter++;
                    
            cout << "Case " << ++cases << ": ";
            cout << counter << " nodes not reachable from node ";
            cout << node << " with TTL = " << ttl << "." << endl;
        }
    }
    
	return 0;
}
