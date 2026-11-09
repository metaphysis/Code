#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

// 将上述指定格式的小数转换为分数
// fraction表示小数的字符串长度
// lengthOfRepeated表示无限循环部分的长度
pair<ull, ull> getFraction(string fraction, int lengthOfRepeated) {
    // 预先计算10的幂
    ull pow10[21] = {1};
    for (int i = 1; i <= 20; i++) pow10[i] = pow10[i - 1] * 10;
    ull numerator, denominator;
    // 获取小数点之后的所有小数数位
    size_t dot = fraction.find('.');
    if (dot != fraction.npos) fraction = fraction.substr(dot + 1);
    // 区分非循环小数和循环小数分别处理
    if (lengthOfRepeated == 0) {
        numerator = stoull(fraction);
        denominator = pow10[(int)fraction.length()];
    } else {
        int k = fraction.length() - lengthOfRepeated;
        string preRepeated = fraction.substr(0, k);
        if (preRepeated.length() == 0) preRepeated = "0";
        numerator = stoull(fraction) - stoull(preRepeated);
        denominator = pow10[k + lengthOfRepeated] - pow10[k];
    }
    // 对结果进行调整使得分数成为最简分数
    long long g = __gcd(numerator, denominator);
    if (g > 1) numerator /= g, denominator /= g;
    return make_pair(numerator, denominator);
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int lengthOfRepeated, cases = 0;
    string fraction;
    while (cin >> fraction >> lengthOfRepeated) {
        pair<ull, ull> r = getFraction(fraction, lengthOfRepeated);
        cout << "Case " << ++cases << ": " << r.first << "/" << r.second << '\n';
    }
    return 0;
}
