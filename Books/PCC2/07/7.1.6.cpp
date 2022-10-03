#include <bits/stdc++.h>

using namespace std;

#define GET(x) (B[x >> 5] & (1 << (x & 0x1F)))
#define SET(x) (B[x >> 5] |= (1 << (x & 0x1F)))

const int MAXB = 100000010, MAXN = 7000000;

int P[MAXN], B[MAXB >> 5], cnt;

int main(int argc, char *argv[])
{
    for (int i = 2; i < MAXB; i++) {
        if (!GET(i)) P[cnt++] = i;
        for (int j = 0; j < cnt && i * P[j] < MAXB; j++) {
            SET(i * P[j]);
            if (i % P[j] == 0) break;
        }
    }
    
    long long n;
    while (true) {
        cout << "Enter a number which is not bigger than 10^12. Enter 0 to quit.\n";
        cin >> n;
        if (n == 0) break;
        if (n < 0 || n > pow(10, 12)) continue;
        long long r = 1, nn = n;
        for (int i = 0; i < cnt && P[i] * P[i] <= n; i++) {
            if (n % P[i]) continue;
            long long p = P[i];
            while (n % P[i] == 0) {
                n /= P[i];
                p *= P[i];
            }
            r *= (p - 1) / (P[i] - 1);
        }
        if (n > 1) r *= 1 + n;
        cout << "σ(" << nn << ") = " << r << '\n';
    }

    return 0;
}
