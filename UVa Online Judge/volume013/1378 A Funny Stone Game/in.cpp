#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 1000;
    for (int cs = 1; cs <= cases; cs++)
    {
        int n = rand() % 23 + 1;
        cout << n << '\n';
        for (int i = 0; i < n; i++)
        {
            if (i) cout << ' ';
            cout << rand() % 1001;
        }
        cout << '\n';
    }
    cout << "0\n";
    return 0;
}
