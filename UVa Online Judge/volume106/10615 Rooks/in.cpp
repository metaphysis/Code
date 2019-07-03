#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 100;
    cout << cases << '\n';
    for (int cs = 1; cs <= cases; cs++)
    {
        int n = rand() % 101;
        cout << n << '\n';
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (rand() % 100 >= 60) cout << '*';
                else cout << '.';
            }
            cout << '\n';
        }
    }
}
