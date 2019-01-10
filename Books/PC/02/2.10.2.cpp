void postorder(string preorder, string inorder)
{
    if (preorder.length() == 0)
        return;

    // 找到根结点。
    int root = 0;
    for (; root < inorder.length(); root++)
        if (inorder[root] == preorder.front())
            break;

    // 在左子树中递归。
    postorder(preorder.substr(1, root), inorder.substr(0, root));

    // 在右子树中递归。
    postorder(preorder.substr(root + 1), inorder.substr(root + 1));

    // 输出根。
    cout << preorder.front();
}
