#include <iostream>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

// 按公式计算： (n^4 - 6n^3 + 23n^2 - 18n + 24) / 24
static cpp_int getPieces(const std::string& line) {
    cpp_int n(line);
    return (n * n * n * n - 6 * n * n * n + 23 * n * n - 18 * n + 24) / 24;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    if (!getline(cin, line)) return 0;
    int cases = stoi(line);
    while (cases--) {
        getline(std::cin, line);
        cout << getPieces(line) << '\n';
    }
    return 0;
}
