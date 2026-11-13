[UVa 221 Urban Elevations](https://blog.csdn.net/metaphysis/article/details/161084594)

## 题目分析

在城市的南部正射投影中，建筑物的可见性取决于其南面是否被其他建筑物遮挡。每个建筑物可以抽象为一个长方体，由西南角坐标 $(x, y)$、宽度 $w$（东西方向）、深度 $d$（南北方向）和高度 $h$ 描述。

**可见性判定条件**：建筑物的南面在投影中有**严格正面积**，即至少有一段区间没有被任何比它更靠南且高度不小于它的建筑物遮挡。

## 解题思路

1. **坐标离散化**：将所有建筑物的左边界 $x$ 和右边界 $x + w$ 收集起来，排序去重。每两个相邻坐标之间的中点可以代表一个小区间，只需检查这些中点即可判定整个建筑是否可见。

2. **排序**：按 $x$ 坐标升序排列，$x$ 相同时按 $y$ 坐标升序排列，保证输出顺序符合要求。

3. **可见性判定**：
   - 对于建筑 $i$，遍历每个离散区间中点 $m$；
   - 如果 $m$ 在建筑 $i$ 的 $x$ 范围内，则检查是否存在比 $i$ 更靠南（$y$ 更小）且高度不小于 $i$ 的建筑也覆盖该中点；
   - 若存在这样的建筑，则该中点被遮挡；否则该中点可见；
   - 只要有一个中点可见，建筑 $i$ 即为可见。

4. **输出**：按题目要求的顺序输出可见建筑的编号。

## 代码

```cpp
// Urban Elevations
// UVa ID: 221
// Verdict: Accepted
// Submission Date: 2018-12-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 建筑物结构体
struct building {
    int index;          // 建筑物编号
    double left, bottom, width, depth, height;  // 坐标和尺寸
    
    // 排序规则：按 x 坐标升序，x 相同时按 y 坐标升序
    bool operator<(const building &b) const {
        if (left != b.left) return left < b.left;
        return bottom < b.bottom;
    }
};

int main() {
    int n, cases = 0;
    while (cin >> n, n) {
        vector<building> bs(n);      // 存储所有建筑物
        vector<double> xs;           // 存储所有 x 坐标边界
        
        // 读入数据
        for (int i = 0; i < n; i++) {
            cin >> bs[i].left >> bs[i].bottom >> bs[i].width >> bs[i].depth >> bs[i].height;
            bs[i].index = i + 1;                       // 编号从 1 开始
            xs.push_back(bs[i].left);                  // 收集左边界
            xs.push_back(bs[i].left + bs[i].width);    // 收集右边界
        }
        
        // 输出格式控制：两个测试用例之间输出空行
        if (cases++) cout << '\n';
        
        // 输出地图标题
        cout << "For map #" << cases;
        cout << ", the visible buildings are numbered as follows:\n";
        
        // 排序建筑物
        sort(bs.begin(), bs.end());
        
        // 坐标离散化：排序并去重
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        
        // 遍历所有建筑物，判定可见性
        for (int i = 0, printed = 0; i < n; i++) {
            bool visible = false;
            
            // 遍历每个离散区间（取中点代表整个区间）
            for (int j = 0; j < xs.size() - 1; j++) {
                double middle = (xs[j] + xs[j + 1]) / 2;      // 区间中点
                
                // 检查中点是否在当前建筑物的 x 范围内
                if (bs[i].left <= middle && bs[i].left + bs[i].width >= middle) {
                    bool covered = false;
                    
                    // 检查是否有更靠南且更高的建筑物覆盖该中点
                    for (int k = 0; k < n; k++)
                        // 建筑物 k 覆盖该中点
                        if (bs[k].left <= middle && bs[k].left + bs[k].width >= middle)
                            // 建筑物 k 更靠南且高度不低于当前建筑物
                            if (bs[k].bottom < bs[i].bottom && bs[k].height >= bs[i].height) {
                                covered = true;
                                break;
                            }
                    
                    // 如果没有被遮挡，则当前建筑物可见
                    if (!covered) {
                        visible = true;
                        break;
                    }
                }
            }
            
            // 输出可见建筑物的编号
            if (visible) {
                if (printed++) cout << ' ';
                cout << bs[i].index;
            }
        }
        cout << '\n';
    }
    
    return 0;
}
```

