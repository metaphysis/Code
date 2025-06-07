#include <bits/stdc++.h>

using namespace std;

const int N = 7000055;

int sn[N], sa[N], pos[N], c[N], lcp[N];

inline bool leq(int a, int b, int c, int d) {
    return a == c ? b <= d : a < c;
}

inline bool leq(int a, int b, int c, int d, int e, int f) {
    return a == d ? leq(b, c, e, f) : a < d;
}

inline void radixSort(int a[], int b[], int r[], int n, int K) {
    memset(c, 0, sizeof(int) * (K + 1));
    for (int i = 0; i < n; i++) c[r[a[i]]]++;
    for (int i = 0, sum = 0; i <= K; i++) {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (int i = 0; i < n; i++) b[c[r[a[i]]]++] = a[i];
}

void DC3algorithm(int s[], int sa[], int n, int K) {
    // sizes
    int nL = (n + 2) / 3;
    int nM = (n + 1) / 3;
    int nR = n / 3;
    int nLR = nL + nR;

    // dummy subarrays
    // int sL[nL], saL[nL], sMR[nLR+3], saMR[nLR+3];

    int *sL = new int[nL], *saL = new int[nL];
    int *sMR = new int[nLR + 3], *saMR = new int[nLR + 3];

    // assign triples
    for (int i = 0; i < 3; i++)
        sMR[i] = saMR[i] = 0;

    // radix sort those not divisible by 3
    for (int i = 0, j = 0; i < n + nL - nM; i++)
        if (i % 3 != 0)
            sMR[j++] = i;

    // "swap" indices
    radixSort(sMR, saMR, s + 2, nLR, K);
    radixSort(saMR, sMR, s + 1, nLR, K);
    radixSort(sMR, saMR, s, nLR, K);

    // assign bucket names
    int name = 0;
    c[0] = c[1] = c[2] = -1;
    for (int i = 0; i < nLR; i++)
    {
        bool equal = true;
        for (int j = 0; j < 3; j++)
        {
            equal &= (c[j] == s[saMR[i] + j]);
            c[j] = s[saMR[i] + j];
        }
        if (!equal) name++;
        // key assignment
        if (saMR[i] % 3 == 1) sMR[saMR[i] / 3] = name;
        else sMR[saMR[i] / 3 + nL] = name;
    }

    // ternary partition
    if (name < nLR) {
        DC3algorithm(sMR, saMR, nLR, name);
        for (int i = 0; i < nLR; i++)
            sMR[saMR[i]] = i + 1;
    } else {
        for (int i = 0; i < nLR; i++) saMR[sMR[i] - 1] = i;
    }
    for (int i = 0, j = 0; i < nLR; i++)
        if (saMR[i] < nL)
            sL[j++] = 3 * saMR[i];
    radixSort(sL, saL, s, nL, K);
    for (int p = 0, t = nL - nM, k = 0; k < n; k++) {
        #define GI (saMR[t] < nL ? 3*saMR[t] + 1 : 3*(saMR[t] - nL) + 2)
        int i = GI;
        int j = saL[p];
        if (saMR[t] < nL ?
            leq(s[i], sMR[saMR[t] + nL], s[j], sMR[j / 3]) :
            leq(s[i], s[i + 1], sMR[saMR[t] - nL + 1], s[j], s[j + 1], sMR[j / 3 + nL]))
        {
            sa[k] = i;
            if (++t == nLR)
                for (k++; p < nL; p++, k++)
                    sa[k] = saL[p];
        }
        else
        {
            sa[k] = j;
            if (++p == nL)
                for (k++; t < nLR; t++, k++)
                    sa[k] = GI;
        }
        #undef GI
    }
    delete[]sL, saL, sMR, saMR;
}

// driver function build SA
void buildSA(char str[], int n) {
    char mn = 127, mx = 0;
    for (int i = 0; i < n; i++) {
        mn = min(mn, str[i]);
        mx = max(mx, str[i]);
    }
    for (int i = 0; i < n; i++) sn[i] = str[i] - mn + 1;
    sn[n] = sn[n + 1] = sn[n + 2] = 0;
    DC3algorithm(sn, sa, n, mx - mn + 1);
    for (int i = 0; i < n; i++) pos[sa[i]] = i;
}

// least common prefix, assuming sa is built
void buildLCP(char s[], int n) {
    for (int i = 0, k = 0; i < n; ++i)
        if (pos[i] != n - 1) {
            for (int j = sa[pos[i] + 1]; s[i + k] == s[j + k]; ++k);
            lcp[pos[i]] = k;
            if (k) --k;
        } else lcp[pos[i]] = 0;
}

char s[N];
bool mark[N];
int grp[N], ptr[8], t, m, freq[N];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &m);
        char *S = s;
        for (int i = 0; i < m; ++i) {
            scanf("%s", S);
            int len = strlen(S);
            for (int j = 0; j < len; ++j)
                if (S[j] == 'G')
                    S[j] = 'B';
                else if (S[j] == 'T')
                    S[j] = 'D';
            fill(grp + (S - s), grp + (S + len - s), i);
            S += len;
            grp[S - s] = -1;
            S[0] = 'A' - 1;
            S[1] = '\0';
            ++S;
            ptr[i] = -1;
        }
        int n = S - s;
        buildSA(s, n);
        buildLCP(s, n);
        int needed = m, R;
        for (R = 0; R < n && needed > 0; ++R) {
            int g = grp[sa[R]];
            if (~g && !~ptr[g]) {
                mark[R] = true;
                ptr[g] = R;
                --needed;
            }
        }
        --R;
        int L = *min_element(ptr, ptr + m);
        memset(freq, 0, sizeof(int) * (n + 1));
        int mn = 2147483647;
        for (int i = L; i < R; ++i) {
            ++freq[lcp[i]];
            mn = min(mn, lcp[i]);
        }
        int mx = mn;
        while (true) {
            // slide the window
            int march = L + 1;
            while (march < n && grp[sa[march]] != grp[sa[L]]) ++march;
            if (march >= n) break;
            int fmark = march;
            for (int i = march - 1; i > L; --i)
                if (mark[i])
                    fmark = i;
            mark[L] = 0;
            mark[march] = 1;
            while (march > R) {
                ++freq[lcp[R]];
                mn = min(mn, lcp[R++]);
            }
            while (L < fmark) {
                --freq[lcp[L++]];
                while (freq[mn] == 0)
                    ++mn;
            }
            mx = max(mx, mn);
        }
        printf("%d\n", mx);
    }
}
