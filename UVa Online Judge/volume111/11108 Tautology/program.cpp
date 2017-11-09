// Tautology
// UVa ID: 11108
// Verdict: Accepted
// Submission Date: 2017-11-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode
{
    char action;
    TreeNode *parent, *left, *right;
};

int     idx;
string  symbol;
bool    lookup[5];

void parse(TreeNode *node)
{
    node->action = symbol[idx++];

    if (isupper(node->action)) 
    {
        TreeNode *left = new TreeNode;
        node->left = left;
        left->parent = node;
        parse(left);

        if (node->action != 'N')
        {
            TreeNode *right = new TreeNode;
            node->right = right;
            right->parent = node;
            parse(right);
        }
        else node->right = NULL;
    }
    else
    {
        node->left = NULL;
        node->right = NULL;
    }
}

bool traversal(TreeNode *node)
{
    if (node->left == NULL && node->right == NULL)
        return lookup[node->action - 'p'];

    bool b1 = false, b2 = false;

    if (node->left != NULL) b1 = traversal(node->left);
    if (node->right != NULL) b2 = traversal(node->right);
    
    if (node->action == 'K') return b1 && b2;
    if (node->action == 'A') return b1 || b2;
    if (node->action == 'N') return !b1;
    if (node->action == 'C') return !b1 || b2;
    if (node->action == 'E') return b1 == b2;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> symbol, symbol != "0")
    {
        idx = 0;
        TreeNode *root = new TreeNode;
        parse(root);
        
        bool flag = true;
        for (int i = 0; i <= 1; i++)
            for (int j = 0; j <= 1; j++)
                for (int k = 0; k <= 1; k++)
                    for (int l = 0; l <= 1; l++)
                        for (int m = 0; m <= 1; m++)
                        {
                            lookup[0] = i, lookup[1] = j, lookup[2] = k, lookup[3] = l, lookup[4] = m;
                            if (!(flag = traversal(root)))
                                goto print;
                        }

        print:
        if (flag) cout << "tautology\n";
        else cout << "not\n";

        delete root;
    }

    return 0;
}
