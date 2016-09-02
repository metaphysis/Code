// The New Villa
// UVa ID: 321
// Verdict: Accepted
// Submission Date: 2016-09-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

const int MAX_V = 102050, BASE = 10000;

int r, d, s, from, to, cases = 0;
int vertex[MAX_V], visited[MAX_V], parent[MAX_V];
int connected[16][16], switchs[16][16];
map<int, set<int>> edges;

// 表示当前所在房间及灯亮灭状态。
struct state
{
    int room, light;
};

// 构建显式有向图。
void read()
{
    // 重置门及开关数据。
    memset(connected, 0, sizeof(connected)), memset(switchs, 0, sizeof(switchs));

    // 读入门数据。
    for (int i = 1; i <= d; i++)
    {
        cin >> from >> to;
        connected[from][to] = connected[to][from] = 1;
    }

    // 读入开关数据。
    for (int i = 1; i <= s; i++)
    {
        cin >> from >> to;
        switchs[from][to] = 1;
    }

    edges.clear(), memset(visited, 0, sizeof(visited));

    // 从初始状态开始构建显式图。
    queue<state> unvisited;
    unvisited.push((state){1, 1}), visited[BASE + 1] = 1;

    while (!unvisited.empty())
    {
        state current = unvisited.front();
        unvisited.pop();

        int current_room = current.room, current_light = current.light;
        int current_status = current_room * BASE + current_light;

        for (int next_room = 1; next_room <= r; next_room++)
        {
            // 查看是否可以进入亮灯的房间。
            bool lighted = (current_light & (1 << (next_room - 1))) > 0;
            if (lighted && connected[current_room][next_room])
            {
                int next_status = next_room * BASE + current_light;
                edges[current_status].insert(next_status);
                if (!visited[next_status])
                {
                    visited[next_status] = 1;
                    unvisited.push((state){next_room, current_light});
                }
            }

            // 将当前房间内开关所控制的灯打开或关闭，不能关闭所在房间的灯。
            if (next_room != current_room && switchs[current_room][next_room])
            {
                // 开关所控制的房间灯是关的，打开该房间的灯，否则关闭该房间的灯。
                int next_light = current_light | (1 << (next_room - 1));
                if ((current_light & (1 << (next_room - 1))) > 0)
                    next_light = current_light & (~(1 << (next_room - 1)));

                // 将所在房间和灯的亮灭状态散列成一个唯一的整数。
                // 添加边并将未访问的结点添加到队列中。
                int next_status = current_room * BASE + next_light;
                edges[current_status].insert(next_status);
                if (!visited[next_status])
                {
                    visited[next_status] = 1;
                    unvisited.push((state){current_room, next_light});
                }
            }
        }
    }
}

void bfs()
{
    // 设置起始顶点和结束顶点。
    from = BASE + 1, to = r * BASE + (1 << (r - 1));
    
    // 初始化父结点信息和访问标记信息。
    memset(parent, 0, sizeof(parent)), memset(visited, 0, sizeof(visited));

    // 使用队列进行广度优先遍历。
    queue<int> unvisited;
    unvisited.push(from), visited[from] = 1, parent[from] = 1;

    while (!unvisited.empty())
    {
        int current = unvisited.front();
        unvisited.pop();

        // 当遍历遇到终止状态时退出。
        if (current == to) break;

        // 遍历与当前状态相连接的其他状态。
      for (auto edge:edges[current])
            if (!visited[edge])
            {
                visited[edge] = true;
                parent[edge] = current;
                unvisited.push(edge);
            }
    }
}

void print()
{
    cout << "Villa #" << ++cases << '\n';

    // 如果终止结点的父域为空，则不存在路径从起始状态到达要求的终止状态。
    if (!parent[to])
        cout << "The problem cannot be solved.\n";
    else
    {
        // 构建从起始状态到达终止状态的最短路径。
        vector<int> walk;
        while (to != from) walk.insert(walk.begin(), to), to = parent[to];
        walk.insert(walk.begin(), from);

        cout << "The problem can be solved in " << (walk.size() - 1) << " steps:\n";

        // 将路径转换为操作步骤。
        for (int i = 1; i < walk.size(); i++)
        {
            int last_room = walk[i - 1] / BASE, last_light = walk[i - 1] % BASE;
            int current_room = walk[i] / BASE, current_light = walk[i] % BASE;

            // 每次只有一种操作，要么关闭或打开某个房间的灯，要么进入另外一个房间。
            if (last_room == current_room)
            {
                if (last_light > current_light)
                    cout << "- Switch off light in room ";
                else
                    cout << "- Switch on light in room ";

                // 查找灯的状态发生改变的房间。
                int status = last_light ^ current_light, rooms = 0;
                while (status > 0) status >>= 1, rooms++;
                cout << rooms << ".\n";
            }
            else
                cout << "- Move to room " << current_room << ".\n";
        }
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> r >> d >> s)
    {
        if (r == 0) break;
        read(), bfs(), print();
    }

    return 0;
}
