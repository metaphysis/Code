// Complex Numbers
// UVa ID: 10378
// Verdict: Accepted
// Submission Date: 2025-11-13
// UVa Run Time: 0.060s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

struct Complex {
    double real;
    double imag;

    Complex(double r, double i) : real(r), imag(i) {}

    // 用于排序：实部降序，虚部降序
    bool operator<(const Complex& other) const {
        // 注意误差，否则可能难以获得 Accepted
        if (fabs(real - other.real) > 1e-6) {
            return real > other.real; // 实部降序
        }
        return imag > other.imag; // 虚部降序
    }
};

// 解析复数字符串，返回实部和虚部
pair<int, int> parseComplex(const string& s) {
    int a = 0, b = 0;
    size_t plusPos = s.find('+');
    size_t minusPos = s.find('-', 1); // 从位置1开始找，避免第一个负号

    if (plusPos != string::npos) {
        a = stoi(s.substr(0, plusPos));
        b = stoi(s.substr(plusPos + 1, s.size() - plusPos - 2)); // 去掉最后的 'i'
    } else if (minusPos != string::npos) {
        a = stoi(s.substr(0, minusPos));
        b = -stoi(s.substr(minusPos + 1, s.size() - minusPos - 2)); // 虚部为负
    }
    return {a, b};
}

// 格式化浮点数，避免 -0.000
string format(double value) {
    stringstream ss;
    ss << fixed << setprecision(3);
    ss << value;
    string result = ss.str();
    // 检查四舍五入后是否为 -0.000
    if (result == "-0.000") return "0.000";
    return result;
}

// 格式化复数输出
string formatComplex(const Complex& c) {
    string realStr = format(c.real);
    string imagStr = format(c.imag);
    if (imagStr == "0.000" || imagStr.front() != '-') return realStr + "+" + imagStr + "i";
    else return realStr + imagStr + "i";
}

int main() {
    string line;
    int caseNum = 0;

    while (getline(cin, line)) {
        caseNum++;

        // 解析输入行
        size_t spacePos = line.find(' ');
        string complexStr = line.substr(0, spacePos);
        int n = stoi(line.substr(spacePos + 1));

        auto [a, b] = parseComplex(complexStr);

        // 计算模长和幅角
        double r = sqrt(a * a + b * b);
        double theta = atan2(b, a);

        // 计算 r^(1/n)
        double rn = pow(r, 1.0 / n);

        vector<Complex> roots;
        for (int k = 0; k < n; k++) {
            double angle = (theta + 2 * k * M_PI) / n;
            double realPart = rn * cos(angle);
            double imagPart = rn * sin(angle);
            roots.emplace_back(realPart, imagPart);
        }

        // 排序
        sort(roots.begin(), roots.end());

        // 输出
        cout << "Case " << caseNum << ":" << endl;
        for (const auto& root : roots) {
            cout << formatComplex(root) << endl;
        }
        cout << endl;
    }

    return 0;
}
