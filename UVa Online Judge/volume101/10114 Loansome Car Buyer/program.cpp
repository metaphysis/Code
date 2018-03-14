// Loansome Car Buyer
// UVa ID: 10114
// Verdict: Accepted
// Submission Date: 2017-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int months, records, lastMonth, currentMonth;
    double downPayment, loan, depreciation[110], percent, lastPercent;
    
    while (cin >> months, months >= 0)
    {
        cin >> downPayment >> loan >> records;
        lastMonth = 0;
        for (int i = 0; i < records; i++)
        {
            cin >> currentMonth >> percent;
            for (int j = lastMonth; j < currentMonth; j++)
                depreciation[j] = lastPercent;
            depreciation[currentMonth] = percent;
            lastMonth = currentMonth + 1;
            lastPercent = percent;
        }
        for (int j = lastMonth; j <= months; j++)
            depreciation[j] = percent;

        double payPerMonth = loan / months;
        double valueOfCar = loan + downPayment, owes = loan;
        for (int i = 0; i <= months; i++)
        {
            if (i) owes -= payPerMonth;
            valueOfCar *= (1.0 - depreciation[i]);
            if (owes < valueOfCar)
            {
                cout << i << ' ';
                if (i == 1) cout << "month\n";
                else cout << "months\n";
                break;
            }
        }
    }

    return 0;
}
