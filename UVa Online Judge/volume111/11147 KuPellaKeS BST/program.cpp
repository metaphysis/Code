// KuPellaKeS BST
// UVa ID: 11147
// Verdict: Accepted
// Submission Date: 2022-01-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct node
{
    int key;
    node *lc, *rc;
};

int n, v[1010], sum[1010];

int getDiff(int pivot, int start, int end)
{
    return abs((sum[pivot - 1] - sum[start - 1]) - (sum[end] - sum[pivot]));
}

int getSum(int start, int pivot)
{
    return sum[pivot - 1] - sum[start - 1];
}

void build(node *&u, int start, int end)
{
    if (start > end) return;
    u = new node;
    u->lc = u->rc = nullptr;
    if (start == end)
    {
        u->key = v[start];
        return;
    }
    int r, minDiff = 0x3f3f3f3f, maxSum = -0x3f3f3f3f;
    for (int i = start; i <= end; i++)
    {
        if (i < end && v[i] == v[i + 1]) continue;
        int d = getDiff(i, start, end);
        int s = getSum(start, i);
        if (d < minDiff || (d == minDiff && s > maxSum))
        {
            minDiff = d;
            maxSum = s;
            r = i;
        }
    }
    u->key = v[r];
    build(u->lc, start, r - 1);
    build(u->rc, r + 1, end);
}

void print(node *u)
{
    if (u != nullptr) cout << u->key;
    if (u->lc != nullptr && u->rc != nullptr)
    {
        cout << '(';
        print(u->lc);
        cout << ',';
        print(u->rc);
        cout << ')';
    }
    else if (u->lc != nullptr)
    {
        cout << '(';
        print(u->lc);
        cout << ')';
    }
    else if (u->rc != nullptr)
    {
        cout << '(';
        print(u->rc);
        cout << ')';
    }
}

void erase(node *u)
{
    if (u->lc != nullptr) erase(u->lc);
    if (u->rc != nullptr) erase(u->rc);
    if (u != nullptr) delete u;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Case #" << cs << ": ";
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> v[i];
        sort(v + 1, v + n + 1);
        sum[0] = 0;
        for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + v[i];
        node *root = nullptr;
        build(root, 1, n);
        assert(root != nullptr);
        print(root);
        cout << '\n';
        erase(root);
    }
    return 0;
}
