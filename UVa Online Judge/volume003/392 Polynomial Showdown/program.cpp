// Polynomial Showdown
// UVa ID: 392
// Verdict: Accepted
// Submission Date: 2016-06-27
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool headTermSetted = false;

inline void term(int coefficient, int degree)
{
    if (degree == 0)
    {
        if (headTermSetted)
        {
            if (coefficient == 0) return;
            cout << (coefficient > 0 ? " + " : " - ");
            cout << abs(coefficient);
        }
        else
            cout << coefficient;
            
        return;
    }

    if (coefficient == 0) return;
            
    if (headTermSetted)
    {
        cout << (coefficient > 0 ? " + " : " - ");
        if (abs(coefficient) > 1) cout << abs(coefficient);
    }
    else
    {
        if (abs(coefficient) > 1) cout << coefficient;
        else if (coefficient < 0) cout << "-";
    }

    cout << "x";
    if (degree > 1) cout << "^" << degree;

    headTermSetted = true;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int c8, c7, c6, c5, c4, c3, c2, c1, c0;

    while (cin >> c8 >> c7 >> c6 >> c5 >> c4 >> c3 >> c2 >> c1 >> c0)
    {
        headTermSetted = false;

        term(c8, 8);
        term(c7, 7);
        term(c6, 6);
        term(c5, 5);
        term(c4, 4);
        term(c3, 3);
        term(c2, 2);
        term(c1, 1);
        term(c0, 0);

        cout << endl;
    }

    return 0;
}
