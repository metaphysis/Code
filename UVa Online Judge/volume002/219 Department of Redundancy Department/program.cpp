// Department of Redundancy Department
// UVa ID: 219
// Verdict: Accepted
// Submission Date: 2025-10-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_N = 105; // 最大FD数量
bool hasRedundant; // 标记当前组是否存在冗余FD
int n; // FD数量
int lhsMask[MAX_N], rhsMask[MAX_N]; // 每个FD的左右部字段掩码
int path[MAX_N], visited[MAX_N]; // 记录推导路径和访问标记
// 解析输入字符串，转换为掩码形式
void parseFD(char* str, int idx) {
    bool isRight = false; // 是否遇到->符号，进入右部解析
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            if (isRight)
                rhsMask[idx] |= (1 << (str[i] - 'A')); // 设置右部对应位
            else
                lhsMask[idx] |= (1 << (str[i] - 'A')); // 设置左部对应位
        } else if (str[i] == '-') {
            isRight = true; // 遇到->，开始解析右部
            i++; // 跳过下一个字符'>'
        }
    }
}
// 初始化：读取输入并解析
void initialize() {
    char inputStr[MAX_N];
    hasRedundant = true; // 初始假设存在冗余
    memset(lhsMask, 0, sizeof(lhsMask));
    memset(rhsMask, 0, sizeof(rhsMask));
    for (int i = 0; i < n; i++) {
        scanf("%s", inputStr);
        parseFD(inputStr, i);
    }
}
// 输出找到的冗余FD及其推导路径
void outputRedundantFD(int idx) {
    printf("     FD %d is redundant using FDs:", idx + 1);
    for (int i = 0; path[i] != -1; i++)
        printf(" %d", path[i]);
    printf("\n");
}
// 检查当前字段集合是否能推导出目标FD的右部（不使用目标FD）
bool canDerive(int currentSet, int targetIdx) {
    int used[MAX_N];
    memset(used, 0, sizeof(used));
    while (true) {
        bool noChange = true; // 标记是否无法继续扩展
        for (int i = 0; i < n; i++) {
            if (used[i] || visited[i]) // 跳过已使用或标记为忽略的FD
                continue;
            if ((currentSet & lhsMask[i]) != lhsMask[i]) // 检查左部是否满足
                continue;
            used[i] = 1;
            currentSet |= rhsMask[i]; // 扩展当前字段集合
            noChange = false;
        }
        if (noChange) break; // 无法继续扩展，退出循环
    }
    // 检查是否包含目标右部
    return (currentSet | rhsMask[targetIdx]) != currentSet;
}
// DFS搜索推导路径
bool searchPath(int depth, int currentSet, int targetIdx) {
    path[depth] = -1; // 路径结束标记
    // 若当前集合已包含目标右部，则找到路径
    if ((currentSet & rhsMask[targetIdx]) == rhsMask[targetIdx])
        return true;
    // 若无法继续推导，剪枝
    if (canDerive(currentSet, targetIdx))
        return false;
    // 尝试应用每个未使用的FD
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        if ((currentSet & lhsMask[i]) != lhsMask[i]) continue; // 左部不满足
        if ((currentSet | rhsMask[i]) == currentSet) continue; // 右部已包含
        visited[i] = 1;
        if (searchPath(depth, currentSet, targetIdx)) // 不选择当前FD
            return true;
        path[depth] = i + 1; // 记录当前FD编号（从1开始）
        if (searchPath(depth + 1, currentSet | rhsMask[i], targetIdx)) // 选择当前FD
            return true;
        visited[i] = 0;
    }
    return false;
}
// 主处理函数：检测每个FD是否冗余
void findRedundantFDs() {
    for (int i = 0; i < n; i++) {
        memset(visited, 0, sizeof(visited));
        visited[i] = 1; // 标记当前FD为忽略
        if (searchPath(0, lhsMask[i], i)) { // 从当前FD的左部开始搜索
            outputRedundantFD(i);
            hasRedundant = false; // 标记存在冗余
        }
    }
}
int main() {
    int caseNum = 1;
    while (scanf("%d", &n) == 1 && n) {
        initialize();
        printf("Set number %d\n", caseNum++);
        findRedundantFDs();
        if (hasRedundant)
            printf("     No redundant FDs.\n");
        printf("\n");
    }
    return 0;
}
