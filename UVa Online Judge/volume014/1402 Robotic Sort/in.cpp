#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    srand(time(NULL));
    int n = rand() % 100000 + 1;
    cout << n << '\n';
    for (int i = 1; i <= n; i++) {
        cout << rand() % 1000 + 1;
        cout << " \n"[i == n];
    }
    cout << 0 << '\n';
    return 0;
}
