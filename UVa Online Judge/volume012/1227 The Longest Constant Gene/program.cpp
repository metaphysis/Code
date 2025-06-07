#include <bits/stdc++.h>

using namespace std;

#define maxn 7001000

#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)

int wa[maxn], wb[maxn], wv[maxn], wws[maxn];

int c0(int *r, int a, int b) {
    return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
}

int c12(int k, int *r, int a, int b) {
    if (k == 2)
        return r[a] < r[b] || r[a] == r[b] && c12(1, r, a + 1, b + 1);
    else
        return r[a] < r[b] || r[a] == r[b] && wv[a + 1] < wv[b + 1];
}

void sort(int *r, int *a, int *b, int n, int m) {
    int i;
    for (i = 0; i < n; i++) wv[i] = r[a[i]];
    for (i = 0; i < m; i++) wws[i] = 0;
    for (i = 0; i < n; i++) wws[wv[i]]++;
    for (i = 1; i < m; i++) wws[i] += wws[i - 1];
    for (i = n - 1; i >= 0; i--) b[--wws[wv[i]]] = a[i];
}

void dc3(int *r, int *sa, int n, int m) {
    int i, j, *rn = r + n, *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
    r[n] = r[n + 1] = 0;
    for (i = 0; i < n; i++)
        if (i % 3 != 0)
            wa[tbc++] = i;
    sort(r + 2, wa, wb, tbc, m);
    sort(r + 1, wb, wa, tbc, m);
    sort(r, wa, wb, tbc, m);
    for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
        rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
    if (p < tbc) dc3(rn, san, tbc, p);
    else
        for (i = 0; i < tbc; i++)
            san[rn[i]] = i;
    for (i = 0; i < tbc; i++)
        if (san[i] < tb)
            wb[ta++] = san[i] * 3;
    if (n % 3 == 1) wb[ta++] = n - 1;
    sort(r, wb, wa, ta, m);
    for (i = 0; i < tbc; i++) wv[wb[i] = G(san[i])] = i;
    for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
        sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
    for (; i < ta; p++) sa[p] = wa[i++];
    for (; j < tbc; p++) sa[p] = wb[j++];
}

int ranks[maxn], height[maxn];
void calheight(int *r, int *sa, int n)
{
    int i, j, k = 0;
    for (i = 1; i <= n; i++)
        ranks[sa[i]] = i;
    for (i = 0; i < n; height[ranks[i++]] = k)
        for (k ? k-- : 0, j = sa[ranks[i] - 1]; r[i + k] == r[j + k]; k++);
}

int r[maxn], sa[maxn];
int who[maxn];
int len, T, m, tag[32];
char st[2000010];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &m);
        len = 0;
        for (int i = 1; i <= m; i++) {
            scanf("%s", st);
            int k = strlen(st);
            for (int j = 0; j < k; j++) {
                char ch = st[j];
                if (ch == 'G') ch = 'B';
                if (ch == 'T') ch = 'D';
                r[j + len] = ch - 'A' + 10;
                who[j + len] = i;
            }
            r[len + k] = i;
            who[len + k] = 0;
            len += k + 1;
        }
        len--;
        r[len] = 0;
        continue;
        dc3(r, sa, len + 1, 16);
        calheight(r, sa, len);
        for (int i = 0; i < 32; i++) tag[i] = 0;
        int c = 0, mh = 0, left = m, right = m + 1;
        if (!tag[who[sa[left]]]) c++;
        tag[who[sa[left]]]++;
        if (!tag[who[sa[right]]]) c++;
        tag[who[sa[right]]]++;
        while (left <= right) {
            if (c >= m) {
                int h = height[left + 1];
                if (h > mh) {
                    for (int i = left + 2; i <= right; i++)
                        if (height[i] < h)
                            h = height[i];
                    if (h > mh)  mh = h;
                }
            }
            if (c < m) {
                right++;
                if (right > len) break;
                if (!tag[who[sa[right]]]) c++;
                tag[who[sa[right]]]++;
            } else {
                tag[who[sa[left]]]--;
                if (!tag[who[sa[left]]]) c--;
                left++;
            }
        }
        printf("%d\n", mh);
    }
    return 0;
}
