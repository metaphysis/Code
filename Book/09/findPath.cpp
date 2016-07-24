// 顶点的数目。
const int MAX_VERTICES = 1000;

// 存储各顶点的父顶点信息，由遍历过程进行填充。
int parent[MAX_VERTICES];

// 使用递归来构建路径。
void findPath(int start, int current)
{
    if (current != start)
    {
        findPath(start, parent[current]);
        cout << ' ' << current;
    }
    else
        cout << current;
}

// 声明一个vector，存储路径上顶点的编号
vector<int> path;

// current为终止顶点的序号，start为起始顶点的序号。每次将顶点编号插入到路径的最
// 前端。然后将当前顶点的编号设置为其父顶点的编号，继续该过程，直到找到起始顶点。
while (current != start)
{
    path.insert(path.begin(), current);
    current = parent[current];
}

// 注意在退出while循环时，current和start相同，但起始顶点start的编号尚未加入，需
// 要将起始顶点的编号添加进来，这样才能构成从起点到终点的一条完整路径。
path.insert(path.begin(), current);


