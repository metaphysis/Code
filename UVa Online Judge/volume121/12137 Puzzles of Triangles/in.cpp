#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    for (int i = 1; i <= 800; i++)
        cout << ((long long)rand() * (long long)rand() % (100000000000000LL - 1LL) + 1) << '\n';
    cout << 0 << '\n';
    return 0;
}
