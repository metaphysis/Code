#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;

const int endCost[5] = {2, 3, 5, 6, 9};
const int endValue[5] = {2, 3, 5, 9, 27};

struct Tower {
    int twoCount, endId;
};

// 返回幂塔值与上限中的较小值
int getCap(Tower tower, int cap) {
    int value = min(endValue[tower.endId], cap);
    for (int i = 0; i < tower.twoCount && value < cap; ++i) {
        int nextValue = 1;
        for (int j = 0; j < value && nextValue < cap; ++j) nextValue = min(cap, nextValue * 2);
        value = nextValue;
    }
    return value;
}

// 去掉共同的前置2后，只需比较到28
int compareTower(Tower first, Tower second) {
    int common = min(first.twoCount, second.twoCount), firstValue, secondValue;
    first.twoCount -= common;
    second.twoCount -= common;
    firstValue = getCap(first, 28);
    secondValue = getCap(second, 28);
    if (firstValue < secondValue) return -1;
    if (firstValue > secondValue) return 1;
    return 0;
}

// 求整数乘积不超过限制的最优后缀
Tower getBest(int limit) {
    Tower best = {0, 0};
    for (int endId = 0; endId < 5; ++endId) {
        for (int cost = endCost[endId], twoCount = 0; cost <= limit; cost *= 2, ++twoCount) {
            Tower current = {twoCount, endId};
            if (compareTower(current, best) > 0) best = current;
        }
    }
    return best;
}

// 使用整数运算求对数下取整
int getLimit(const cpp_int &amount, int base) {
    cpp_int power = 1;
    int limit = 0;
    while (power * base <= amount) {
        power *= base;
        ++limit;
    }
    return limit;
}

long long getPower(int base, int exponent) {
    long long value = 1;
    for (int i = 0; i < exponent; ++i) value *= base;
    return value;
}

void printTower(int base, Tower tower) {
    cout << base;
    for (int i = 0; i < tower.twoCount; ++i) cout << "^2";
    if (tower.endId == 0) cout << "^2";
    else if (tower.endId == 1) cout << "^3";
    else if (tower.endId == 2) cout << "^5";
    else if (tower.endId == 3) cout << "^3^2";
    else cout << "^3^3";
    cout << '\n';
}

// 小于64时，寻找字典序最小的等值表示
void solveSmall(int amount) {
    for (int base = 2; base <= amount; ++base) {
        int value = base, exponent = 1;
        while (value < amount) {
            value *= base;
            ++exponent;
        }
        if (value == amount) {
            cout << base;
            if (exponent == 4) cout << "^2^2";
            else if (exponent > 1) cout << '^' << exponent;
            cout << '\n';
            return;
        }
    }
}

void solve(const cpp_int &amount) {
    if (amount < 64) {
        solveSmall(amount.convert_to<int>());
        return;
    }
    int twoLimit = getLimit(amount, 2), threeLimit = getLimit(amount, 3);
    Tower twoTower = getBest(twoLimit), threeTower = getBest(threeLimit);
    int order = compareTower(twoTower, threeTower), twoValue, threeValue;
    if (order <= 0) {
        printTower(3, threeTower);
        return;
    }
    twoValue = getCap(twoTower, 33);
    if (twoValue == 33) {
        printTower(2, twoTower);
        return;
    }
    threeValue = getCap(threeTower, 33);
    if (getPower(2, twoValue) > getPower(3, threeValue)) printTower(2, twoTower);
    else printTower(3, threeTower);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string input;
    while (cin >> input) {
        cpp_int amount = 0;
        for (char digit : input) amount = amount * 10 + (digit - '0');
        solve(amount);
    }
    return 0;
}
