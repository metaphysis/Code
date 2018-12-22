// 使用递归输出路径。
void findPath1(int u, int v)
{
    if (v != u)
    {
        findPath1(u, parent[v]);
        cout << ' ' << v;
    }
    else
        cout << u;
}

// 使用回溯来输出路径。
void findPath2(int u, int v)
{
    // 声明一个vector，存储路径上顶点的编号。
    vector<int> path;

    // v为终止顶点的序号，u为起始顶点的序号。每次将顶点编号插入到路径的最前端。
    // 然后将当前顶点的编号设置为其父顶点的编号，继续该过程，直到找到起始顶点。
    while (v != u)
    {
        path.insert(path.begin(), v);

        // path.push_back(v);

        v = parent[v];
    }

    // 注意在退出while循环时，v和u相同，但起始顶点u的编号尚未加入，需要
    // 将起始顶点的编号添加进来，这样才能构成从起点到终点的一条完整路径。
    path.insert(path.begin(), u);

    // path.push_back(u);
    // reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++)
    {
        if (i > 0)
            cout << ' ';
        cout << path[i];
    }
    cout << '\n';
}
