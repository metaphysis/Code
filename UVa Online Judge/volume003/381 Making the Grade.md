[UVa 381 Making the Grade](https://blog.csdn.net/metaphysis/article/details/161673558)

## 题目描述

$\texttt{Mr. Chips}$ 有一套简单的评分方案，便于自动计算。你需要编写程序，读取学生的成绩、奖励分数和出勤记录，计算学生的最终成绩，并输出班级的平均绩点（`avg grd pnt`）。

$\texttt{Mr. Chips}$ 的评分规则如下：

1. 所有测验满分 $100$ 分，成绩在 $0$ 到 $100$ 之间。
2. 如果测验次数超过 $2$ 次，则**去掉每个学生的最低一次成绩**后再计算平均分。
3. 计算每个学生的平均分后，计算班级的平均分（`mean`）和标准差（`sd`）。
   - 若计算出的标准差小于 $1$，则用 $1$ 代替标准差用于等级划分。
4. 等级划分标准（未调整前）：
   - 平均分 $\ge$ 平均分 $+$ 标准差：**`A`**
   - 平均分 $\ge$ 平均分 且 $<$ 平均分 $+$ 标准差：**`B`**
   - 平均分 $\ge$ 平均分 $-$ 标准差 且 $<$ 平均分：**`C`**
   - 平均分 $\le$ 平均分 $-$ 标准差：**`D`**
5. 奖励分数调整：每 $2$ 个奖励分，平均分提高 $3$ 个百分点（向上取整到十分位）。例如 $1$ 个奖励分不提高，$4$ 或 $5$ 个奖励分提高 $6$ 个百分点，以此类推。
6. 出勤调整：每 $4$ 次缺勤，降低一个字母等级（`A→B→C→D→F`）。如果全勤（缺勤 $0$ 次），则提高一个字母等级（不能高于 `A`）。
7. 所有计算过程中，$\texttt{Mr. Chips}$ 总是将结果**四舍五入到十分位**。

**平均绩点**计算规则：`A` 计 $4$ 分，`B` 计 $3$ 分，`C` 计 $2$ 分，`D` 计 $1$ 分，`F` 计 $0$ 分。总绩点除以学生数即为班级平均绩点。

## 输入格式

第一行包含整数 $N$（$1 \le N \le 10$），表示 $\texttt{Mr. Chips}$ 的班级数量。

每个班级的第一行包含两个整数 $S$ 和 $T$：
- $S$：学生数（$1 < S < 31$）
- $T$：测验次数（$1 < T < 11$）

接下来 $S$ 行，每行表示一个学生：
- 前 $T$ 个整数为各次测验成绩（$0 \sim 100$）
- 接着一个整数为奖励分数
- 最后一个整数为缺勤次数

## 输出格式

第一行输出 `MAKING THE GRADE OUTPUT`。

接下来 $N$ 行，每行输出一个班级的平均绩点（保留一位小数）。

最后一行输出 `END OF OUTPUT`。

## 样例

输入

```
3
3 2
100 50 2 5
60 60 17 1
20 10 0 5
5
100 80 90 80 90 0 0
80 80 80 80 0 0
50 50 50 50 0 0
100 100 20 20 20 0 0
30 30 30 30 0 0
10
4 79 56 59 89 4 5
100 89 96 79 6 2
80 80 80 76 1 3
76 76 76 76 5 4
58 78 67 75 4 0
100 96 100 95 1 2
47 49 46 45 0 5
67 98 59 87 5 5
23 45 52 54 2 7
78 75 79 79 3 3
```

输出

```
MAKING THE GRADE OUTPUT
3.0
3.2
2.4
END OF OUTPUT
```

## 题目分析

本题的评分流程较为复杂，涉及多个步骤：

1. **原始平均分计算**：若 $T > 2$ 则去掉最低分后求平均，否则直接平均。结果需**四舍五入到十分位**。
2. **班级统计量**：计算所有学生原始平均分的**均值**和**标准差**。若标准差 $< 1$，则视为 $1$。
3. **奖励分调整**：每 $2$ 个奖励分增加 $3$ 个百分点。调整后的平均分仍要**四舍五入到十分位**。
4. **初始等级划分**：根据调整后的平均分与均值、标准差的关系，确定 `A/B/C/D`。
5. **出勤调整**：每缺勤 $4$ 次降一级，全勤（缺勤 $0$ 次）升一级，且等级不能超出 `A` 到 `F` 范围。
6. **绩点计算**：将最终等级转换为绩点（`A:4, B:3, C:2, D:1, F:0`），求和后除以学生数，结果保留一位小数。

**关键细节**：
- 所有“平均分”计算（原始平均、奖励调整后平均）都需要**四舍五入到十分位**。
- 标准差公式：$\textit{sd} = \sqrt{\frac{\sum (x_i - \textit{mean})^2}{S}}$。
- 奖励分调整公式：$\textit{avg}' = \textit{avg} + 3 \times \lfloor \textit{bouns} / 2 \rfloor$。
- 等级调整时注意边界：不能低于 `F`（绩点 $0$），不能高于 `A`（绩点 $4$）。

## 代码实现

```cpp
// Making the Grade
// UVa ID: 381
// Verdict: Accepted
// Submission Date: 2016-07-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct student
{
    double average;
    int bouns, absences, grade;
};

double roundToTenth(double number)
{
    return (int)(number * 10.0 + 0.5) / 10.0;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    vector<student> students;
    int N, S, T;
    cin >> N;

    cout << "MAKING THE GRADE OUTPUT" << endl;
    for (int i = 1; i <= N; i++)
    {
        cin >> S >> T;

        students.clear();
        for (int j = 1; j <= S; j++)
        {
            double lowest = 100.0, sumOfScores = 0.0, score;
            for (int k = 1; k <= T; k++)
            {
                cin >> score;
                sumOfScores += score;
                lowest = min(lowest, score);
            }

            student aStudent;
            cin >> aStudent.bouns >> aStudent.absences;
            if (T > 2) aStudent.average = roundToTenth((sumOfScores - lowest) / (T - 1));
            else aStudent.average = sumOfScores / T;
            students.push_back(aStudent);
        }

        double sumOfPoints = 0.0, mean, sd;
        for (int i = 0; i < students.size(); i++) sumOfPoints += students[i].average;
        mean = roundToTenth(sumOfPoints / S);
        for (int i = 0; i < students.size(); i++) sd += pow(students[i].average - mean, 2);
        sd = roundToTenth(sqrt(sd / S));

        double sumOfGrade = 0;
        for (int i = 0; i < students.size(); i++)
        {
            students[i].average = roundToTenth(students[i].average + 3.0 * (students[i].bouns / 2));

            if (students[i].average >= (mean + sd)) students[i].grade = 4;
            else if (students[i].average >= mean) students[i].grade = 3;
            else if (students[i].average >= (mean - sd)) students[i].grade = 2;
            else students[i].grade = 1;

            if (students[i].absences > 0) students[i].grade -= students[i].absences / 4;
            else students[i].grade++;

            if (students[i].grade < 0) students[i].grade = 0;
            else if (students[i].grade > 4) students[i].grade = 4;

            sumOfGrade += students[i].grade;
        }

        cout << fixed << setprecision(1) << (sumOfGrade / S) << endl;
    }
    cout << "END OF OUTPUT" << endl;

    return 0;
}
```
