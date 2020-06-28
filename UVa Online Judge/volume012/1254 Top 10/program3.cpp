// Top 10
// UVa ID: 1254
// Verdict: Accepted
// Submission Date: 2020-06-26
// UVa Run Time: 0.280s
//
// https://github.com/ackoroa/UVa-Solutions/blob/master/UVa%201254%20-%20Top%2010/src/UVa%201254%20-%20Top%2010.cpp

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

typedef pair < int, int >ii;
typedef vector < int >vi;
struct stnode
{
    vi topTen;
};
typedef vector < stnode > vst;

#define MAXN 200001
char T[MAXN], P[MAXN];
int n, m;
int RA[MAXN], tempRA[MAXN];
int SA[MAXN], tempSA[MAXN];
int c[MAXN], phi[MAXN];

int OWNER[MAXN], WLEN[MAXN], IDX[MAXN];
int WPOS[MAXN], LEXICORDER[MAXN];

void countSort(int k)
{
    int i, sum, maxi = max(300, n);
    memset(c, 0, sizeof c);
    for (i = 0; i < n; i++)
        c[i + k < n ? RA[i + k] : 0]++;
    for (i = sum = 0; i < maxi; i++)
    {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (i = 0; i < n; i++)
        tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    for (i = 0; i < n; i++)
        SA[i] = tempSA[i];
}

void makeSA()
{
    int i, k, r;
    for (i = 0; i < n; i++)
    {
        RA[i] = T[i];
        SA[i] = i;
    }
    for (k = 1; k < n; k <<= 1)
    {
        countSort(k);
        countSort(0);
        tempRA[SA[0]] = r = 0;
        for (i = 1; i < n; i++)
            tempRA[SA[i]] =
                (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
        for (i = 0; i < n; i++)
            RA[i] = tempRA[i];
    }
}

ii strMatch()
{
    int lo = 0, hi = n - 1, mid = lo;
    while (lo < hi)
    {
        mid = (lo + hi) / 2;
        int res = strncmp(T + SA[mid], P, m);
        if (res >= 0)
            hi = mid;
        else
            lo = mid + 1;
    }
    if (strncmp(T + SA[lo], P, m) != 0)
        return ii(-1, -1);
    ii ans;
    ans.first = lo;
    lo = 0;
    hi = n - 1;
    mid = lo;
    while (lo < hi)
    {
        mid = (lo + hi) / 2;
        int res = strncmp(T + SA[mid], P, m);
        if (res > 0)
            hi = mid;
        else
            lo = mid + 1;
    }
    if (strncmp(T + SA[hi], P, m) != 0)
        hi--;
    ans.second = hi;
    return ans;
}

bool topTenCmp(int l, int r)
{
    if (l == r)
        return false;
    else
        l = WPOS[OWNER[SA[l]]], r = WPOS[OWNER[SA[r]]];
    if (WLEN[l] != WLEN[r])
        return WLEN[l] < WLEN[r];
    if (LEXICORDER[l] != LEXICORDER[r])
        return LEXICORDER[l] < LEXICORDER[r];
    return l < r;
}

vi combineTopTen(const vi & l, const vi & r)
{
    vi res = l;
    for (int i = 0; i < (int)r.size(); i++)
    {
        bool dupe = false;
        for (int j = 0; j < (int)res.size(); j++)
        {
            if (OWNER[SA[r[i]]] == OWNER[SA[res[j]]])
            {
                dupe = true;
                break;
            }
        }
        if (dupe)
            continue;

        res.push_back(r[i]);
        for (int i = res.size() - 1; i > 0; i--)
            if (topTenCmp(res[i], res[i - 1]))
            {
                swap(res[i], res[i - 1]);
            }
        if (res.size() > 10)
            res.pop_back();
    }
    return res;
}

// Segment Tree Library: The segment tree is stored like a heap array
void st_build(vst & st, int vertex, int L, int R)
{
    if (L == R)                 // as L == R, either one is fine
        st[vertex].topTen.push_back(L); // store the index
    else
    {                           // recursively compute the values in the left and right subtrees
        int nL = 2 * vertex, nR = 2 * vertex + 1;
        st_build(st, nL, L, (L + R) / 2);
        st_build(st, nR, (L + R) / 2 + 1, R);
        stnode lContent = st[nL], rContent = st[nR];
        st[vertex].topTen = combineTopTen(lContent.topTen, rContent.topTen);
    }
}

void st_create(vst & st)
{                               // if original array size is N,
    // the required segment tree array length is 2*2^(floor(log2(N)) + 1);
    int len = (int)(2 * pow(2.0, floor((log((double)n) / log(2.0)) + 1)));
    st.assign(len, stnode());   // create vector of size `len' and fill it with zeroes
    st_build(st, 1, 0, n - 1);  // recursive build
}

void st_rmq(vst & st, vi & res, int vertex, int L, int R, int i, int j)
{
    if (i > R || j < L)
    {
        res.push_back(-1);
        return;                 // current segment outside query range
    }
    if (L >= i && R <= j)
    {
        res = st[vertex].topTen;        // inside query range
        return;
    }
    // compute the min position in the left and right part of the interval
    vi res1, res2;
    st_rmq(st, res1, 2 * vertex, L, (L + R) / 2, i, j);
    st_rmq(st, res2, 2 * vertex + 1, (L + R) / 2 + 1, R, i, j);

    // return the position where the overall minimum is
    if (res1[0] == -1)
    {
        res = res2;
        return;                 // if we try to access segment outside query
    }
    if (res2[0] == -1)
    {
        res = res1;
        return;                 // same as above
    }
    res = combineTopTen(res1, res2);
}

void st_rmq(vst & st, vi & res, int i, int j)
{                               // function overloading
    return st_rmq(st, res, 1, 0, n - 1, i, j);
}

int N, Q;
char s[MAXN];

int main()
{

    WPOS[0] = 0;
    T[0] = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%s", s);
        strcat(T, s);
        strcat(T, "$");

        OWNER[WPOS[i]] = i;
        WLEN[WPOS[i]] = strlen(s) + 1;
        IDX[WPOS[i]] = i + 1;
        WPOS[i + 1] = WPOS[i] + WLEN[WPOS[i]];
        for (int j = WPOS[i] + 1; j < WPOS[i + 1]; j++)
        {
            WLEN[j] = WLEN[j - 1];
            IDX[j] = IDX[j - 1];
            OWNER[j] = OWNER[j - 1];
        }
    }
    n = strlen(T);

    makeSA();

    for (int i = 0; i < N; i++)
    {
        strncpy(P, T + WPOS[i], WLEN[WPOS[i]]);
        m = WLEN[WPOS[i]];
        ii pos = strMatch();
        LEXICORDER[WPOS[i]] = pos.first;
    }

    vst st;
    st_create(st);

    vi res;
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++)
    {
        scanf("%s", P);
        m = strlen(P);
        ii pos = strMatch();
        res.clear();
        st_rmq(st, res, pos.first, pos.second);

        if (res[0] >= 0)
        {
            for (int i = 0; i < (int)res.size(); i++)
            {
                if (i)
                    printf(" ");
                printf("%d", IDX[SA[res[i]]]);
            }
        }
        else
            printf("-1");
        printf("\n");
    }

    return 0;
}
