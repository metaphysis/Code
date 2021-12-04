// value记录各个变量的取值。
vector<int> value;

// components记录位于同一个强连通分支内的顶点。
vector<vector<int>> components;

// 获取某个变量的取值。需要注意的是，同一个变量，对应两个顶点，两个顶点的取值总是相反的。
int getValue(int idx)
{
    int x = (idx & 1) ? (idx ^ 1) : idx;
    if (value[x] == -1) return -1;
    return (idx & 1) ? !value[x] : value[x];
}

// 按拓扑排序的逆序为变量赋值。
void setValue()
{
    // 由于Tarjan算法获得的强连通分支按序号从小到大恰为拓扑排序的逆序，因此可以根据各个顶点
    // 所归属的强连通分支序号，将顶点划分到不同的强连通分支中。因为强连通分支从1开始计数，故
    // 在重设component的大小时将其设置为比cscc大1。
    components.assign(cscc + 1, vector<int>());
    for (int i = 0; i < 2 * n; i++)
        components[scc[i]].push_back(i);

    // 初始时假定所有变量均未被赋值。
    value.assign(n, -1);
    for (int i = 1; i <= cscc; i++) {
        // 赋值原则：尽量为同一强连通分支内的变量赋予真值。
        int boolean = 1;
        // 检查是否存在冲突。存在冲突是指在之前已经为此变量赋值，且其值为假，
        // 或者从此变量出发的边所到达的变量其取值为假，根据对偶性，
        // 有向边连接的顶点其取值应该相同。
        for (auto u : components[i]) {
            if (getValue(u) == 0) boolean = 0;
            for (auto v : g[u])
                if (getValue(v) == 0) {
                    boolean = 0;
                    break;
                }
            // 存在冲突则表明只能为当前强连通分支内的顶点取假值。
            if (boolean == 0) break;
        }
        // 根据取值为该强连通分支中的顶点赋值。注意同一变量所对应的两个顶点其取值相反。
        for (auto u : components[i])
            if (u & 1) value[u ^ 1] = !boolean;
            else value[u] = boolean;
    }
}
