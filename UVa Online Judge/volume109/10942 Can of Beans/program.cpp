// Can of Beans
// UVa ID: 10942
// Verdict: Accepted
// Submission Date: 2021-12-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool isLeapYear(long long year)
{
    return !(year % 400) || (!(year % 4) && (year % 100));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int numbers[4];
        for (int i = 0; i < 4; i++) cin >> numbers[i];
        sort(numbers + 1, numbers + 4);
        int valid = 0;
        do
        {
            if (numbers[2] == 0 || numbers[3] == 0) continue;
            if (numbers[2] > 12) continue;
            if (numbers[3] > 31) continue;
            if ((numbers[2] == 4 || numbers[2] == 6 || numbers[2] == 9 || numbers[2] == 11) && numbers[3] == 31) continue;
            if (numbers[2] == 2 && numbers[3] >= 30) continue;
            if (!isLeapYear(1LL * numbers[0] + numbers[1]) && numbers[2] == 2 && numbers[3] >= 29) continue;
            valid = 1;
            cout << setw(2) << setfill('0') << numbers[1] << ' ';
            cout << setw(2) << setfill('0') << numbers[2] << ' ';
            cout << setw(2) << setfill('0') << numbers[3] << '\n';
            break;
        } while (next_permutation(numbers + 1, numbers + 4));
        if (!valid) cout << -1 << '\n';
    }

    return 0;
}
