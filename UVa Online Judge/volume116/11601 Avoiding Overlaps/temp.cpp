struct interval
{
    int low, high;
};

struct itNode
{
    interval i;
    int max;
    itNode *left, *right;
};

itNode *setNode(interval i)
{
    itNode * node = new itNode;
    node->i = i;
    node->max = i.high;
    node->left = node->right = NULL;
}

itNode *insert(itNode *root, interval i)
{
    if (root == NULL) return setNode(i);
    if (i.low < root->i.low) root->left = insert(root->left, i);
    else root->right = insert(root->right, i);
    if (root->max < i.high) root->max = i.high;
    return root;
}

bool isOverlapped(interval i1, interval i2)
{
    if (i1.low <= i2.high && i2.low <= i1.high) return true;
    return false;
}

bool search(itNode *root, interval i)
{
    if (root == NULL) return false;
    if (isOverlapped(root->i, i)) return true;
    if (root->left != NULL && root->left->max >= i.low)
        return search(root->left, i);
    return search(root->right, i);  
}
