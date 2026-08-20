#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_dec_float.hpp>
using namespace std;
using namespace boost::multiprecision;

using Big = cpp_dec_float_100;

void printAns(const Big &ans, int p) {
    if (ans == 0) cout << fixed << setprecision(p) << Big(0) << '\n';
    else cout << fixed << setprecision(p) << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string op, a, b;
    int p;
    Big x, y, ans;
    while (cin >> op) {
        if (op == "add" || op == "sub" || op == "mul" || op == "div" || op == "pow" || op == "atan2") {
            cin >> a >> b >> p;
            x = Big(a);
            y = Big(b);
            if (op == "add") ans = x + y;
            else if (op == "sub") ans = x - y;
            else if (op == "mul") ans = x * y;
            else if (op == "div") ans = x / y;
            else if (op == "pow") ans = pow(x, y);
            else ans = atan2(x, y);
        } else {
            cin >> a >> p;
            x = Big(a);
            if (op == "exp") ans = exp(x);
            else if (op == "ln") ans = log(x);
            else if (op == "sqrt") ans = sqrt(x);
            else if (op == "asin") ans = asin(x);
            else if (op == "acos") ans = acos(x);
            else if (op == "atan") ans = atan(x);
            else if (op == "sin") ans = sin(x);
            else if (op == "cos") ans = cos(x);
            else ans = tan(x);
        }
        printAns(ans, p);
    }
    return 0;
}
