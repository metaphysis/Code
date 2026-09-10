#include <bits/stdc++.h>
using namespace std;

int countNotDivisible(int prime, long long rowNumber) {
    long long answer = 1;
    while (rowNumber > 0) {
        int digit = rowNumber % prime;
        answer = answer * (digit + 1) % 10000;
        rowNumber /= prime;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int prime;
    long long rowNumber;
    int caseNumber = 1;
    while (cin >> prime >> rowNumber) {
        if (prime == 0 && rowNumber == 0)
            break;
        int answer = countNotDivisible(prime, rowNumber);
        cout << "Case " << caseNumber << ": " << setw(4) << setfill('0') << answer << '\n';
        ++caseNumber;
    }
    return 0;
}
