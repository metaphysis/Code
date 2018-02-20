// Expressions
// UVa ID: 11234
// Verdict: Accepted
// Submission Date: 2018-02-20
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
    char letter;
    TreeNode *leftchild, *rightchild;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string line;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> line;
        stack<TreeNode*> s;
        for (auto symbol : line)
        {
            TreeNode *node = new TreeNode;
            node->letter = symbol;
            node->leftchild = node->rightchild = NULL;
            if (islower(symbol)) s.push(node);
            else
            {
                TreeNode* a = s.top(); s.pop();
                TreeNode* b = s.top(); s.pop();
                node->leftchild = b;
                node->rightchild = a;
                s.push(node);
            }
        }

        string expression;
        queue<TreeNode*> q;
        q.push(s.top());
        while (!q.empty())
        {
            TreeNode* u = q.front(); q.pop();
            if (u == NULL) continue;
            expression += u->letter;
            q.push(u->leftchild);
            q.push(u->rightchild);
        }
        delete s.top();
        s.pop();
        reverse(expression.begin(), expression.end());
        cout << expression << '\n';
    }

    return 0;
}
