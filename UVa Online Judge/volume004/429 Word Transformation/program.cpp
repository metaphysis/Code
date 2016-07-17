// Word Transformation
// UVa ID: 429
// Verdict: Accepted
// Submission Date: 2016-07-17
// UVa Run Time: 0.030s
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

const int MAX_STEPS = 1000000;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    string line;
    getline(cin, line);
    int cases = stoi(line);
    
    getline(cin, line);
    for (int m = 1; m <= cases; m++)
    {
        if (m > 1) cout << endl;

        set<string> existed;
        map<string, int> words;
        vector<string> dictionary;
        
        int n = 0;
        while (getline(cin, line), line != "*")
        {
            if (existed.find(line) == existed.end())
            {
                existed.insert(line);
                dictionary.push_back(line);
                words[line] = n++;
            }
        }
        
        vector<vector<int>> edges(n, vector<int>());
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                if (dictionary[i].length() != dictionary[j].length()) continue;
                
                int difference = 0;
                for (int k = 0; k < dictionary[i].length(); k++)
                    if (dictionary[i][k] != dictionary[j][k])
                        difference++;
                if (difference == 1)
                {
                    edges[i].push_back(j);
                    edges[j].push_back(i);
                }
            }
            
        while (getline(cin, line), line.length() > 0)
        {
            istringstream iss(line);
            string first, second;
            iss >> first >> second;
            
            int start = words[first], end = words[second];
            
            vector<bool> visited(n);
            vector<int> distances(n);
            fill(distances.begin(), distances.end(), MAX_STEPS);
            fill(visited.begin(), visited.end(), false);
            distances[start] = 0;
            
            int current = start;
            while (visited[current] == false)
            {
                visited[current] = true;
                for (int i = 0; i < edges[current].size(); i++)
                {
                    int next = edges[current][i];
                    if (visited[next] == false && distances[next] > distances[current] + 1)
                    {
                        distances[next] = distances[current] + 1;
                    }
                }
                
                int max_distances = MAX_STEPS;
                for (int i = 0; i < n; i++)
                    if (visited[i] == false && distances[i] < max_distances)
                    {
                        current = i;
                        max_distances = distances[i];
                    }
            }
            
            cout << first << ' ' << second << ' ' << distances[end] << '\n';
        }
    }
    
	return 0;
}
