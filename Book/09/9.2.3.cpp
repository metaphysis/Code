#include <iostream>
#include <vector>

using namespace std;

// 顶点最大数目为1000。
const int MAX_V = 1000;

int main(int argc, char *argv[])
{
    // 声明存储顶点邻接表的vecotr，顶点序号从1开始计数。
    vector<vector<int>> edges(MAX_V + 1);

    // 如果图数据中边可能重复给出但不需要重复的边，可以使用set来存储。
    // vector<set<int>> edges(MAX_V + 1);

    // 如果边的数目较多且不对边进行增删操作，可以使用list来存储。
    // list<list<int>> edges(MAX_V + 1);

    // n为顶点数目，m为边的数目，from为起始顶点，to为终止顶点。
    int n, m, from, to;

    // 逐条边读入，将其添加到邻接表中。如果是无向图，则边为双向，在建立邻接表
    // 时需要正反两个方向共两条边。如果是有向图，则只需添加指定方向的边。
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> from >> to;
        edges[from].push_back(to);
        edges[to].push_back(from);
    }

    // 输出邻接表。
    for (int i = 1; i <= n; i++)
        if (edges[i].size() > 0)
        {
            cout << i;
            for (int j = 0; j < edges[i].size(); j++)
                cout << ' ' << edges[i][j];
            cout << '\n';
        }

    return 0;
}
