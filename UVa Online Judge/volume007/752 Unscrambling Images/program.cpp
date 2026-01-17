// Unscrambling Images
// UVa ID: 752
// Verdict: Accepted
// Submission Date: 2026-01-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 516;  // 最大节点数：对于n=16，最大节点编号略大于256

int main() {
    cin.tie(0); 
    cout.tie(0); 
    ios::sync_with_stdio(false);  // 加速输入输出
    
    int T;  // 测试用例数量
    cin >> T;
    
    for (int cs = 1; cs <= T; ++cs) {  // 处理每个测试用例
        int n;
        cin >> n;
        
        // 读取测试图像编码
        int m;
        cin >> m;
        int test[MAXN];
        memset(test, 0, sizeof test);  // 初始化
        for (int i = 0; i < m; ++i) {
            int k, v;
            cin >> k >> v;
            test[k] = v;  // 节点k的值
        }
        
        // 读取秘密图像编码
        cin >> m;
        int secret[MAXN];
        memset(secret, -1, sizeof secret);  // 初始化为-1，表示不是叶节点
        for (int i = 0; i < m; ++i) {
            int k, v;
            cin >> k >> v;
            secret[k] = v;  // 节点k的值
        }
        
        // 解码秘密图像
        int decoded[MAXN];  // 存储最终图像（按行优先顺序）
        function<void(int, int, int, int, int)> decode = [&](int node, int r, int c, int size, int value) {
            // 如果是叶子节点，更新当前值
            if (~secret[node]) value = secret[node];  // ~x表示x!=-1
            
            // 如果区域大小为1×1，记录到对应位置
            if (size == 1) {
                decoded[test[node]] = value;  // 关键步骤：建立映射
                return;
            }
            
            // 继续划分四个象限
            int half = size / 2;
            decode(4 * node + 1, r, c, half, value);           // 左上
            decode(4 * node + 2, r, c + half, half, value);    // 右上
            decode(4 * node + 3, r + half, c, half, value);    // 左下
            decode(4 * node + 4, r + half, c + half, half, value); // 右下
        };
        
        decode(0, 0, 0, n, -1);  // 从根节点开始
        
        // 输出结果
        cout << "Case " << cs << "\n\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                cout << setw(4) << decoded[i * n + j];  // 按行优先输出
            cout << '\n';
        }
        if (cs < T) cout << '\n';  // 测试用例间空行
    }
    
    return 0;
}
