// 2D Representations
// UVa ID: 874
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int child[4];      // 子节点索引，0表示该子项为叶子
    bool leafVal[4];   // 当 child[i]==0 时有效，true 表示满(F)，false 表示空(E)
};

int L;                         // 图像边长
vector<Node> nodes;            // 节点数组，下标从1开始

// 递归填充图像，将四叉树映射到一维像素数组 img (大小为 L*L)
// 参数：当前节点索引，区域左下角坐标 (x, y)，区域边长 size
void fillImage(vector<int>& img, int nodeIdx, int x, int y, int size) {
    int half = size / 2;
    // 四个子区域的偏移量，顺序：左下、右下、左上、右上
    int dx[4] = {0, half, 0, half};
    int dy[4] = {0, 0, half, half};

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nodes[nodeIdx].child[i] == 0) {
            // 叶子：填充该区域全部为对应值
            int val = nodes[nodeIdx].leafVal[i] ? 1 : 0;   // 1=满，0=空
            for (int dy2 = 0; dy2 < half; ++dy2)
                for (int dx2 = 0; dx2 < half; ++dx2)
                    img[(ny + dy2) * L + (nx + dx2)] = val;
        } else {
            // 内部节点：递归处理
            fillImage(img, nodes[nodeIdx].child[i], nx, ny, half);
        }
    }
}

int main() {
    int T;
    cin >> T;
    for (int caseNo = 0; caseNo < T; ++caseNo) {
        cin >> L;
        int N;
        cin >> N;
        nodes.assign(N + 1, Node());

        // 读取每个内部节点的四个子项
        for (int i = 1; i <= N; ++i) {
            for (int j = 0; j < 4; ++j) {
                string token;
                cin >> token;
                if (token == "F" || token == "E") {
                    nodes[i].child[j] = 0;
                    nodes[i].leafVal[j] = (token == "F");
                } else {
                    nodes[i].child[j] = stoi(token);
                    // leafVal 无需设置
                }
            }
        }

        // 生成像素数组，初始为0（空）
        vector<int> image(L * L, 0);
        // 根节点编号为1，整个图像区域为 (0,0) 到 (L,L)
        fillImage(image, 1, 0, 0, L);

        // 游程编码：第一组假设为满(1)
        vector<int> runLength;
        int curVal = 1;   // 当前颜色：1=满
        int cnt = 0;
        for (int y = 0; y < L; ++y) {
            for (int x = 0; x < L; ++x) {
                int pixel = image[y * L + x];
                if (pixel == curVal) {
                    ++cnt;
                } else {
                    runLength.push_back(cnt);
                    curVal = pixel;
                    cnt = 1;
                }
            }
        }
        runLength.push_back(cnt);   // 最后一组

        // 输出当前用例的结果
        for (size_t i = 0; i < runLength.size(); ++i) {
            if (i > 0) cout << ' ';
            cout << runLength[i];
        }
        cout << endl;

        // 两个连续用例之间输出空行
        if (caseNo != T - 1) cout << endl;
    }
    return 0;
}
