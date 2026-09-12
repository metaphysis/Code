#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

struct Fraction {
    long long num, den;
};

cpp_int getGcd(cpp_int a, cpp_int b) {
    while (b != 0) {
        cpp_int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCase;
    cin >> testCase;
    while (testCase--) {
        int n;
        cin >> n;
        vector<vector<long double>> cost(n + 1, vector<long double>(n + 1));
        vector<vector<Fraction>> safe(n + 1, vector<Fraction>(n + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                long long a, b;
                char slash;
                cin >> a >> slash >> b;
                safe[i][j] = {b - a, b};
                if (a == b)
                    cost[i][j] = 1e100L;
                else
                    cost[i][j] = -logl((long double)(b - a) / b);
            }
        }
        vector<long double> rowPotential(n + 1), colPotential(n + 1);
        vector<int> matchCol(n + 1), pathCol(n + 1);
        for (int i = 1; i <= n; i++) {
            matchCol[0] = i;
            int currentCol = 0;
            vector<long double> minDistance(n + 1, 1e100L);
            vector<bool> used(n + 1, false);
            do {
                used[currentCol] = true;
                int currentRow = matchCol[currentCol], nextCol = 0;
                long double delta = 1e100L;
                for (int j = 1; j <= n; j++) {
                    if (used[j])
                        continue;
                    long double currentDistance = cost[currentRow][j] - rowPotential[currentRow] - colPotential[j];
                    if (currentDistance < minDistance[j]) {
                        minDistance[j] = currentDistance;
                        pathCol[j] = currentCol;
                    }
                    if (minDistance[j] < delta) {
                        delta = minDistance[j];
                        nextCol = j;
                    }
                }
                for (int j = 0; j <= n; j++) {
                    if (used[j]) {
                        rowPotential[matchCol[j]] += delta;
                        colPotential[j] -= delta;
                    } else
                        minDistance[j] -= delta;
                }
                currentCol = nextCol;
            } while (matchCol[currentCol] != 0);
            do {
                int previousCol = pathCol[currentCol];
                matchCol[currentCol] = matchCol[previousCol];
                currentCol = previousCol;
            } while (currentCol != 0);
        }
        vector<int> matchRow(n + 1);
        for (int j = 1; j <= n; j++)
            matchRow[matchCol[j]] = j;
        cpp_int safeNum = 1, safeDen = 1;
        for (int i = 1; i <= n; i++) {
            int j = matchRow[i];
            safeNum *= safe[i][j].num;
            safeDen *= safe[i][j].den;
        }
        cpp_int riskNum = safeDen - safeNum;
        cpp_int commonDivisor = getGcd(riskNum, safeDen);
        riskNum /= commonDivisor;
        safeDen /= commonDivisor;
        cout << riskNum << "/" << safeDen << '\n';
    }
    return 0;
}
