#include <bits/stdc++.h>
using namespace std;

pair<long long, long long> getFraction(string fraction, int lengthOfRepeated) {
    long long numerator, denominator;
    size_t dot = fraction.find('.');
    if (dot != fraction.npos) fraction = fraction.substr(dot + 1);
    if (lengthOfRepeated == 0) {
        numerator = stoll(fraction);
        denominator = pow(10, fraction.length());
    } else {
        int k = fraction.length() - lengthOfRepeated;
        string preRepeated = fraction.substr(0, k);
        if (preRepeated.length() == 0) preRepeated = "0";
        cout << fraction << ' ' << preRepeated << '\n';
        numerator = stoll(fraction) - stoll(preRepeated);
        denominator = pow(10, k + lengthOfRepeated) - pow(10, k);
    }
    cout << numerator << ' ' << denominator << '\n';
    long long g = __gcd(numerator, denominator);
    if (g > 1) numerator /= g, denominator /= g;
    cout << numerator << ' ' << denominator << '\n';
    return make_pair(numerator, denominator);
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int lengthOfRepeated, cases = 0;
    string fraction;
    while (cin >> fraction >> lengthOfRepeated) {
        pair<long long, long long> r = getFraction(fraction, lengthOfRepeated);
        cout << "Case " << ++cases << ": " << r.first << "/" << r.second << '\n';
    }
    return 0;
}
