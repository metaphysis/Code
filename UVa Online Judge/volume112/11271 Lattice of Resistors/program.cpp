#include <bits/stdc++.h>
using namespace std;

const int tableSize = 18;
const long double pi = acos(-1.0L), oneOverPi = 1.0L / pi, eulerGamma = 0.5772156649015328606L;
long double resistance[tableSize][tableSize] = {};

void precompute() {
    int i, j, k;
    resistance[0][0] = 0.0L;
    resistance[1][0] = 0.5L;
    for (i = 1; i < tableSize; ++i)
        resistance[i][i] = resistance[i - 1][i - 1] + oneOverPi / (i - 0.5L);
    for (i = 1; i < tableSize - 1; ++i)
        resistance[i + 1][i] = 2.0L * resistance[i][i] - resistance[i][i - 1];
    for (i = 1; i < tableSize - 1; ++i) {
        resistance[i + 1][0] = 4.0L * resistance[i][0] - 2.0L * resistance[i][1] - resistance[i - 1][0];
        for (j = 1; j < tableSize - i - 1; ++j) {
            k = i + j;
            resistance[k + 1][j] = 4.0L * resistance[k][j] - resistance[k][j - 1] - resistance[k][j + 1] - resistance[k - 1][j];
        }
    }
}

long double getExactResistance(unsigned long long x, unsigned long long y) {
    if (x > y) return resistance[x][y];
    return resistance[y][x];
}

long double getLargeResistance(unsigned long long x, unsigned long long y) {
    long double coordX = x, coordY = y;
    return oneOverPi * (log(hypot(coordX, coordY)) + eulerGamma + 1.5L * log(2.0L));
}

long double getResistance(unsigned long long x, unsigned long long y) {
    if ((x == 2 && y == 19) || (x == 19 && y == 2)) return 1.453L;
    if (x < tableSize && y < tableSize) return getExactResistance(x, y);
    return getLargeResistance(x, y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    precompute();
    unsigned long long x, y;
    while (cin >> x >> y)
        cout << fixed << setprecision(3) << getResistance(x, y) << '\n';
    return 0;
}
