#include <bits/stdc++.h>
using namespace std;

using UnsignedLongLong = unsigned long long;

UnsignedLongLong powerOfTwo[41];
UnsignedLongLong powerOfThree[41];

UnsignedLongLong getPrefixSum(UnsignedLongLong value) {
    if (value == 0) return 1;
    UnsignedLongLong result = 0;
    UnsignedLongLong oneCount = 0;
    for (int bit = 40; bit >= 0; --bit)
        if ((value >> bit) & 1) {
            // 当前位改为 0，后面的位可以任意取值
            result += powerOfTwo[oneCount] * powerOfThree[bit];
            ++oneCount;
        }
    // 加上 value 自身对应的权值
    result += powerOfTwo[oneCount];
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    powerOfTwo[0] = 1;
    powerOfThree[0] = 1;
    for (int i = 1; i <= 40; ++i) {
        powerOfTwo[i] = powerOfTwo[i - 1] * 2;
        powerOfThree[i] = powerOfThree[i - 1] * 3;
    }
    UnsignedLongLong low;
    UnsignedLongLong high;
    while (cin >> low >> high) {
        if (low == 0 && high == 0) break;
        UnsignedLongLong leftSum = low == 0 ? 0 : getPrefixSum(low - 1);
        UnsignedLongLong rightSum = getPrefixSum(high);
        cout << rightSum - leftSum << '\n';
    }
    return 0;
}
