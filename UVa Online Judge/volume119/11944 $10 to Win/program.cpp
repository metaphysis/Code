#include <bits/stdc++.h>
using namespace std;

long long getMultiplier(int moneyLine) {
    if (moneyLine > 0)
        return moneyLine * 10;
    long long absoluteLine = -static_cast<long long>(moneyLine);
    return (100000 + absoluteLine / 2) / absoluteLine;
}

string formatMoney(long long amount) {
    string result = to_string(amount);
    for (int position = static_cast<int>(result.size()) - 3; position > 0; position -= 3) result.insert(position, ",");
    return "$" + result + ".00";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseNumber = 1; caseNumber <= testCount; caseNumber++) {
        long long currentAmount;
        int wagerCount;
        cin >> currentAmount >> wagerCount;
        for (int i = 0; i < wagerCount; i++) {
            int moneyLine;
            cin >> moneyLine;
            long long multiplier = getMultiplier(moneyLine);
            long long amountWon = (currentAmount * multiplier + 999) / 1000;
            currentAmount += amountWon;
            // 超过上限后无需继续扩大金额
            if (currentAmount > 1000000) currentAmount = 1000000;
        }
        cout << caseNumber << " " << formatMoney(currentAmount) << '\n';
    }
    return 0;
}
