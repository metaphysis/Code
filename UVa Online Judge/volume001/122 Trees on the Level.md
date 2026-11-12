[UVa 122 Trees on the Level](https://blog.csdn.net/metaphysis/article/details/156708913)

## 题目分析

本题要求根据给定的节点描述序列，构建二叉树，并输出该树的**层序遍历**（$\texttt{Level-order Traversal}$）。每个节点由一个正整数和一个路径字符串表示，路径字符串由 `L` 和 `R` 组成，分别表示向左和向右走。例如，`(13, RL)` 表示从根节点开始，先向右再向左到达的节点值为 13。空字符串 `()` 表示一棵树的输入结束。

如果一棵树是**完全指定**（$\texttt{completely specified}$）的，即每个节点都被赋予一个值且仅被赋予一次，则输出其层序遍历结果；否则输出 `not complete`。题目保证每棵树节点数不超过 $256$。

### 输入说明
- 每棵树由若干 `(值, 路径)` 对组成，以 `()` 结尾。
- 输入可能有多棵树，以 $\texttt{EOF}$ 结束。

### 输出说明
- 对于每棵完全指定的树，按层序输出节点值，值之间用空格分隔。
- 否则输出 `not complete`。

---

## 解题思路

我们可以将问题拆解为以下步骤：

1. **建树与存储**  
   使用动态创建节点的方式构建二叉树。每个节点包含左子节点、右子节点和节点值（初始为 0 表示未赋值）。  
   根据路径字符串从根节点开始遍历，若某子节点不存在则创建，最后将值赋给该节点。若该节点已被赋值，则标记为重复赋值（设为 $0$，表示无效）。

2. **检查完全性**  
   对树进行深度优先遍历（$\texttt{DFS}$），若存在节点值为 $0$（未赋值或重复赋值），则树不完全。

3. **层序遍历输出**  
   若树完全，则进行层序遍历。  
   这里采用 $\texttt{DFS}$ 配合深度数组 `cache[depth][...]` 记录每一层的节点值，最后按深度从小到大输出。

4. **内存管理**  
   每处理完一棵树后，递归释放所有节点内存，准备下一棵树。

---

## 算法复杂度
- 时间复杂度：$O(N)$，其中 $N$ 为节点数，每个节点只被访问常数次。
- 空间复杂度：$O(N)$，用于存储树结构和缓存输出。

---

## 代码实现

```cpp
// Trees on the Level
// UVa ID: 122
// Verdict: Accepted
// Submission Date: 2011-12-25
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 本题可以归结为数据结构问题。步骤是建立树结构，检查是否完整，若完整则按深度输出节点。

#include <bits/stdc++.h>

using namespace std;

#define TAG 0
#define MAXN 256

struct node {
	struct node *parent;
	struct node *childLeft, *childRight;
	int value;
};

bool noComplete, printWhitespace;
int cache[MAXN][MAXN];
int cnt[MAXN];

void checkComplete(node * current) {
	if (current->value == TAG) noComplete = true;
	if (current->childLeft != NULL) checkComplete(current->childLeft);
	if (current->childRight != NULL) checkComplete(current->childRight);
}

// 遍历树，检查叶子节点保存的路径和是否为目标值。
void travelTree(node * current, int depth) {
	cache[depth][cnt[depth]++] = current->value;
	if (current->childLeft != NULL) travelTree(current->childLeft, depth + 1);
	if (current->childRight != NULL) travelTree(current->childRight, depth + 1);
}

void clearTree(node * current) {
	if (current->childLeft != NULL) clearTree(current->childLeft);
	if (current->childRight != NULL) clearTree(current->childRight);
	delete current;
}

int main(int argc, char const *argv[]) {
	char c;
	node *root = new node;
	root->childLeft = NULL;
	root->childRight = NULL;
	root->value = TAG;

	while (cin >> c)	{
		if (c == ' ') continue;
		if (c == '(') {
			string pairs;
			while (cin >> c, c != ')') pairs += c;
			if (pairs.length()) {
				istringstream iss(pairs);
				int number;
				string positions;
				iss >> number >> c >> positions;
				node *current = root;
				for (int i = 0; i < positions.length(); i++)	{
					if (positions[i] == 'L') {
						if (current->childLeft == NULL) {
							node *temp = new node;
							temp->value = TAG;
							temp->childLeft = NULL;
							temp->childRight = NULL;
							current->childLeft = temp;
						}
						current = current->childLeft;
					} else {
						if (current->childRight == NULL)	{
							node *temp = new node;
							temp->value = TAG;
							temp->childLeft = NULL;
							temp->childRight = NULL;
							current->childRight = temp;
						}
						current = current->childRight;
					}
				}
				if (current->value > 0)	current->value = TAG;
				else current->value = number;
			} else {
				noComplete = false;
				checkComplete(root);
				if (noComplete)	cout << "not complete\n";
				else {
					memset(cnt, 0, sizeof(cnt));
					travelTree(root, 0);
					printWhitespace = false;
					for (int i = 0; i < MAXN; i++)
						for (int j = 0; j < cnt[i]; j++)	{
							if (printWhitespace) cout << " ";
							else printWhitespace = true;
							cout << cache[i][j];
						}
					cout << endl;
				}
				clearTree(root);
				root = new node;
				root->childLeft = NULL;
				root->childRight = NULL;
				root->value = TAG;
			}
		}
	}
	return 0;
}
```

---

## 示例运行

**输入：**
```
(11, LL) (7, LLL) (8, R)  
(5, ) (4, L) (13, RL) (2, LLR) (1, RRR) (4, RR) ()  
(3, L) (4, R) ()  
```

**输出：**
```
5 4 8 11 13 4 7 2 1
not complete
```

---

## 总结

本题的关键在于正确解析输入、动态建树、检查节点赋值完整性以及按层序输出。代码采用递归方式实现树的遍历与清理，逻辑清晰，适合用作二叉树基本操作的练习。
