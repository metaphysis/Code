// Climbing Trees
// UVa ID: 115
// Verdict: Accepted
// Submission Date: 2011-11-27
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 模拟题。由于只需要保存父子关系，不一定要构建树。虽然方法是直接的，但是有点繁琐。

#include <bits/stdc++.h>

using namespace std;

#define MAXN 310
#define DUMMY (-1)

int parent[MAXN];
map<string, int> genealogy;
	
bool isAncestor(string fName, string sName)
{
	int nFirst = genealogy[fName];
	int nSecond = genealogy[sName];
	int depth = 0;
	bool found = false;

	while (parent[nSecond] != DUMMY)
	{
		if (parent[nSecond] == nFirst)
		{
			found = true;
			break;
		}
		nSecond = parent[nSecond];
		depth++;
	}
	
	if (found)
	{
		if (depth == 0)
			cout << "parent\n";
		else if (depth == 1)
			cout << "grand parent\n";
		else
		{
			for (int i = 1; i < depth; i++)
				cout << "great ";
			cout << "grand parent\n";		
		}

		return true;
	}
	
	return false;
}

bool isDescendent(string fName, string sName)
{
	int nFirst = genealogy[fName];
	int nSecond = genealogy[sName];
	int depth = 0;
	bool found = false;
	while (parent[nFirst] != DUMMY)
	{
		if (parent[nFirst] == nSecond)
		{
			found = true;
			break;
		}
		nFirst = parent[nFirst];
		depth++;
	}
	
	if (found)
	{
		if (depth == 0)
			cout << "child\n";
		else if (depth == 1)
			cout << "grand child\n";
		else
		{
			for (int i = 1; i < depth; i++)
				cout << "great ";
			cout << "grand child\n";		
		}

		return true;
	}
	
	return false;
}

bool isInTree(string fName, string sName)
{
	if (genealogy.find(fName) == genealogy.end() ||
			genealogy.find(sName) == genealogy.end())
	{
		cout << "no relation\n";
		return false;
	}
	
	return true;
}

bool isInSameTree(string fName, string sName)
{
	int nFirst = genealogy[fName];
	int nSecond = genealogy[sName];

	while (parent[nFirst] != DUMMY)
		nFirst = parent[nFirst];
	while (parent[nSecond] != DUMMY)
		nSecond = parent[nSecond];

	if (nFirst != nSecond)
	{
		cout << "no relation\n";
		return false;		
	}
	
	return true;
}

bool isSibling(string fName, string sName)
{
	int nFirst = genealogy[fName];
	int nSecond = genealogy[sName];	
	if (parent[nFirst] != DUMMY && parent[nSecond] != DUMMY &&
		parent[nFirst] == parent[nSecond])
	{
		cout << "sibling\n";
		return true;
	}
	
	return false;
}

bool isCousin(string fName, string sName)
{
	int nFirst = genealogy[fName];
	int nSecond = genealogy[sName];
	int n = 0, m = 0;

	while (parent[nFirst] != DUMMY)
	{
		nFirst = parent[nFirst];
		n++;
	}
	while (parent[nSecond] != DUMMY)
	{
		nSecond = parent[nSecond];
		m++;
	}

	nFirst = genealogy[fName];
	nSecond = genealogy[sName];
	int backN = n, backM = m;

	if (n > m)
	{
		while (n > m)
		{
			nFirst = parent[nFirst];
			n--;
		}
		while (parent[nFirst] != parent[nSecond])
		{
			nFirst = parent[nFirst];
			nSecond = parent[nSecond];
			n--;
		}
		
		backN -= n;
		backM -= n;
		
		cout << backM << " cousin removed " << (backN - backM) << "\n";
	}
	else if (m > n)
	{
		while (m > n)
		{
			nSecond = parent[nSecond];
			m--;
		}
		while (parent[nFirst] != parent[nSecond])
		{
			nFirst = parent[nFirst];
			nSecond = parent[nSecond];
			m--;
		}
		
		backN -= m;
		backM -= m;
		
		cout << backN << " cousin removed " << (backM - backN) << "\n";	
	}
	else
	{
		while (parent[nFirst] != parent[nSecond])
		{
			nFirst = parent[nFirst];
			nSecond = parent[nSecond];
			n--;
			m--;
		}
		
		cout << (backN - n) << " cousin\n";
	}
}

int main (int argc, char const* argv[])
{
	int nNames = 0;
	string allNames[MAXN];
	string childName, parentName;

	for (int i = 0; i < MAXN; i++)
		parent[i] = DUMMY;

	while (cin >> childName >> parentName)
	{
		if (childName == "no.child" && parentName == "no.parent")
			break;
		if (genealogy.find(childName) == genealogy.end())
		{
			genealogy[childName] = nNames;
			allNames[nNames++] = childName;
		}

		if (genealogy.find(parentName) == genealogy.end())
		{
			genealogy[parentName] = nNames;
			allNames[nNames++] = parentName;
		}

		parent[genealogy[childName]] = genealogy[parentName];
	}

	while (cin >> childName >> parentName)
	{
		if (!isInTree(childName, parentName))
			continue;
		
		if (!isInSameTree(childName, parentName))
			continue;

		if (isAncestor(childName, parentName))
			continue;

		if (isDescendent(childName, parentName))
			continue;

		if (isSibling(childName, parentName))
			continue;

		if (isCousin(childName, parentName))
			continue;
	}

	return 0;
}
