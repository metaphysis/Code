#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    srand(time(NULL));
    for (int cs = 1; cs <= 5; cs++)
    {
        int n = rand() % 40000 + 1;
        cout << n << '\n';
        for (int i = 1; i <= n; i++) cout << rand() % 2000000001 << '\n';
        cout << '\n';
    }
    cout << 0 << '\n';
    return 0;
}
