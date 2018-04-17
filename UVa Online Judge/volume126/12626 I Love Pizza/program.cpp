// I Love Pizza
// UVa ID: 12626
// Verdict: Accepted
// Submission Date: 2018-04-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        string line;
        cin >> line;
        int M = 0, A = 0, R = 0, G = 0, I = 0, T = 0;
        for (auto c : line)
        {
            if (c == 'M') M++;
            if (c == 'A') A++;
            if (c == 'R') R++;
            if (c == 'G') G++;
            if (c == 'I') I++;
            if (c == 'T') T++;
        }
        A /= 3, R /= 2;
        int pizzas = 10000;
        pizzas = min(pizzas, M);
        pizzas = min(pizzas, A);
        pizzas = min(pizzas, R);
        pizzas = min(pizzas, G);
        pizzas = min(pizzas, I);
        pizzas = min(pizzas, T);
        cout << pizzas << '\n';
    }

    return 0;
}
