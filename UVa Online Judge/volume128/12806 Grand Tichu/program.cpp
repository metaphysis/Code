#include <bits/stdc++.h>
using namespace std;

long long combination(int n, int k) {
    if (k < 0 || k > n) return 0;
    k = min(k, n - k);
    long long result = 1;
    for (int i = 1; i <= k; i++) result = result * (n - k + i) / i;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string cards;
    while (cin >> cards && cards != "0") {
        int hasA = 0, hasD = 0, hasP = 0, hasM = 0, hasDogs = 0;
        for (char card : cards) {
            if (card == 'A') hasA++;
            else if (card == 'D') hasD = 1;
            else if (card == 'P') hasP = 1;
            else if (card == 'M') hasM = 1;
            else if (card == 'd') hasDogs = 1;
        }
        int remA = 4 - hasA, remD = 1 - hasD, remP = 1 - hasP, remM = 1 - hasM, remDogs = 1 - hasDogs;
        int remOther = 48 - remA - remD - remP - remM - remDogs;
        long long goodWays[4] = {0, 0, 0, 0}, totalWays = combination(48, 6);
        for (int addA = 0; addA <= remA; addA++) {
            for (int addD = 0; addD <= remD; addD++) {
                for (int addP = 0; addP <= remP; addP++) {
                    for (int addM = 0; addM <= remM; addM++) {
                        for (int addDogs = 0; addDogs <= remDogs; addDogs++) {
                            int used = addA + addD + addP + addM + addDogs, addOther = 6 - used;
                            if (addOther < 0 || addOther > remOther) continue;
                            long long ways = combination(remA, addA) * combination(remOther, addOther);
                            int totalA = hasA + addA, totalD = hasD + addD, totalP = hasP + addP, totalM = hasM + addM, totalDogs = hasDogs + addDogs;
                            if (totalD && totalP && totalA >= 1) goodWays[0] += ways;
                            if (totalD && totalA >= 2) goodWays[1] += ways;
                            if (totalP && totalA >= 3) goodWays[2] += ways;
                            if (totalD && totalP && totalM && totalDogs) goodWays[3] += ways;
                        }
                    }
                }
            }
        }
        bool isGrand = false;
        for (int i = 0; i < 4; i++)
            if (4 * goodWays[i] > totalWays) isGrand = true;
        if (isGrand) cout << "Grand Tichu!\n";
        else cout << "...\n";
    }
    return 0;
}
