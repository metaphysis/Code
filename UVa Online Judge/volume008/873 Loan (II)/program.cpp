// Loan (II)
// UVa ID: 873
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int capital, ratePercent, months;
        cin >> capital >> ratePercent >> months;
        
        double monthlyRate = ratePercent / 100.0 / 12.0;
        double payment;
        
        if (fabs(monthlyRate) < 1e-12) {
            payment = static_cast<double>(capital) / months;
        } else {
            double factor = pow(1.0 + monthlyRate, months);
            payment = capital * monthlyRate * factor / (factor - 1.0);
        }
        
        if (caseNo > 1) cout << "\n";
        printf("%.2f\n", payment);
    }
    return 0;
}
