#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000;

int sg[MAXN];

int grundy(int x)
{
    if (~sg[x]) return sg[x];
    set<int> s;
    for (int i = 1; i <= x / 2; i++)
        s.insert(grundy(x - i));
    int g = 0;
    while (s.find(g) != s.end()) g++;
    return sg[x] = g;
}

int main(int argc, char *argv[])
{
    memset(sg, -1, sizeof(sg));
    for (int i = 1; i <= 200; i++)
        cout << i << '=' << grundy(i) << '\n';
    return 0;
}
