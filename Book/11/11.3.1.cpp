#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    int maxSum = 0;
    for (int a = 1; a <= 13; a++) {
        int sum = S[1][a];
        for (int b = 1; b <= 13; b++) {
            if (b == a) continue;
            sum += S[2][j];
            for (int c = 1; c <= 13; c++) {
                if (c == a || c == b) continue;
                sum += S[3][k];
                // ...
                for (int m = 1; m <= 12; m++) {
                    if (m == a || ... || m == l) continue;
                    sum += S[13][m];
                    if (sum > maxSum) {
                        sum = maxSum;
                        // 记录取法。
                    }
                }
            }
        }
    }

    return 0;
}
