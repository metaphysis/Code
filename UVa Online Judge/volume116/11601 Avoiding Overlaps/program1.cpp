// Avoiding Overlaps
// UVa ID: 11601
// Verdict: Accepted
// Submission Date: 2018-12-27
// UVa Run Time: 0.1.090s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct interval
{
    int low, high, lowy, highy;
};

struct itNode
{
    interval i;
    int min, max;
    itNode *left, *right;
};

itNode *setNode(interval i)
{
    itNode *node = new itNode;
    node->i = i;
    node->min = i.low, node->max = i.high;
    node->left = node->right = NULL;
    return node;
}

itNode *insert(itNode *root, interval i)
{
    if (root == NULL) return setNode(i);
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

bool search(itNode *root, interval i)
{
    bool overlapped = false;
    if (root == NULL) return overlapped;
    overlapped |= isOverlapped(root->i, i);
    if (!overlapped && root->left != NULL && root->left->max > i.low)
        overlapped |= search(root->left, i);
    if (!overlapped && root->right != NULL && root->right->min < i.high)
        overlapped |= search(root->right, i);
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
        itNode *root = NULL;
        int area = 0;
        interval r;
        for (int i = 0; i < N; i++)
        {
            cin >> r.low >> r.lowy >> r.high >> r.highy;
            if (search(root, r)) continue;
            if (root == NULL) root = insert(root, r);
            else insert(root, r);
            area += abs(r.low - r.high) * abs(r.lowy - r.highy);
        }
        cout << "Case " << cs << ": " << area << '\n';
    }

    return 0;
}
