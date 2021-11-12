// 2D-Nim
// UVa ID: 10707
// Verdict: Accepted
// Submission Date: 2021-11-08
// UVa Run Time: 0.020s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 使用点来定义一个块。
struct piece {
    int x, y;
    piece (int x = 0, int y = 0): x(x), y(y) {}
    // 位于同一簇内的块，按行序递增排列，若行序相同，按列序递增排列。
    bool operator<(const piece &p) const
    {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
};

// 存储左侧图和右侧图中的簇。
vector<vector<piece>> leftBoard, rightBoard;

int H, W, n, g[110][110];
int offset[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1};
vector<piece> cluster;

// Flood-Fill 算法确定簇。
void dfs(int i, int j)
{
    cluster.push_back(piece(i, j));
    g[i][j] = 0;
    for (int k = 0; k < 4; k++)
    {
        int ni = i + offset[k][0], nj = j + offset[k][1];
        if (ni >= 0 && ni < H && nj >= 0 && nj < W && g[ni][nj])
            dfs(ni, nj);
    }
}

// 将簇按包含块的数量升序排列。
bool cmp(vector<piece> &p1, vector<piece> &p2)
{
    return p1.size() < p2.size();
}

// 将簇旋转 90 度。相对于簇中排序后的第一个块进行旋转。考虑到坐标旋转变换中包含
// 正弦和余弦函数，要使得旋转后的坐标仍为整数，只有当旋转角度是 90 度的整数倍才
// 有可能，因此只需考虑 90 度的旋转即可。类似地，在进行镜像操作时，也只考虑左右
// 镜像和上下镜像变换。
vector<piece> rotate_90(vector<piece> cluster)
{
    vector<piece> rotated;
    int x = cluster.front().x, y = cluster.front().y;
    for (auto p : cluster)
        rotated.push_back(piece(x - (p.y - y), y + (p.x - x)));
    sort(rotated.begin(), rotated.end());
    return rotated;
}

// 左右镜像。
vector<piece> reflect_left_right(vector<piece> cluster)
{
    vector<piece> reflected;
    int x = cluster.front().x, y = cluster.front().y;
    for (auto p : cluster)
        reflected.push_back(piece(p.x, 2 * y - p.y));
    sort(reflected.begin(), reflected.end());
    return reflected;
}

// 上下镜像。
vector<piece> reflect_up_down(vector<piece> cluster)
{
    vector<piece> reflected;
    int x = cluster.front().x, y = cluster.front().y;
    for (auto p : cluster)
        reflected.push_back(piece(2 * x - p.x, p.y));
    sort(reflected.begin(), reflected.end());
    return reflected;
}

// 判断簇 p1 能够通过平移成为簇 p2。
bool equals(vector<piece> p1, vector<piece> p2)
{
    int dx = p1.front().x - p2.front().x, dy = p1.front().y - p2.front().y;
    for (int i = 1; i < p1.size(); i++)
        if (p1[i].x - p2[i].x != dx || p1[i].y - p2[i].y != dy)
            return false;
    return true;
}

// 判断簇 p1 和簇 p2 是否等同。
bool isomorphism(vector<piece> p1, vector<piece> p2)
{
    // 检查簇 p1 通过平移是否能够成为簇 p2。
    if (equals(p1, p2)) return true;
    // 将簇 p1 分别进行左右和上下镜像后再判断是否能够通过平移成为簇 p2。
    if (equals(reflect_left_right(p1), p2)) return true;
    if (equals(reflect_up_down(p1), p2)) return true;
    // 将簇 p1 逆时针旋转 90 度。
    p1 = rotate_90(p1);
    if (equals(p1, p2)) return true;
    if (equals(reflect_left_right(p1), p2)) return true;
    if (equals(reflect_up_down(p1), p2)) return true;
    // 将簇 p1 逆时针继续旋转 90 度。
    p1 = rotate_90(p1);
    if (equals(p1, p2)) return true;
    if (equals(reflect_left_right(p1), p2)) return true;
    if (equals(reflect_up_down(p1), p2)) return true;
    // 将簇 p1 逆时针继续旋转 90 度。
    p1 = rotate_90(p1);
    if (equals(p1, p2)) return true;
    if (equals(reflect_left_right(p1), p2)) return true;
    if (equals(reflect_up_down(p1), p2)) return true;
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        leftBoard.clear();
        rightBoard.clear();

        // 读入数据，通过 Flood-Fill 算法得到块构成的簇。
        cin >> W >> H >> n;
        
        memset(g, 0, sizeof(g));
        for (int i = 0, x, y; i < n; i++)
        {
            cin >> x >> y;
            g[y][x] = 1;
        }
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                if (g[i][j])
                {
                    cluster.clear();
                    dfs(i, j);
                    sort(cluster.begin(), cluster.end());
                    leftBoard.push_back(cluster);
                }

        memset(g, 0, sizeof(g));
        for (int i = 0, x, y; i < n; i++)
        {
            cin >> x >> y;
            g[y][x] = 1;
        }
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                if (g[i][j])
                {
                    cluster.clear();
                    dfs(i, j);
                    sort(cluster.begin(), cluster.end());
                    rightBoard.push_back(cluster);
                }
        
        // 如果左侧图和右侧图的簇数量不等，肯定不可能等同。
        if (leftBoard.size() != rightBoard.size())
        {
            cout << "NO\n";
            continue;
        }
        
        // 按簇中包含块的数量排序。
        sort(leftBoard.begin(), leftBoard.end(), cmp);
        sort(rightBoard.begin(), rightBoard.end(), cmp);
        
        // 逐个簇进行比对，通过旋转，镜像，平移以检查是否能够重合。
        bool flag = true;
        while (leftBoard.size())
        {
            if (leftBoard.front().size() != rightBoard.front().size())
            {
                flag = false;
                break;
            }
            if (leftBoard.front().size() <= 2)
            {
                leftBoard.erase(leftBoard.begin());
                rightBoard.erase(rightBoard.begin());
                continue;
            }

            bool found = false;
            for (int i = 0; i < rightBoard.size() && rightBoard[i].size() == leftBoard.front().size(); i++)
                if (isomorphism(leftBoard.front(), rightBoard[i]))
                {
                    found = true;
                    leftBoard.erase(leftBoard.begin());
                    rightBoard.erase(rightBoard.begin() + i);
                    break;
                }
            if (!found) { flag = false; break; }
        }
        cout << (flag ? "YES\n" : "NO\n");
    }

    return 0;
}
