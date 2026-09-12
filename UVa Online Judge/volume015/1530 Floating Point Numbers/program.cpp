#include <bits/stdc++.h>
using namespace std;

int solve() {
    string s;
    cout << "Program 6 by team X\n";
    while (cin >> s) {
        int expBits = 0, i, sign, expVal, outExp;
        double mant = 1.0, val = 0.0;
        sign = s[0] - '0';
        for (i = 1; i <= 7; i++)
            expBits = expBits * 2 + s[i] - '0';
        for (i = 8; i < 16; i++)
            mant += (s[i] - '0') * pow(2.0, -(i - 7));
        expVal = expBits - 63;
        for (i = 1; i < 16; i++)
            if (s[i] == '1') {
                val = ldexp(mant, expVal);
                break;
            }
        if (val == 0.0) {
            cout << " 0.000000e+000\n";
            continue;
        }
        ostringstream out;
        out << scientific << setprecision(6) << val;
        string result = out.str();
        int pos = result.find('e');
        string num = result.substr(0, pos);
        outExp = stoi(result.substr(pos + 1));
        cout << (sign ? '-' : ' ') << num << 'e' << (outExp >= 0 ? '+' : '-');
        cout << setfill('0') << setw(3) << abs(outExp) << setfill(' ') << '\n';
    }
    cout << "End of program 6 by team X\n";
    return 0;
}

int main() {
    return solve();
}
