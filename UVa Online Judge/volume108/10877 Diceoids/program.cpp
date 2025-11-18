// Diceoids
// UVa ID: 10877
// Verdict: Accepted
// Submission Date: 2025-11-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 修正后的面序号定义（根据题目实际定义）：
// 0: 顶面 (Top)     - A
// 1: 前面 (Front)   - B  
// 2: 右侧面 (Right) - C
// 3: 后面 (Back)    - F  ← 注意：F是后面
// 4: 左侧面 (Left)  - E
// 5: 底面 (Bottom)  - D  ← 注意：D是底面

// 预定义所有 24 种旋转的映射关系
// 每种旋转是一个长度为 6 的数组，表示原始面 0-5 分别映射到的新面索引
const int rotations[24][6] = {
    {0, 1, 2, 3, 4, 5}, {0, 2, 3, 4, 1, 5}, {0, 3, 4, 1, 2, 5}, {0, 4, 1, 2, 3, 5},
    {1, 0, 4, 5, 2, 3}, {1, 2, 0, 4, 5, 3}, {1, 5, 2, 0, 4, 3}, {1, 4, 5, 2, 0, 3},
    {2, 0, 1, 5, 3, 4}, {2, 1, 5, 3, 0, 4}, {2, 5, 3, 0, 1, 4}, {2, 3, 0, 1, 5, 4},
    {3, 0, 2, 5, 4, 1}, {3, 2, 5, 4, 0, 1}, {3, 5, 4, 0, 2, 1}, {3, 4, 0, 2, 5, 1},
    {4, 0, 3, 5, 1, 2}, {4, 3, 5, 1, 0, 2}, {4, 5, 1, 0, 3, 2}, {4, 1, 0, 3, 5, 2},
    {5, 1, 4, 3, 2, 0}, {5, 4, 3, 2, 1, 0}, {5, 3, 2, 1, 4, 0}, {5, 2, 1, 4, 3, 0}
};

// 获取一个骰子状物体的规范表示（最小表示）
string getCanonicalForm(vector<int>& dice) {
    string minForm = "999999";
    for (int i = 0; i < 24; i++) {
        string currentForm = "";
        for (int j = 0; j < 6; j++)
            currentForm += to_string(dice[rotations[i][j]]);
        if (currentForm < minForm) minForm = currentForm;
    }
    return minForm;
}

int main() {
    int n;
    while (cin >> n, n) {
        set<string> classes;
        for (int i = 0; i < n; i++) {
            vector<int> dice(6);
            // 输入顺序：A(顶), B(前), C(右), D(底), E(左), F(后)
            // 对应索引：0,    1,    2,    5,    4,    3
            // 但输入是按 A, B, C, D, E, F 的顺序，所以我们需要重新映射
            int a, b, c, d, e, f;
            cin >> a >> b >> c >> d >> e >> f;
            // 根据题目实际定义重新映射：
            dice[0] = a; // A = 顶面
            dice[1] = b; // B = 前面  
            dice[2] = c; // C = 右侧面
            dice[3] = f; // F = 后面  ← 注意：输入的第 6 个是 F，对应后面
            dice[4] = e; // E = 左侧面
            dice[5] = d; // D = 底面  ← 注意：输入的第 4 个是 D，对应底面
            string canonicalForm = getCanonicalForm(dice);
            classes.insert(canonicalForm);
        }
        cout << classes.size() << endl;
    }
    return 0;
}
