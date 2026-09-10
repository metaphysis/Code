#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>  // 大整数支持，避免溢出
using namespace std;
using boost::multiprecision::cpp_int;

// 解码 Cantor 配对函数 P2(i,j) = ((i+j)*(i+j+1))/2 + j
// 返回 (i, j)
pair<cpp_int, cpp_int> decodePair(cpp_int z) {
    cpp_int low = 0, high = 1;
    // 倍增找到上界 high，使得 high*(high+1)/2 > z
    while (high * (high + 1) / 2 <= z) high <<= 1;
    // 二分查找 w = i+j
    while (low < high) {
        cpp_int mid = low + (high - low + 1) / 2;
        if (mid * (mid + 1) / 2 <= z) low = mid;
        else high = mid - 1;
    }
    cpp_int w = low;
    cpp_int t = z - w * (w + 1) / 2;   // j
    cpp_int i = w - t;
    return {i, t};
}

// 从编码中还原顶点序列
vector<pair<cpp_int, cpp_int>> decodePolygon(cpp_int num) {
    auto [len, rest] = decodePair(num);
    vector<cpp_int> coordEnc;
    cpp_int cur = rest;
    cpp_int rem = len;
    while (rem > 1) {
        auto [a, next] = decodePair(cur);
        coordEnc.push_back(a);
        cur = next;
        --rem;
    }
    coordEnc.push_back(cur);  // 最后一个坐标编码
    vector<pair<cpp_int, cpp_int>> verts;
    for (auto& e : coordEnc) {
        auto [x, y] = decodePair(e);
        verts.push_back({x, y});
    }
    return verts;
}

// 鞋带公式计算 2 倍面积（返回正数）
cpp_int computeArea2(const vector<pair<cpp_int, cpp_int>>& verts) {
    cpp_int sum = 0;
    size_t n = verts.size();
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        sum += verts[i].first * verts[j].second - verts[j].first * verts[i].second;
    }
    return sum < 0 ? -sum : sum;
}

// 输出 cpp_int
void printCppInt(cpp_int v) {
    if (v == 0) { cout << '0'; return; }
    string s = v.convert_to<string>();
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string token;
    while (cin >> token) {
        if (token == "*") break;
        cpp_int num(token);  // 从字符串构造，避免溢出
        auto verts = decodePolygon(num);
        cpp_int area2 = computeArea2(verts);
        cpp_int intPart = area2 / 2;
        cpp_int frac = area2 % 2;
        printCppInt(intPart);
        cout << (frac == 0 ? ".0" : ".5") << '\n';
    }
    return 0;
}
