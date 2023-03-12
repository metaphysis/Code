#include <bits/stdc++.h>

using namespace std;
int used[1000010];
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    srand(time(NULL));
    int T = 10;
    cout << T << '\n';
    for (int cs = 1; cs <= T; cs++) {
        int n = rand() % 1000 + 1;
        cout << n << '\n';
        memset(used, 0, sizeof used);
        for (int i = 0; i < n; i++) {
            int xi = rand() % 1000000 + 1;
            int yi = rand() % 1000000 + 1;
            int li = rand() % 1000000 + 1;
            int wi = rand() % 1000000 + 1;
            while (used[wi]) wi = rand() % 1000000 + 1;
            used[wi] = 1;
            cout << xi << ' ' << yi << ' ' << wi << ' ' << li << '\n';
        }
    }
    return 0;
}
