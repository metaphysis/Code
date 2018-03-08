void preorder(string postorder, string inorder)
{
    if (postorder.length() == 0)
        return;

    // 找到根结点。
    int root = 0;
    for (; root < inorder.length(); root++)
        if (inorder[root] == postorder.back())
            break;

    // 输出根。
    cout << postorder.back();

    // 在左子树中递归。
    preorder(postorder.substr(0, root), inorder.substr(0, root));

    // 在右子树中递归。
    preorder(postorder.substr(root, postorder.length() - root - 1),
        inorder.substr(root + 1));
}
