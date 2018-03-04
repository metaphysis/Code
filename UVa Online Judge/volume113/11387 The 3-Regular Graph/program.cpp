// The 3-Regular Graph
// UVa ID: 11387
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct vertex
{
    int idx, degree;
    vertex (int idx = 0, int degree = 0): idx(idx), degree(degree) {}
    bool operator<(const vertex &v) const 
    {
        if (degree != v.degree)
            return degree > v.degree;
        return idx < v.idx;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        if (n <= 2 || (n % 2 == 1)) cout << "Impossible\n";
        else
        {
            cout << 3 * n / 2 << '\n';
            vector<vertex> vertices;
            for (int i = 1; i <= n; i++)
                vertices.push_back(vertex(i, 3));
            while (vertices.size() > 0)
            {
                sort(vertices.begin(), vertices.end());
                for (int i = 0, j = 1; i < vertices.front().degree; i++, j++)
                {
                    cout << vertices.front().idx << ' ';
                    cout << vertices[j].idx << '\n';
                    vertices[j].degree--;
                }
                vertices.erase(vertices.begin());
            }
        }
    }

    return 0;
}
