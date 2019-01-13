// Avoiding Overlaps
// UVa ID: 11601
// Verdict: Accepted
// Submission Date: 2018-12-27
// UVa Run Time: 1.080s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct interval
{
    int low, high, lowy, highy;
};

struct node
{
    interval i;
    int min, max;
    node *left, *right;
};

node* getNode(interval i)
{
    node *nd = new node;
    nd->i = i;
    nd->min = i.low, nd->max = i.high;
    nd->left = nd->right = NULL;
    return nd;
}

node* insert(node *root, interval i)
{
    if (root == NULL) return getNode(i);
    if (i.low < root->i.low) root->left = insert(root->left, i);
    else root->right = insert(root->right, i);
    if (root->max < i.high) root->max = i.high;
    if (root->min > i.low) root->min = i.low;
    return root;
}

bool isOverlapped(interval i1, interval i2)
{
    if (i1.low < i2.high && i2.low < i1.high &&
        i1.lowy < i2.highy && i2.lowy < i1.highy)
        return true;
    return false;
}

bool query(node *root, interval i)
{
    bool overlapped = false;
    if (root == NULL) return overlapped;
    overlapped |= isOverlapped(root->i, i);
    if (!overlapped && root->left != NULL && root->left->max > i.low)
        overlapped |= query(root->left, i);
    if (!overlapped && root->right != NULL && root->right->min < i.high)
        overlapped |= query(root->right, i);
    return overlapped;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, N;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> N;
        node *root = NULL;
        int area = 0;
        interval r;
        for (int i = 0; i < N; i++)
        {
            cin >> r.low >> r.lowy >> r.high >> r.highy;
            if (query(root, r)) continue;
            if (root == NULL) root = insert(root, r);
            else insert(root, r);
            area += abs(r.low - r.high) * abs(r.lowy - r.highy);
        }
        cout << "Case " << cs << ": " << area << '\n';
    }

    return 0;
}
