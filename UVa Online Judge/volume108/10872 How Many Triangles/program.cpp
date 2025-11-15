// How Many Triangles
// UVa ID: 10872
// Verdict: Accepted
// Submission Date: 2025-11-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

long long countTriangles(long long n) {
    if (n < 3) return 0;
    
    if (n % 2 == 0) {
        return (n * n + 24) / 48;
    } else {
        return ((n + 3) * (n + 3) + 24) / 48;
    }
}

int main() {
    long long n;
    int caseNum = 1;
    while (cin >> n && n != 0) {
        long long result = countTriangles(n);
        cout << "Case " << caseNum++ << ": " << result << endl;
    }
    return 0;
}
