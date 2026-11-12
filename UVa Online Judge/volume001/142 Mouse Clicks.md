[UVa 142 Mouse Clicks](https://blog.csdn.net/metaphysis/article/details/157463837)

## 题目分析

本题模拟了一个简单的窗口系统，需要处理鼠标点击事件，根据点击位置确定选中的区域（$\texttt{Region}$）或图标（$\texttt{Icon}$）。  

**关键规则**：  
1. 如果点击位置**在某个区域内（包括边界）**，则选中该区域。  
2. 如果点击位置**不在任何区域内**，则选中**距离最近**的可见图标；如果多个图标距离相同，则全部选中。  
3. 区域会遮挡图标，被区域完全覆盖的图标视为不可见。  
4. 区域按输入顺序标记为 `'A'`、`'B'`、…，图标按输入顺序编号为 `1`、`2`、…。  
5. 当多个区域重叠时，后输入的区域视为在前面（即覆盖先输入的区域）。  

**输入格式**：  
- 每行以一个大写字母开头，表示数据类型：  
  - `I` 表示图标，后跟其中心坐标 $(x, y)$。  
  - `R` 表示区域，后跟左上角 $(x_1, y_1)$ 和右下角 $(x_2, y_2)$ 坐标。  
  - `M` 表示鼠标点击，后跟点击坐标 $(x, y)$。  
- 第一个 `M` 之后不会再出现 `I` 或 `R`。  
- 输入以 `#` 结束。  

**输出格式**：  
- 对于每个鼠标点击，输出一行，表示选中的区域或图标：  
  - 区域：输出单个大写字母。  
  - 图标：输出其编号，宽 $3$ 位、右对齐；若多个图标，按编号升序输出。  

---

## 解题思路

1. **数据结构设计**  
   - 图标（$\texttt{Icon}$）：存储其中心坐标、编号、到当前点击点的距离、是否可见。  
   - 区域（$\texttt{Region}$）：存储其矩形范围（左上角和右下角坐标）、字母标签。  

2. **处理流程**  
   - 读入所有 `I` 和 `R` 数据，分别存入向量中。  
   - 遇到 `M` 时：  
     a. **判断是否点击在区域内**：从后往前遍历区域向量（后输入的在前），若点击坐标在某个矩形内（含边界），则选中该区域，输出其标签，并跳过后续图标处理。  
     b. **若不在任何区域内**：  
        - 计算每个图标到点击点的**欧几里得距离平方**（避免开方，比较时等价）。  
        - 判断每个图标是否可见：若其中心被任何一个区域覆盖，则不可见。  
        - 对图标按**可见性优先、距离次之、编号最小**排序。  
        - 输出所有可见且距离等于最小距离的图标编号（按格式右对齐、宽 $3$ 位）。  

3. **注意事项**  
   - 区域遮挡关系：后输入的区域在前，因此判断图标可见性时应遍历所有区域，只要被任意一个区域覆盖即不可见。  
   - 图标距离计算：使用平方距离即可，无需开方。  
   - 输出格式：图标编号需右对齐、占 $3$ 位，多个图标按编号升序排列（排序已保证）。  

---

## 代码实现

```cpp
// Mouse Clicks
// UVa ID: 142
// Verdict: Accepted
// Submission Date: 2016-01-21
// UVa Run Time: 0.012s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct icon {
    int leftX, topY;
    int label;
    int distance;
    int visible;
};
    
struct region {
    int leftX, topY, rightX, bottomY;
    char label;
};

// 图标排序比较规则
bool operator<(const icon& a, const icon& b) {
    if (a.visible == b.visible) {
        if (a.distance == b.distance) return a.label < b.label;
        else return a.distance < b.distance;
    } else return a.visible > b.visible;
}

int main() {
    string line;
    string category;
    int leftX, topY, rightX, bottomY;
    vector<icon> icons;
    vector<region> regions;
    int indexI = 1, indexR = 1;
    while (getline(cin, line), line != "#") {
        istringstream iss(line);
        iss >> category >> leftX >> topY;
        if (line.find('I') != line.npos) {
            icons.push_back((icon) { leftX, topY, indexI++, 0, 0 });
        } else if (line.find('R') != line.npos) {
            iss >> rightX >> bottomY;
            regions.push_back((region) { leftX, topY, rightX, bottomY, ('A' + indexR++ - 1) });
        } else {
            // 检查鼠标事件是否落在矩形内
            bool inRegion = false;
            for (int i = regions.size() - 1; i >= 0; i--) {
                region r = regions[i];
                if (leftX >= r.leftX && leftX <= r.rightX && topY >= r.topY && topY <= r.bottomY) {
                    cout << r.label << endl;
                    inRegion = true;
                    break;
                }
            }
            // 落在矩形内，不需处理后续图标
            if (inRegion) continue;
            // 计算鼠标和图标的距离
            for (int i = 0; i < icons.size(); i++)
                icons[i].distance =
                    pow(icons[i].leftX - leftX, 2) + pow(icons[i].topY - topY, 2);
            // 设置图标可见性
            for (int i = 0; i < icons.size(); i++) {
                icons[i].visible = 1;
                for (int j = 0; j < regions.size(); j++) {
                    region r = regions[j];
                    if (icons[i].leftX >= r.leftX && icons[i].leftX <= r.rightX
                        && icons[i].topY >= r.topY && icons[i].topY <= r.bottomY) {
                        icons[i].visible = 0;
                        break;
                    }
                }
            }
            // 排序
            sort(icons.begin(), icons.end());
            // 按要求输出图标序号
            for (int i = 0; i < icons.size(); i++)
                if (icons[i].distance == icons[0].distance && icons[i].visible) 
                    cout << setw(3) << right << icons[i].label;
                else break;
            cout << '\n';
        }
    }
	return 0;
}
```
