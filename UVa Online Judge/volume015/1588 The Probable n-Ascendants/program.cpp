#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string gene, pairName[6] = {"BBBB", "BBBw", "BBww", "BwBw", "Bwww", "wwww"};
    int level;
    bool firstCase = true;
    while (cin >> gene >> level) {
        long double x = 0, y = 0, z = 0, pairProb[6] = {};
        if (gene == "BB") x = 1;
        else if (gene == "ww") z = 1;
        else y = 1;
        for (int step = 0; step < level; ++step) {
            pairProb[0] = x;
            pairProb[1] = (x + y) / 2;
            pairProb[2] = y;
            pairProb[3] = (x + 2 * y + z) / 4;
            pairProb[4] = (y + z) / 2;
            pairProb[5] = z;
            long double total = 0;
            for (int i = 0; i < 6; ++i) total += pairProb[i];
            for (int i = 0; i < 6; ++i) pairProb[i] /= total;
            x = pairProb[0] + (pairProb[1] + pairProb[2]) / 2;
            y = pairProb[3] + (pairProb[1] + pairProb[4]) / 2;
            z = pairProb[5] + (pairProb[2] + pairProb[4]) / 2;
        }
        if (!firstCase) cout << '\n';
        firstCase = false;
        for (int i = 0; i < 6; ++i) {
            if (pairProb[i] <= 0) continue;
            cout << pairName[i] << ' ';
            cout << fixed << setprecision(2) << (pairProb[i] * 100 + 1e-11L);
            cout << "%\n";
        }
    }
    return 0;
}
