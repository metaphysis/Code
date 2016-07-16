// Stacking Boxes
// UVa ID: 103
// Verdict: Accepted
// Submission Date: 2011-10-17
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 该问题可以归结为求最长上升子序列的问题。

#include <algorithm>
#include <iostream>

using namespace std;

#define MAXD 10
#define MAXN 30
#define END (-1)

struct box
{
public:
	int dimensionality[MAXD];
	int dimensions;
	int index;

	bool operator<(const box &other) const
	{
		for (int i = 0; i < dimensions; i++)
			if (dimensionality[i] != other.dimensionality[i])
				return dimensionality[i] < other.dimensionality[i];
		return false;
	}

	bool nests(const box &other) const
	{
		for (int i = 0; i < dimensions; i++)
			if (dimensionality[i] >= other.dimensionality[i])
				return false;		
		return true;
	}
};

box boxes[MAXN];
int longest[MAXN];
int ancestor[MAXN];
int nBoxes, nDimensions;

void sequences(int current)
{
	if (ancestor[current] != END)
		sequences(ancestor[current]);
	cout << (ancestor[current] == END ? "" : " ") << (boxes[current].index + 1);
}

void lis(void)
{
	for (int i = 0; i < nBoxes; i++)
		for (int j = 0; j < i; j++)
			if (boxes[j].nests(boxes[i]) && (longest[j] + 1) > longest[i])
			{
				longest[i] = longest[j] + 1;
				ancestor[i] = j;
			}

	int maximum = 0, marker;
	for (int i = 0; i < nBoxes; i++)
		if (maximum < longest[i])
		{
			maximum = longest[i];
			marker = i;
		}

	cout << maximum << endl;
	sequences(marker);
	cout << endl;
}

int main(int ac, char *av[])
{
	while (cin >> nBoxes >> nDimensions)
	{
		for (int i = 0; i < nBoxes; i++)
		{
			longest[i] = 1;
			ancestor[i] = END;

			boxes[i].dimensions = nDimensions;
			boxes[i].index = i;

			for (int j = 0; j < nDimensions; j++)
				cin >> boxes[i].dimensionality[j];
			sort(boxes[i].dimensionality, boxes[i].dimensionality + nDimensions);
		}

		sort(boxes, boxes + nBoxes);

		lis();
	}

	return 0;
}
