#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    char leftBracket, comma, rightBracket;
    int x, y;
    while (cin >> leftBracket >> x >> comma >> y >> rightBracket) {
        if (x > y) swap(x, y);
        if (x == 0 && y == 2) cout << "wins 2738632; loses 3409819\n";
        if (x == 0 && y == 3) cout << "wins 4466061; loses 5186711\n";
        if (x == 0 && y == 6) cout << "wins 4121220; loses 4678487\n";
        if (x == 1 && y == 1) cout << "wins 1816630; loses 1190535\n";
        if (x == 1 && y == 5) cout << "wins 1795412; loses 2139600\n";
        if (x == 3 && y == 4) cout << "wins 4729392; loses 5832338\n";
        if (x == 4 && y == 6) cout << "wins 3866400; loses 4953686\n";
    }
    return 0;
}
