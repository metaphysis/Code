#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 15;
    for (int cs = 1; cs <= cases; cs++)
    {
        int n = rand() % 100 + 1;
        cout << n << '\n';
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (j) cout << ' ';
                cout << rand() % 100 + 1;
            }
            cout << '\n';
        }
    }
    return 0;
}
