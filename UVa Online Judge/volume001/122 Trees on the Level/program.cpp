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

struct node
{
	struct node *parent;
	struct node *childLeft, *childRight;
	int value;
};

bool noComplete, printWhitespace;
int cache[MAXN][MAXN];
int count[MAXN];

void checkComplete(node * current)
{
	if (current->value == TAG)
		noComplete = true;
	if (current->childLeft != NULL)
		checkComplete(current->childLeft);
	if (current->childRight != NULL)
		checkComplete(current->childRight);
}

// 遍历树，检查叶子节点保存的路径和是否为目标值。
void travelTree(node * current, int depth)
{
	cache[depth][count[depth]++] = current->value;
	if (current->childLeft != NULL)
		travelTree(current->childLeft, depth + 1);
	if (current->childRight != NULL)
		travelTree(current->childRight, depth + 1);
}

void clearTree(node * current)
{
	if (current->childLeft != NULL)
		clearTree(current->childLeft);
	if (current->childRight != NULL)
		clearTree(current->childRight);
	delete current;
}

int main(int argc, char const *argv[])
{
	char c;
	node *root = new node;
	root->childLeft = NULL;
	root->childRight = NULL;
	root->value = TAG;

	while (cin >> c)
	{
		if (c == ' ')
			continue;
		if (c == '(')
		{
			string pairs;
			while (cin >> c, c != ')')
				pairs += c;

			if (pairs.length())
			{
				istringstream iss(pairs);
				int number;
				string positions;
				iss >> number >> c >> positions;

				node *current = root;
				for (int i = 0; i < positions.length(); i++)
				{
					if (positions[i] == 'L')
					{
						if (current->childLeft == NULL)
						{
							node *temp = new node;
							temp->value = TAG;
							temp->childLeft = NULL;
							temp->childRight = NULL;
							current->childLeft = temp;
						}

						current = current->childLeft;
					}
					else
					{
						if (current->childRight == NULL)
						{
							node *temp = new node;
							temp->value = TAG;
							temp->childLeft = NULL;
							temp->childRight = NULL;
							current->childRight = temp;
						}

						current = current->childRight;
					}
				}

				if (current->value > 0)
					current->value = TAG;
				else
					current->value = number;
			}
			else
			{
				noComplete = false;
				checkComplete(root);

				if (noComplete)
					cout << "not complete\n";
				else
				{
					memset(count, 0, sizeof(count));
					travelTree(root, 0);

					printWhitespace = false;
					for (int i = 0; i < MAXN; i++)
						for (int j = 0; j < count[i]; j++)
						{
							if (printWhitespace)
								cout << " ";
							else
								printWhitespace = true;
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
