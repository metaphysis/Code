// Perfect Cubes
// UVa ID: 386
// Verdict: Accepted
// Submission Date: 2016-06-26
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct cube
{
    int a, b, c, d;
    bool operator<(cube x) const
    {
        if (a != x.a) return a < x.a;
        else if (b != x.b) return b < x.b;
        else if (c != x.c) return c < x.c;
        else return d < x.d;
    }
};

int main(int argc, char *argv[])
{
    vector<cube> cubes;

    for (int i = 2; i <= 200; i++)
        for (int j = i; j <= 200; j++)
            for (int k = j; k <= 200; k++)
            {
                int temp = i * i * i + j * j * j + k * k * k;
                int a = cbrt(temp);
                for (int m = -1; m <= 1; m++)
                {
                    int t = a + m;
                    if (t * t * t == temp && t <= 200)
                        cubes.push_back((cube){t, i, j, k});
                }
                
            }
    
    sort(cubes.begin(), cubes.end());
    
    for (auto group : cubes)
    {
        cout << "Cube = " << group.a << ", Triple = (";
        cout << group.b << "," << group.c << "," << group.d << ")" << endl;
    }
    
	return 0;
}
