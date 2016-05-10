// Calling Circles
// UVa IDs: 247
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MAXN = 10000;
int edges[25][25];
map < string, int > indexer;
map < int, string > names;
int n, m;

void floyd()
{   
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (edges[i][k] + edges[k][j] < edges[i][j])
                    edges[i][j] = edges[i][k] + edges[k][j];
}

void findAllCircles()
{
    floyd();
    
    vector < bool > outputed(n);
    fill(outputed.begin(), outputed.end(), false);
    
    for (int i = 0; i < n; i++)
    {
        if (outputed[i] == false)
        {
            vector < int > circle;
            circle.push_back(i);
            outputed[i] = true;
            
            for (int j = 0; j < n; j++)
                if (outputed[j] == false && edges[i][j] < MAXN && edges[j][i] < MAXN)
                {
                    circle.push_back(j);
                    outputed[j] = true;
                }
                
            for (int j = 0; j < circle.size(); j++)
            {
                if (j > 0)
                    cout << ", ";
                cout << names[circle[j]];
            }
            cout << "\n";
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int cases = 0;
    string first, second;
    while (cin >> n >> m, n && m)
    {
        indexer.clear();
        names.clear();
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                edges[i][j] = MAXN;
        
        for (int i = 1; i <= m; i++)
        {
            cin >> first >> second;
            
            if (indexer.count(first) == 0)
            {
                names.insert(make_pair(indexer.size(), first));
                indexer.insert(make_pair(first, indexer.size()));
            }
            
            if (indexer.count(second) == 0)
            {
                names.insert(make_pair(indexer.size(), second));
                indexer.insert(make_pair(second, indexer.size()));
            }
            
            edges[indexer[first]][indexer[second]] = 1;
        }
        
        if (cases++)
            cout << "\n";
        
        cout << "Calling circles for data set " << cases << ":\n";
    
        findAllCircles();
    }
    
	return 0;
}
