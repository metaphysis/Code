struct interval
{
    int low, high;
};

struct node
{
    interval i;
    int max;
    node *left, *right;
};

node* getNode(interval i)
{
    node *nd = new node;
    nd->i = i;
    nd->max = i.high;
    nd->left = nd->right = NULL;
    return nd;
}

node* insert(node *root, interval i)
{
    if (root == NULL) return getNode(i);
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

bool query(node *root, interval i)
{
    if (root == NULL) return false;
    if (isOverlapped(root->i, i)) return true;
    if (root->left != NULL && root->left->max >= i.low)
        return query(root->left, i);
    return query(root->right, i);  
}

