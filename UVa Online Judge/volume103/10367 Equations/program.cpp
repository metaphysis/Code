// Equations
// UVa ID: 10367
// Verdict: Accepted
// Submission Date: 2025-11-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Equation {
    long long a, b, c; // a*x + b*y = c
    Equation() : a(0), b(0), c(0) {}
};

void parseEquation(const string& line, Equation& eq) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (ss >> token) tokens.push_back(token);

    int side = 1;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i] == "=") { side = -1; continue; }
        if (tokens[i] == "+" || tokens[i] == "-") continue;

        int sign = (i > 0 && tokens[i - 1] == "-") ? -1 : 1;
        string term = tokens[i];
        
        if (term[0] == '-') { sign *= -1; term = term.substr(1); }
        
        long long coeff = 1;
        if (isdigit(term[0])) {
            size_t pos = 0;
            coeff = stoll(term, &pos);
            term = term.substr(pos);
        }
        coeff *= sign * side;

        if (term == "x") eq.a += coeff;
        else if (term == "y") eq.b += coeff;
        else eq.c -= coeff;
    }
}

string formatFraction(long long num, long long den) {
    if (den == 0) return "don't know";
    if (num == 0) return "0";
    long long g = __gcd(abs(num), abs(den));
    num /= g; den /= g;
    if (den < 0) { num = -num; den = -den; }
    return den == 1 ? to_string(num) : to_string(num) + "/" + to_string(den);
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    
    for (int caseNum = 0; caseNum < n; ++caseNum) {
        Equation eq1, eq2;
        string line;
        
        getline(cin, line); parseEquation(line, eq1);
        getline(cin, line); parseEquation(line, eq2);
        
        long long a1 = eq1.a, b1 = eq1.b, c1 = eq1.c;
        long long a2 = eq2.a, b2 = eq2.b, c2 = eq2.c;
        
        long long D = a1 * b2 - a2 * b1;
        long long Dx = c1 * b2 - c2 * b1;
        long long Dy = a1 * c2 - a2 * c1;
        
        string xStr = "don't know", yStr = "don't know";
        
        if (D != 0) {
            xStr = formatFraction(Dx, D);
            yStr = formatFraction(Dy, D);
        } else if (Dx != 0 || Dy != 0) {
            // 无解
        } else {
            // 无穷多解，检查每个变量是否被唯一确定
            bool bothEquationsHaveXY = (a1 != 0 && b1 != 0 && a2 != 0 && b2 != 0);
            
            if (!bothEquationsHaveXY) {
                // 至少有一个方程只约束一个变量
                if (a1 != 0 || a2 != 0) {
                    if ((a1 == 0 || a2 == 0) || (c1 * a2 == c2 * a1)) {
                        long long num = (a1 != 0) ? c1 : c2;
                        long long den = (a1 != 0) ? a1 : a2;
                        xStr = formatFraction(num, den);
                    }
                }
                if (b1 != 0 || b2 != 0) {
                    if ((b1 == 0 || b2 == 0) || (c1 * b2 == c2 * b1)) {
                        long long num = (b1 != 0) ? c1 : c2;
                        long long den = (b1 != 0) ? b1 : b2;
                        yStr = formatFraction(num, den);
                    }
                }
            }
            // 如果两个方程都包含x和y（是同一个方程的倍数），则两个变量都没有唯一解
        }
        
        cout << xStr << "\n" << yStr << "\n";
        if (caseNum < n - 1) {
            cout << "\n";
            getline(cin, line);
        }
    }
    return 0;
}
