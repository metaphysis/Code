// Ceiling Function
// UVa ID: 1738
// Verdict: Accepted
// Submission Date: 2022-11-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct Node {
    int v;
    Node *lc, *rc;
};

Node* nd[64];

bool same(Node* a, Node* b)
{
    if (a->lc == nullptr && b->lc != nullptr) return false;
    if (a->lc != nullptr && b->lc == nullptr) return false;
    if (a->lc != nullptr && b->lc != nullptr)
        if (!same(a->lc, b->lc)) return false;
    if (a->rc == nullptr && b->rc != nullptr) return false;
    if (a->rc != nullptr && b->rc == nullptr) return false;
    if (a->rc != nullptr && b->rc != nullptr)
        if (!same(a->rc, b->rc)) return false;
    return true;
}

void insert(Node* r, int v)
{
    if (v < r->v)
    {
        if (r->lc != nullptr) insert(r->lc, v);
        else
        {
            r->lc = new Node;
            r->lc->v = v;
            r->lc->lc = nullptr;
            r->lc->rc = nullptr;
        }
    }
    else
    {
        if (r->rc != nullptr) insert(r->rc, v);
        else
        {
            r->rc = new Node;
            r->rc->v = v;
            r->rc->lc = nullptr;
            r->rc->rc = nullptr;
        }
    }
}

void erase(Node* r)
{
    if (r->lc != nullptr) erase(r->lc);
    if (r->rc != nullptr) erase(r->rc);
    delete r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, k;
    while (cin >> n >> k)
    {
        for (int i = 0; i < n; i++)
        {
            nd[i] = new Node;
            cin >> nd[i]->v;
            nd[i]->lc = nd[i]->rc = nullptr;
            for (int j = 1, v; j < k; j++)
            {
                cin >> v;
                insert(nd[i], v);
            }
        }
        int answer = 0;
        for (int i = 0; i < n; i++)
        {
            bool flag = true;
            for (int j = 0; j < i; j++)
                if (same(nd[i], nd[j]))
                {
                    flag = false;
                    break;
                }
            if (flag) answer++;
        }
        for (int i = 0; i < n; i++) erase(nd[i]);
        cout << answer << '\n';
    }
    return 0;
}
