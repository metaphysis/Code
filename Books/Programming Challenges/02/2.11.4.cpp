struct interval
{
    int low, high;
};

struct node
{
    interval i;
    int max;
    node *leftNode, *rightNode;
};

node* getNode(interval i)
{
    node *nd = new node;
    nd->i = i;
    nd->max = i.high;
    nd->leftNode = nd->rightNode = NULL;
    return nd;
}

node* insert(node *root, interval i)
{
    if (root == NULL) return getNode(i);
    if (i.low < root->i.low) root->leftNode = insert(root->leftNode, i);
    else root->rightNode = insert(root->rightNode, i);
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
    if (root->leftNode != NULL && root->leftNode->max >= i.low)
        return query(root->leftNode, i);
    return query(root->rightNode, i);  
}

