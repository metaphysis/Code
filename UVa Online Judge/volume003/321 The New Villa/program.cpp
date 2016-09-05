// The New Villa
// UVa ID: 321
// Verdict: Accepted
// Submission Date: 2016-09-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bitset>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

// 最大顶点数目。
const int MAX_V = 102050;

// 将所在房间和灯的亮灭状态转换为一个唯一的整数进行表示。将房间编号左移指定位数
// 再加上表示所有灯亮灭的状态整数即可唯一标识某个时刻人所在房间及灯的状态。
const int SHIFTS = 10, SHIFTS_MASK = 1023;

// r为房间的数量，d为门的数量，s为开关的数量。
int r, d, s, from, to, cases = 0;

// vertex记录顶点，visited标记顶点是否已被访问，parent记录各顶点的父域。
int vertex[MAX_V], visited[MAX_V], parent[MAX_V];

// connected记录门的连接，switchs记录开关信息。
int connected[16][16], switchs[16][16];

// 以邻接表方式表示图。
map<int, set<int>> edges;

// 表示当前所在房间及灯亮灭状态。使用bitset来表示灯的状态，便于进行操作。
struct state
{
    int room; bitset<10> light;
};

// 构建显式有向图。
void buildGraph()
{
    // 重置门及开关数据。
    memset(connected, 0, sizeof(connected)), memset(switchs, 0, sizeof(switchs));

    // 读入门数据。
    for (int i = 1; i <= d; connected[from][to] = connected[to][from] = 1, i++)
        cin >> from >> to;

    // 读入开关数据。
    for (int i = 1; i <= s; switchs[from][to] = 1, i++)
        cin >> from >> to;


    // 重置相关变量。
    edges.clear(), memset(visited, 0, sizeof(visited));

    // 从初始状态开始构建显式图。
    queue<state> unvisited;
    unvisited.push((state){1, 1}), visited[1 << SHIFTS + 1] = 1;

    // 队列非空继续构建。
    while (!unvisited.empty())
    {
        state current = unvisited.front(); unvisited.pop();
        int room = current.room; bitset<10> light = current.light;
        int status = (room << SHIFTS) | (int)light.to_ulong();
       
        for (int next_room = 1; next_room <= r; next_room++)
        {
            // 查看是否可以进入亮灯的房间。
            if (light.test(next_room - 1) && connected[room][next_room])
            {
                int next_status = (next_room << SHIFTS) | (int)light.to_ulong();
                edges[status].insert(next_status);
                if (!visited[next_status])
                {
                    visited[next_status] = 1;
                    unvisited.push((state){next_room, light});
                }
            }

            // 打开或关闭其他房间的灯，不能关闭所在房间的灯。
            if (next_room != room && switchs[room][next_room])
            {
                // 如果房间的灯是亮的，关闭，否则打开。
                bitset<10> next_light(light); next_light.flip(next_room - 1);

                // 添加边并将未访问的顶点添加到队列中。
                int next_status = (room << SHIFTS) | (int)next_light.to_ulong();
                edges[status].insert(next_status);
                if (!visited[next_status])
                {
                    visited[next_status] = 1;
                    unvisited.push((state){room, next_light});
                }
            }
        }
    }
}

// 广度优先遍历。
void bfs()
{
    // 设置起始状态和终止状态对应的顶点。
    from = (1 << SHIFTS) | 1, to = (r << SHIFTS) | (1 << (r - 1));
    
    // 初始化父域和访问标记。
    memset(parent, 0, sizeof(parent)), memset(visited, 0, sizeof(visited));

    // 压入初始状态，开始遍历。
    queue<int> unvisited;
    unvisited.push(from), visited[from] = 1, parent[from] = 1;
    
    // 队列非空继续遍历。
    while (!unvisited.empty())
    {
        int current = unvisited.front(); unvisited.pop();

        // 当遍历遇到终止状态时退出。
        if (current == to) break;

        // 遍历与当前状态相连接的其他状态。
        for (auto edge : edges[current])
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

    // 如果终止状态的父域为空，则不存在解决方案。
    if (!parent[to])
    {
        cout << "The problem cannot be solved.\n\n";
        return;
    }
    
    // 构建从起始状态到达终止状态的最短路径，逆向查找父域。
    vector<int> walk;
    while (to != from) walk.insert(walk.begin(), to), to = parent[to];
    walk.insert(walk.begin(), from);

    // 输出最少操作步骤。
    cout << "The problem can be solved in " << (walk.size() - 1) << " steps:\n";

    // 将路径转换为操作步骤。
    for (int i = 1; i < walk.size(); i++)
    {
        int last_room = walk[i - 1] >> SHIFTS;
        int last_light = walk[i - 1] & SHIFTS_MASK;
        int room = walk[i] >> SHIFTS, light = walk[i] & SHIFTS_MASK;

        // 每次只有一种操作，要么关闭或打开某个房间的灯，要么进入另外一个房间。
        if (last_room == room)
        {
            // 如果在相同房间，后一状态整数比前一状态整数小，则必定是关闭了某一盏
            // 灯，否则是打开了某一盏灯。
            if (light < last_light)
                cout << "- Switch off light in room ";
            else
                cout << "- Switch on light in room ";

            // 查找灯的状态发生改变的房间。
            int status = last_light ^ light, rooms = 0;
            while (status > 0) status >>= 1, rooms++;
            cout << rooms << ".\n";
        }
        // 进入另一房间。
        else cout << "- Move to room " << room << ".\n";
    }

    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> r >> d >> s)
    {
        if (r == 0) break;
        buildGraph(), bfs(), print();
    }

    return 0;
}
