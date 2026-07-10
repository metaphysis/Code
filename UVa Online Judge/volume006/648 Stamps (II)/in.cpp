#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    srand(time(NULL));
    for (int cs = 1; cs <= 100; cs++)
    {
        int n = rand() % 25 + 1;
        for (int i = 0; i < n; i++)
            cout << rand() % 100 + 1 << ' ';
        cout << "0\n";
        n = rand() % 25 + 1;
        for (int i = 0; i < n; i++)
            cout << rand() % 200 + 1 << ' ';
        cout << "0\n";
    }

    return 0;
}
