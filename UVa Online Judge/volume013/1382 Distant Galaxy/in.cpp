#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 100;
    for (int cs = 1; cs <= cases; cs++)
    {
        int n = rand() % 100 + 1;
        cout << n << '\n';
        int x[110], y[110];
        x[0] = rand() % 1000000000 + 1;
        y[0] = rand() % 1000000000 + 1;
        if (rand() % 2) x[0] *= -1;
        if (rand() % 2) y[0] *= -1;
        cout << x[0] << ' ' << y[0] << '\n';
        for (int i = 1; i < n; )
        {
            x[i] = rand() % 1000000000 + 1;
            y[i] = rand() % 1000000000 + 1;
            if (rand() % 2) x[i] *= -1;
            if (rand() % 2) y[i] *= -1;
            bool flag = true;
            for (int j = 0; j < i; j++)
                if (x[j] == x[i] && y[j] == y[i])
                {
                    flag = false;
                    break;
                }
            if (flag)
            {
                cout << x[i] << ' ' << y[i] << '\n';
                i++;
            }
        }
    }
    cout << "0\n";
    return 0;
}
