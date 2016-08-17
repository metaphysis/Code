// Tree
// UVa ID: 548
// Verdict: Accepted
// Submission Date: 2016-08-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

struct treenode
{
    int value;
    treenode *parent, *leftchild, *rightchild;
};

int min_sum = 100000000, min_value = 10000;

treenode* recover(vector<int>& in, int start1, int length1, vector<int>& post, int start2, int length2)
{
    if (length1 == 0)
        return NULL;

    int root_value = post[start2 + length2 - 1];
    
    int end = start1 + length1;
    int i = 0;
    for (; i < end; i++)
        if (in[i + start1] == root_value)
            break;
            
    treenode *root = new treenode;

    root->value = root_value;
    root->leftchild = recover(in, start1, i, post, start2, i);
    root->rightchild = recover(in, start1 + i + 1, length1 - i - 1, post, start2 + i, length2 - i - 1);
    
    if (root->leftchild != NULL)
        root->leftchild->parent = root;
    if (root->rightchild != NULL)
        root->rightchild->parent = root;

    return root;
}

void traversal(treenode* current, int sum)
{
    if (current == NULL)
        return;

    if (current->leftchild == NULL && current->rightchild == NULL)
    {
        if (min_sum > sum + current->value)
        {
            min_sum = sum + current->value;
            min_value = current->value;
        }
        else if (min_sum == sum + current->value)
        {
            min_value = min(min_value, current->value);
        }
    }
    else
    {
        traversal(current->leftchild, sum + current->value);
        traversal(current->rightchild, sum + current->value);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string inorder, postorder;
    while (getline(cin, inorder), getline(cin, postorder))
    {
        vector<int> in, post;
        
        int number;
        istringstream iss(inorder);
        while (iss >> number)
            in.push_back(number);
        
        iss.clear();
        iss.str(postorder);
        while (iss >> number)
            post.push_back(number);

        min_sum = 100000000;
        min_value = 10000;
        traversal(recover(in, 0, in.size(), post, 0, post.size()), 0);

        cout << min_value << '\n';
    }
    
	return 0;
}
