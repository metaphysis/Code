#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 500;
    cout << cases << '\n';
    for (int i = 1; i <= cases; i++)
    {
        int t1 = 360 + rand() % 720;
        int t2 = t1 + rand() % (1080 - t1) + 1;
        int s1 = 360 + rand() % 720;
        int s2 = s1 + rand() % (1080 - s1) + 1;
        int w = rand() % 90 + 1;
        cout << t1 << ' ' << t2 << ' ' << s1 << ' ' << s2 << ' ' << w << '\n';
    }
    return 0;
}
