#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cout << 1 << '\n';
    
    for (int i = 0; i < 61; i++) 
    {
        if (i % 16) cout << ' ';
        cout << 4;
        if ((i + 1) % 16 == 0) cout << '\n';
    }
    cout << '\n';
    cout << 801 * 12 << '\n';
    for (int i = 0; i <= 800; i++)
        for (int j = 1; j <= 12; j++)
            cout << i << ' ' << j << ' ' << 1 << '\n';

    return 0;
}
