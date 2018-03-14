// Dropping Balls
// UVa ID: 679
// Verdict: Accepted
// Submission Date: 2016-08-25
// UVa Run Time: 0.090s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int position[21][525000], nodes[1050000], visited[1050000];

void buildTree(int depth, int index)
{
    if (depth <= 20)
    {
        nodes[index] = index;
        visited[index] = 0;
        buildTree(depth + 1, 2 * index);
        buildTree(depth + 1, 2 * index + 1);
    }
}

void traversal(int index, int D, int I)
{
    if (index <= 1048575)
    {
        position[D][I] = nodes[index];
        
        if (!visited[index])
        {
            visited[index] = 1;
            traversal(2 * index, D + 1, I);
        }
        else
        {
            visited[index] = 0;
            traversal(2 * index + 1, D + 1, I);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    buildTree(1, 1);
    
    for (int i = 1; i <= 524288; i++)
        traversal(1, 1, i);
    
    int cases, D, I;
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        cin >> D >> I;
        cout << position[D][I] << '\n';
    }
    
	return 0;
}
