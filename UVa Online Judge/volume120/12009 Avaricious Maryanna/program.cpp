// Avaricious Maryanna
// UVa ID: 12009
// Verdict: Accepted
// Submission Date: 2026-06-03
// UVa Run Time: 0.130s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    vector<int> digits;
    
    BigInt() {}
    BigInt(long long n) {
        if (n == 0) digits.push_back(0);
        else while (n) { digits.push_back(n % 10); n /= 10; }
    }
    BigInt(const string& s) {
        for (int i = (int)s.size() - 1; i >= 0; --i) digits.push_back(s[i] - '0');
    }
    
    string toString() const {
        if (digits.empty()) return "0";
        string res;
        for (int i = (int)digits.size() - 1; i >= 0; --i) res += char(digits[i] + '0');
        return res;
    }
    
    int size() const { return (int)digits.size(); }
    
    BigInt operator*(const BigInt& other) const {
        BigInt res;
        res.digits.resize(digits.size() + other.digits.size(), 0);
        for (size_t i = 0; i < digits.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < other.digits.size(); ++j) {
                int sum = res.digits[i + j] + digits[i] * other.digits[j] + carry;
                res.digits[i + j] = sum % 10;
                carry = sum / 10;
            }
            if (carry) res.digits[i + other.digits.size()] += carry;
        }
        while (res.digits.size() > 1 && res.digits.back() == 0) res.digits.pop_back();
        return res;
    }
    
    void modPow10(int N) {
        if ((int)digits.size() > N) digits.resize(N);
    }
    
    BigInt square() const { return (*this) * (*this); }
    
    bool operator<(const BigInt& other) const {
        if (digits.size() != other.digits.size()) return digits.size() < other.digits.size();
        for (int i = (int)digits.size() - 1; i >= 0; --i)
            if (digits[i] != other.digits[i]) return digits[i] < other.digits[i];
        return false;
    }
    
    bool operator==(const BigInt& other) const {
        if (digits.size() != other.digits.size()) return false;
        for (size_t i = 0; i < digits.size(); ++i)
            if (digits[i] != other.digits[i]) return false;
        return true;
    }
    
    int getDigit(int pos) const {
        if (pos >= (int)digits.size()) return 0;
        return digits[pos];
    }
    
    void setDigit(int pos, int val) {
        if (pos >= (int)digits.size()) digits.resize(pos + 1, 0);
        digits[pos] = val;
    }
};

vector<vector<string>> precompute(int maxN) {
    vector<vector<string>> res(maxN + 1);
    res[1] = {"0", "1", "5", "6"};
    BigInt a("5"), b("6");
    
    for (int N = 1; N < maxN; ++N) {
        BigInt x2 = a.square();
        int m = ((int)x2.digits.size() > N) ? x2.digits[N] : 0;
        int twoXMinus1 = (2 * a.getDigit(0) - 1 + 10) % 10;
        int inv = 0;
        for (int i = 0; i < 10; ++i) {
            if ((twoXMinus1 * i) % 10 == 1) {
                inv = i;
                break;
            }
        }
        int k = ((-m) % 10 + 10) % 10 * inv % 10;
        BigInt aNew = a;
        aNew.setDigit(N, k);
        a = aNew;
        
        x2 = b.square();
        m = ((int)x2.digits.size() > N) ? x2.digits[N] : 0;
        twoXMinus1 = (2 * b.getDigit(0) - 1 + 10) % 10;
        for (int i = 0; i < 10; ++i) {
            if ((twoXMinus1 * i) % 10 == 1) {
                inv = i;
                break;
            }
        }
        k = ((-m) % 10 + 10) % 10 * inv % 10;
        BigInt bNew = b;
        bNew.setDigit(N, k);
        b = bNew;
        
        string sa = a.toString();
        string sb = b.toString();
        if ((int)sa.length() < N + 1) sa = string(N + 1 - sa.length(), '0') + sa;
        if ((int)sb.length() < N + 1) sb = string(N + 1 - sb.length(), '0') + sb;
        
        if (sa[0] != '0') res[N + 1].push_back(sa);
        if (sb[0] != '0') res[N + 1].push_back(sb);
        sort(res[N + 1].begin(), res[N + 1].end());
    }
    
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T;
    cin >> T;
    auto solutions = precompute(500);
    
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N;
        cin >> N;
        cout << "Case #" << caseNo << ":";
        if (solutions[N].empty()) cout << " Impossible\n";
        else {
            for (const string& s : solutions[N]) cout << " " << s;
            cout << "\n";
        }
    }
    
    return 0;
}
