[UVa 396 Top Dog](https://blog.csdn.net/metaphysis/article/details/161705476)

## 题目描述

你是 $\texttt{TOP-DOG}$（最新军事情报程序）项目的一名绝密政府软件工程师。$\texttt{TOP-DOG}$ 处理从绘制敌方领土和位置到解析总司令的高度加密消息等一切事务。

你需要编写一段软件，从 $\texttt{Orcaattle}$ 数据库中获取所需信息，并将其存储到“平面”文件中，随后发送到磁盘。

### 输入格式

输入包含一个或多个描述，两个连续描述之间有一个空行。每个描述以一行包含描述编号开始，然后是三个用空行分隔的伪文件集合。

- **第一组**：要导出的表名列表（每行一个）
- **第二组**：数据库架构信息，包含每个表的列名、类型和大小（如果是 `VARCHAR`）
  - 每个表以表名开始，后续行包含列名、数据类型和大小（`VARCHAR` 特有）
  - `#` 表示该表没有更多列
  - 数据类型：`VARCHAR`、`INT`、`DATE`、`LONGINT`
- **第三组**：$\texttt{Dispatcher}$ 处理后的实际数据
  - 每行包含表名，然后是每行的数据
  - `<NULL>` 表示空字段

### 输出格式

第一组输出（在描述编号后）：
- 对于每个要导出的表，如果存在于架构中，输出 `SELECT (类型) 列名, ... FROM 表名;`
  - 类型映射：`VARCHAR` 和 `DATE` → `CHAR`，`INT` 和 `LONGINT` → `NUM`
  - 如果表不存在，输出 `<TABLE NOT FOUND>`

第二组输出（空行后）：
- 对于每个表，输出 `表名(列数)(行数)`
- 然后每行列名和数据：`列名 "数据"`（若 `VARCHAR` 大小 > 64，在列名后加 `(大小)`）

### 样例输入

```
1
INTELSYS
GROUPSPI
SYSTEMEL
DEPLOYREG

GROUPSPI
GRCODE INT
GRSUBNET VARCHAR 20
GREGION VARCHAR 25
GRACTION VARCHAR 100
GRREF VARCHAR 100
#
INTELSYS
ISDATE DATE
ISNUM INT
ISGEN LONGINT
ISSUBGEN VARCHAR 25
#
SYSTEMEL
...
...

[数据部分]
```

### 样例输出

```
1
SELECT (CHAR) ISDATE, (NUM) ISNUM, (NUM) ISGEN, (CHAR) ISSUBGEN FROM INTELSYS;
SELECT (NUM) GRCODE, (CHAR) GRSUBNET, (CHAR) GREGION, (CHAR) GRACTION, (CHAR) GRREF FROM GROUPSPI;
<TABLE NOT FOUND>
<TABLE NOT FOUND>

INTELSYS(4)(4)
ISDATE "122922T DEC 94"
ISNUM "1"
ISGEN "2"
ISSUBGEN "ISDATE "1111112 DEC 01""
ISNUM "3"
...
GROUPSPI(5)(0)
SYSTEMEL(6)(1)
SITRANS "342"
...
```

---

## 题目分析

### 问题的本质

这是一个**数据导出与格式转换**问题。需要：
1. 解析数据库架构信息（第二组输入）
2. 生成 $\texttt{SQL}$ 查询语句（第一组输出）
3. 解析实际数据（第三组输入）
4. 按特定格式导出（第二组输出）

### 关键点

- 表名、列名区分大小写
- 数据类型映射：`VARCHAR/DATE` → `CHAR`，`INT/LONGINT` → `NUM`
- `VARCHAR` 大小 $> 64$ 时需要在列名后标注
- 数据行数与架构列数对应
- `<NULL>` 表示空字符串

---
## 参考代码

```cpp
// Top Dog
// UVa ID: 396
// Verdict: Accepted
// Submission Date: 2016-07-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<string> names;                               // 要导出的表名
map<string, vector<vector<string>>> tables;         // 表名 -> 列信息

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        int n = stoi(line);
        cout << n << endl;
        
        names.clear();
        tables.clear();

        // 读取第一组：要导出的表名
        while (getline(cin, line), line.length() > 0)
            names.push_back(line);
        
        // 读取第二组：数据库架构（列信息）
        while (getline(cin, line), line.length() > 0)
        {
            string name = line;
            vector<vector<string>> fields;
            while (getline(cin, line), line != "#")
            {
                istringstream iss(line);
                vector<string> property;
                string block;
                while (iss >> block) 
                    property.push_back(block);
                fields.push_back(property);
            }
            tables[name] = fields;
        }
        
        // 输出第一组：生成 SELECT 语句
        for (auto name : names)
        {
            if (tables.find(name) == tables.end())
                cout << "<TABLE NOT FOUND>" << endl;
            else
            {
                cout << "SELECT ";
                bool first_field = true;
                for (auto field : tables[name])
                {
                    if (first_field) 
                        first_field = false;
                    else 
                        cout << ", ";
                    
                    // 类型映射：INT/LONGINT -> NUM，其他 -> CHAR
                    if (field[1] == "INT" || field[1] == "LONGINT") 
                        cout << "(NUM) ";
                    else 
                        cout << "(CHAR) ";
                    
                    cout << field[0];
                }
                cout << " FROM " << name << ";" << endl;
            }
        }
        
        cout << endl;  // 两组输出之间空行
        
        // 读取第三组：实际数据并输出第二组
        while (getline(cin, line), line.length() > 0)
        {
            string name = line;
            vector<vector<string>> records;
            vector<string> record;
            
            // 读取该表的所有行
            while (getline(cin, line), line != "#")
            {
                if (line == "<NULL>")
                    record.push_back("");
                else
                    record.push_back(line);
                if (record.size() == tables[name].size())
                {
                    records.push_back(record);
                    record.clear();
                }
            }
            
            // 输出表头：表名(列数)(行数)
            cout << name << "(" << tables[name].size() << ")(" << records.size() << ")" << endl;
            
            // 输出每行数据
            for (int i = 0; i < records.size(); i++)
            {
                for (int j = 0; j < records[i].size(); j++)
                {
                    // 列名
                    cout << tables[name][j].front();
                    // VARCHAR 且大小 > 64 时标注大小
                    if (tables[name][j][1] == "VARCHAR" && stoi(tables[name][j][2]) > 64)
                        cout << "(" << tables[name][j][2] << ")";
                    cout << " ";
                    // 数据
                    cout << "\"" << records[i][j] << "\"";
                    cout << endl;
                }
            }
        }
    }
    
    return 0;
}
```
