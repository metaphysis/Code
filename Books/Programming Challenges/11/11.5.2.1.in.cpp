#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    srand(time(NULL));
    int cases = 100;
    for (int cs = 1; cs <= cases; cs++)
    {
        int n = rand() % 100 + 1;
        cout << n << '\n';
        for (int i = 0; i < n; i++)
        {
            if (i) cout << ' ';
            cout << (rand() % 1000000 + 1);
        }
        cout << '\n';
    }    

    return 0;
}
