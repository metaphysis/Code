// Bisection Method
// UVa ID: 12635
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.170s

#include <bits/stdc++.h>
using namespace std;

vector<int> rootList;

int getSign(long long num, long long den) {
    int cnt = 0;
    for (int root : rootList) {
        long long value = 1LL * root * den;
        if (num == value) return 0;
        if (num < value) cnt++;
    }
    return cnt % 2 == 0 ? 1 : -1;
}

bool checkPair(int left, int right, int root, int step, int mask) {
    int leftSign = getSign(left, 1), rightSign = getSign(right, 1);
    if (leftSign == 0 || rightSign == 0 || leftSign == rightSign) return false;
    long long leftNum = left, rightNum = right, den = 1;
    for (int i = 1; i <= step; i++) {
        long long midNum = leftNum + rightNum, midDen = den * 2;
        int midSign = getSign(midNum, midDen);
        if (midSign == 0) {
            if (i == step && midNum == 1LL * root * midDen) return true;
            return false;
        }
        if (i == step) return false;
        int dir = leftSign * midSign < 0 ? 0 : 1;
        int need = (mask >> (i - 1)) & 1;
        if (dir != need) return false;
        if (dir == 0) {
            leftNum *= 2;
            rightNum = midNum;
        } else {
            leftNum = midNum;
            rightNum *= 2;
        }
        den *= 2;
        leftSign = getSign(leftNum, den);
    }
    return false;
}

long long countWays(int root) {
    long long ans = 0;
    for (int step = 1; step <= 7; step++) {
        int total = 1 << (step - 1);
        for (int mask = 0; mask < total; mask++) {
            long long leftA = 1, leftB = 0, rightA = 0, rightB = 1;
            for (int i = 1; i < step; i++) {
                long long midA = leftA + rightA, midB = leftB + rightB;
                if (((mask >> (i - 1)) & 1) == 0) {
                    leftA *= 2;
                    leftB *= 2;
                    rightA = midA;
                    rightB = midB;
                } else {
                    leftA = midA;
                    leftB = midB;
                    rightA *= 2;
                    rightB *= 2;
                }
            }
            long long a = leftA + rightA, b = leftB + rightB;
            long long den = 1LL << step;
            for (int left = 0; left < 10000; left++) {
                long long value = 1LL * root * den - a * left;
                if (value <= 0 || value % b != 0) continue;
                long long right = value / b;
                if (right <= left || right > 10000) continue;
                if (checkPair(left, right, root, step, mask)) ans++;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int test;
    cin >> test;
    string line;
    getline(cin, line);
    while (test--) {
        getline(cin, line);
        while (line.empty()) getline(cin, line);
        rootList.clear();
        for (int i = 0; i < (int)line.size(); i++) {
            if (line[i] == '=') break;
            if (!isdigit(line[i])) continue;
            int value = 0;
            while (i < (int)line.size() && isdigit(line[i])) {
                value = value * 10 + line[i] - '0';
                i++;
            }
            rootList.push_back(value);
            i--;
        }
        int root;
        cin >> root;
        cout << countWays(root) << '\n';
        getline(cin, line);
    }
    return 0;
}
