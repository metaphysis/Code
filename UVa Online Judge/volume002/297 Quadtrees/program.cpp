// Quadtrees
// UVa ID: 297
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char image[32][32];

void parse(string &tree, int &index, int x, int y, int width)
{
    if (index < tree.length() && tree[index] == 'p')
    {
        parse(tree, ++index, x, y + width / 2, width / 2);
        parse(tree, ++index, x, y, width / 2);
        parse(tree, ++index, x + width / 2, y, width / 2);
        parse(tree, ++index, x + width / 2, y + width / 2, width / 2);
    }
    else if (index < tree.length() && tree[index] == 'e')
    {
        for (int i = x; i < x + width; i++)
            for (int j = y; j < y + width; j++)
                if (image[i][j] == '0' || image[i][j] == 'w')
                    image[i][j] = 'w';
    }
    else if (index < tree.length() && tree[index] == 'f')
    {
        for (int i = x; i < x + width; i++)
            for (int j = y; j < y + width; j++)
                    image[i][j] = 'b';
    }
}

int count()
{
    int counter = 0;
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++)
            if (image[i][j] == 'b')
                counter++;
    return counter;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int n;
    cin >> n;
    
    string first, second;
    while (n--)
    {
        for (int i = 0; i < 32; i++)
            for (int j = 0; j < 32; j++)
                image[i][j] = '0';
                
        cin >> first >> second;

        int index = 0;
        parse(first, index, 0, 0, 32);

        index = 0;
        parse(second, index, 0, 0, 32);
        
        cout << "There are " << count() << " black pixels.\n";
    }
    
	return 0;
}
