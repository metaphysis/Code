// Roman Roulette
// UVa IDs: 130
// Verdict: Accepted
// Submission Date: 2015-12-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char *argv[])
{
    int n, k;
    while (cin >> n >> k, n || k)
    {
        vector < int > victim;
        for (int i = 1; i <= n; i++)
            victim.push_back(i);

        int killed = (k - 1) % victim.size(), burier;
        while (victim.size() > 1)
        {
            burier = (killed - 1 + k) % (victim.size() - 1);
            burier = (burier + (burier >= killed)) % victim.size();
            victim[killed] = victim[burier];
            victim.erase(victim.begin() + burier);
            killed = (killed - (burier < killed) + k) % victim.size();
        }
        cout << (n - victim.front() + 1) % n + 1 << endl;
    }
    return 0;
}
