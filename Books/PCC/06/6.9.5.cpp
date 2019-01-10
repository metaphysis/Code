#include <bits/stdc++.h>

using namespace std;

const double GOLDEN_RATIO = (1 + sqrt(5)) / 2;

int main(int argc, char *argv[])
{
    int ai, bi;

    while (cin >> ai >> bi)
    {
        if (min(ai, bi) == (int)(GOLDEN_RATIO * abs(ai - bi)))
            cout << "A Lose!\n";
        else
            cout << "A Win!\n";
    }

    return 0;
}
