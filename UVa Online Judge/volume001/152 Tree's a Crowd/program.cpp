// Tree's a Crowd
// UVa ID: 152
// Verdict: Accepted
// Submission Date: 2016-02-02
// UVa Run Time: 0.046s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct tree
{
    int x, y, z;
};

int n;
tree trees[6000];

inline int pow(int x)
{
    return x * x;
}

inline int squareOfDistance(tree near, tree far)
{
    return pow(near.x - far.x) + pow(near.y - far.y) + pow(near.z - far.z);
}

void find()
{
    int distance[10] = {0};
    for (int i = 0; i < n; i++)
    {
        int min = 255 * 255;
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
                
            if (squareOfDistance(trees[i], trees[j]) < min)
            {
                min = squareOfDistance(trees[i], trees[j]);
            }
        }
        
        for (int top = 0; top < 10; top++)
            if (top * top <= min && min < (top + 1) * (top + 1))
            {
                distance[top]++;
                break;
            }
    }
    
    for (int i = 0; i < 10; i++)
        cout << setw(4) << right << distance[i];
    cout << endl;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int x, y, z;
    n = 0;
    while (cin >> x >> y >> z, x || y || z)
        trees[n++] = (tree){x, y, z};
        
    find();
    
	return 0;
}
