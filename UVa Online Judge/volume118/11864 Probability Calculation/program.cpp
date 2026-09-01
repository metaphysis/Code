#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long double p, failProb, oddMass, evenMass, fOdd, fEven, fNextOdd;
    int queryCount, caseNum = 1, maxM;
    while (cin >> p >> queryCount) {
        if (queryCount == 0) break;
        vector<int> queries(queryCount);
        maxM = 0;
        for (int i = 0; i < queryCount; i++) {
            cin >> queries[i];
            if (queries[i] > maxM) maxM = queries[i];
        }
        failProb = 1.0L - p;
        vector<long double> prefixSum(maxM + 1, 0.0L);
        fOdd = p;
        oddMass = failProb;
        for (int k = 0; 2 * k + 1 <= maxM; k++) {
            int nOdd = 2 * k + 1;
            prefixSum[nOdd] = prefixSum[nOdd - 1] + fOdd;
            if (nOdd + 1 <= maxM) {
                fEven = fOdd + p * oddMass;
                prefixSum[nOdd + 1] = prefixSum[nOdd] + fEven;
                evenMass = 2.0L * p * oddMass;
                if (nOdd + 2 <= maxM) {
                    fNextOdd = fEven - failProb * evenMass;
                    oddMass = evenMass * (2.0L * k + 3.0L) / (k + 2.0L) * failProb;
                    fOdd = fNextOdd;
                }
            }
        }
        cout << "Case " << caseNum++ << ":\n";
        cout << fixed << setprecision(8);
        for (int i = 0; i < queryCount; i++)
            cout << prefixSum[queries[i]] << '\n';
    }
    return 0;
}
