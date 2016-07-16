// Vertex
// UVa ID: 280
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.210s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int vertices;
    vector < vector < int > > edges;
    vector < bool > visited, accessible;

    while (cin >> vertices, vertices)
    {
        edges.clear();
        edges.resize(vertices);
        
        visited.resize(vertices);
        accessible.resize(vertices);
        
        cin.ignore();
        
        string line;
        while(getline(cin, line), line != "0")
        {
            istringstream iss(line);
            int start, index;
            iss >> start;
            while (iss >> index, index)
                edges[start - 1].push_back(index - 1);
        }
        
        int numberOfVertices, vertex;
        cin >> numberOfVertices;
        
        for (int i = 1; i <= numberOfVertices; i++)
        {
            cin >> vertex;
            
            fill(visited.begin(), visited.end(), false);
            fill(accessible.begin(), accessible.end(), false);
            
            queue < int > unvisited;
            
            visited[vertex - 1] = true;
            unvisited.push(vertex - 1);
            
            while (!unvisited.empty())
            {
                int current = unvisited.front();
                unvisited.pop();

                for (int j = 0; j < edges[current].size(); j++)
                {
                    if (visited[edges[current][j]] == false)
                    {
                        visited[edges[current][j]] = true;
                        unvisited.push(edges[current][j]);
                    }
                    accessible[edges[current][j]] = true;
                }
            }
            
            int numberOfUnvisited = 0;
            string verticesText;
            for (int i = 0; i < accessible.size(); i++)
            {
                if (accessible[i] == false)
                {
                    numberOfUnvisited++;
                    verticesText.append(" " + to_string(i + 1));
                }
            }
            
            cout << numberOfUnvisited << verticesText << "\n";
        }
    }
    
	return 0;
}
