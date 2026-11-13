[UVa 230 Borrowers](https://blog.csdn.net/metaphysis/article/details/161207211)

## 题目分析

这道题模拟图书馆的图书借还系统。图书馆有一个藏书目录，包含每本书的标题和作者。初始时所有书都在书架上。系统需要处理三种操作：

- **`BORROW title`**：借出指定书名的书
- **`RETURN title`**：归还指定书名的书（归还的书暂存在一个待上架列表中）
- **`SHELVE`**：将当前所有归还的书按规则放回书架，并输出放置指令

图书的排序规则是：**先按作者名排序，作者相同则按书名排序**（使用 `ASCII` 字典序）。

对于每本归还的书，需要找到在排序后的书架上，它应该放在哪本书 **之后**。如果它应放在书架的最前面（即没有比它更靠前的书在书架上），则输出 `Put "title" first`。

## 解题思路

1. **存储书籍信息**：定义一个结构体存储每本书的索引、书名、作者以及是否被借出。一开始所有书都在书架上，所以 `borrowed` 初值为 `false`。

2. **建立排序索引**：读取初始藏书目录后，按 **作者 → 书名** 的规则对书籍数组进行排序。排序后，记录每本书在排序数组中的位置（索引），便于后续查找。

3. **映射关系**：使用一个 `map<string, int>` 将书名映射到它在排序数组中的索引，方便通过书名快速定位书籍。

4. **处理操作**：
   - `BORROW`：将对应书籍的 `borrowed` 标记为 `true`（表示该书从书架上被拿走）。
   - `RETURN`：将对应书籍的信息保存到 `returned` 向量中（暂时不上架）。
   - `SHELVE`：对 `returned` 中的书按规则排序，然后依次为每本书寻找它在书架上应放置的位置：
     - 从该书在排序数组中的位置向前查找，找到第一本 **仍在书架上**（即 `borrowed == false`）的书。
     - 如果找到，输出 `Put "title" after "pre_title"`。
     - 如果没找到（即前面所有书都被借走了），输出 `Put "title" first`。
     - 然后将这本书的 `borrowed` 标记为 `false`（放回书架）。
   - 每次 `SHELVE` 结束后，清空 `returned` 向量，并输出 `END`。

5. **输入终止**：当遇到单独的 `END` 行时，整个程序结束。

## 代码实现

```cpp
// Borrowers
// UVa ID: 230
// Verdict: Accepted
// Submission Date: 2016-05-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 定义书籍结构体
struct book {
    int index;          // 在排序数组中的位置索引
    bool borrowed;      // 是否已被借出
    string title, author;   // 书名和作者
    
    // 重载小于运算符，用于排序，先按作者排序，作者相同按书名排序
    bool operator<(book x) const {
        if (author != x.author) return author < x.author;
        else return title < x.title;
    }
};

vector<book> books, returned;   // books: 所有书籍，returned: 待上架书籍

int main() {
    string line;
    
    // 读取初始藏书目录，直到遇到 "END"
    while (getline(cin, line) && line != "END") {
        // 查找书名结束的引号位置
        int index = line.find('\"', 1);
        // 提取书名（位于第一个引号之后，第二个引号之前）
        string title = line.substr(1, index - 1);
        // 提取作者（位于第二个引号之后，跳过 " by " 共5个字符）
        string author = line.substr(index + 5);
        
        book aBook;
        aBook.title = title;
        aBook.author = author;
        books.push_back(aBook);
    }
    
    // 按作者和书名排序
    sort(books.begin(), books.end());
    
    // 建立书名到排序后索引的映射
    map<string, int> indexer;
    for (int i = 0; i < books.size(); i++) {
        books[i].index = i;
        books[i].borrowed = false;
        indexer.insert(make_pair(books[i].title, i));
    }
    
    // 处理后续的操作命令
    while (getline(cin, line) && line != "END") {
        // 借书操作
        if (line[0] == 'B') {
            string title = line.substr(8, line.length() - 9);
            books[indexer[title]].borrowed = true;
        }
        // 还书操作
        else if (line[0] == 'R') {
            string title = line.substr(8, line.length() - 9);
            returned.push_back(books[indexer[title]]);
        }
        // 上架操作
        else {
            // 将要上架的书籍按规则排序
            sort(returned.begin(), returned.end());
            
            // 依次处理每本待上架的书
            for (int i = 0; i < returned.size(); i++) {
                bool found = false;
                // 从该书在排序数组中的位置向前查找，找到第一本仍在书架上的书
                for (int j = returned[i].index; j >= 0; j--)
                    if (books[j].borrowed == false) {
                        cout << "Put \"" << returned[i].title << "\" after \"";
                        cout << books[j].title << "\"" << endl;
                        found = true;
                        break;
                    }
                    
                // 如果前面没有书在书架上，则放在最前面
                if (found == false)
                    cout << "Put \"" << returned[i].title << "\" first" << endl;
                
                // 将该书标记为已上架
                books[returned[i].index].borrowed = false;
            }
            
            // 输出本次 SHELVE 结束标记
            cout << "END" << endl;
            
            // 清空待上架列表
            returned.clear();
        }
    }
    
    return 0;
}
```
