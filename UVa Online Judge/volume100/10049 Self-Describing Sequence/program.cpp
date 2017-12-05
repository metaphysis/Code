// Self-describing Sequence （自描述序列）
// PC/UVa IDs: 110607/10049, Popularity: C, Success rate: high Level: 2
// Verdict: Accepted
// Submission Date: 2011-06-07
// UVa Run Time: 0.048s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 显式的生成这个序列显然是超出内存限制也是没有必要的。有两种方法，一种是得出递推关系，一
// 种是根据序列特点得到某数的f（n）值。
//
// 递推方法：设 G（n） 表示满足 f（k） > f(k - 1) 时的自变量值，观察序列可以知道 G（1）
// = 2，G（2） = 4，G（3） = 6，G（4） = 9，... ，由序列的定义可以知道区间 
// [G（n - 1），G（n）） 有 f（n） 个 n，则可以知道：
//
// G（n） = f（1） + f（2） + f（3） + ... + f（n） + 1
//
// 则有：
//
// G（n） = G（n - 1） + f（n）
//
// 由于已经知道 [G（n - 1），G（n）） 之间的数函数值都是 n。则可以通过以下方式计算
// G（n） 的值：
// G（1） = 2，G（2） = 4，k = 1，对于[G（k），G（k + 1））之间的数，其 f（n） =
// k + 1，则有 G（n） = G（n - 1） + k + 1。
//
// 非递推方法：根据以下事实，从 n = 3 开始对于序列中的每一对 f（n） = k，则必将在序列
// 中添加 f（n） * k 个元素。可以使用一个队列来记录添加的元素，计算将要添加的元素总数，
// 直到该队列将要产生的元素量超过指定数量。根据情况判定要求的 n 值的函数值。具体方法如下：
// 
// 1. n = 1 或者 n = 2，特殊情况，予以特殊处理。
// 2. 设 sequence 为一个队列，记录该序列的元素，初始情况下，队列中存储了 n = 3 时的函
// 数值即 f（3） = 2。变量 total 根据 f（n） * k 的关系记录当前队列中存储元素所能产生
// 的元素总量，初始值为 0。变量 n 为当前的自变量值。
// 3. 从队列中取出第一个元素，设其值为 fn，可知 f（n） = fn。则队列所能产生元素个数
// total += fn * n。比较当前 n 与输入中要求函数值的数 k，若相等则表明 f（k） = fn。
// 否则继续计算 total 直到上限值。
// 4. 当前序列已经产生了足够的元素，最后能生成指定上限的元素，则继续从队列首位取出一个元
// 素，按前述步骤，只不过这时不需要实际在队列的最后添加元素，而是计算 total 的变化范围，
// 在 [total, total + fn) 之间数的函数值都是刚弹出的元素所对应的 n 值。同时仍应比对队
// 列首的 n 值，若有值对应，则该数的函数值就是弹出的队列元素值 fn。
// 5. 继续处理直到找到所有输入数的函数值，然后输出结果。

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
	
struct data
{
	int value;
	int index;
	int fn;
};
	
// 递推方式解法。
void self_describing_by_recurrence()
{
	int self[700000];
	const int max = 2000000000;
	
	self[0] = 1;
	self[1] = 2;
	self[2] = 4;
	
	int index = 0;
	while (self[self[index] - 1] < max)
	{
		for (int j = self[index]; j < self[index + 1]; j++)
			self[j] = self[j - 1] + index + 1;
		index++;
	}
	
	int capacity = self[index] - 1;
	int n;
	while (cin >> n, n)
		cout << upper_bound(self, self + capacity, n) - self << endl;
}
	
bool cmp(data x, data y)
{
	return x.value < y.value;
}
	
// 非递推方式解法。
void self_describing_by_iterate()
{
	int counter = 0, tmp;
	vector < data > input;
	
	while (cin >> tmp, tmp)
	{
		data t;
		t.value = tmp;
		t.index = counter++;
		t.fn = 0;
		
		input.push_back(t);
	}
	
	// 排序以便输出。
	sort(input.begin(), input.end(), cmp);
		
	// 记录当前已添加的元素的队列。
	queue<int> sequence;
	// 初始时函数自变量 n 为 3，当前已有两个元素，即 total 所指定的值。
	int n = 3, total = 2, index = 0, maxn = input[input.size() - 1].value;
	// 输入中尚未设置 f（n） 值的元素个数。
	int unsetted = input.size();
	
	// 处理 n == 1 和 n == 2 的情况。
	while (input[index].value <= 2)
	{
		input[index].fn = input[index].value;
		index++;
		unsetted--;
	}
	
	if (!unsetted)
		goto out;
			
	// 压入初始元素。
	sequence.push(2);
	// 当将要添加的元素总数少于输入的最大给定值时，继续计算添加元素的数量。
	while (total < maxn)
	{
		// 根据序列定义，将 fn 个 n 压入队列。
		int fn = sequence.front();
		for (int c = 1; c <= fn; c++)
			sequence.push(n);
			
		// 计算队列所能产生元素的总数。
		total += fn * n;
		
		// 比较当前 n 值是否和要求的数相等，若相等，则表明要求的数的函数值
		// 就是队列首的元素 fn。
		if (input[index].value == n)
		{
			input[index++].fn = fn;
	
			unsetted--;
			if (!unsetted)
				goto out;
		}
		
		// 弹出队列首元素。
		sequence.pop();
		n++;
	}
	
	total = n + sequence.size();	
	while (sequence.size())
	{
		// 比较队列前端和输入 n 值是否匹配。
		int fn = sequence.front();
		if (input[index].value == n)
		{
			input[index++].fn = fn;
			unsetted--;
		}
		
		// 确定是否有元素在区间 [total, total + number)。
		for (int i = index; i < input.size(); i++)
			if (total <= input[i].value && input[i].value <= (total + fn - 1))
			{
				input[i].fn = n;
				unsetted--;
			}
		
		// 所有数都已设置，打印退出。	
		if (!unsetted)
			goto out;
		
		// 计数要添加的元素个数，并不需要实际添加。
		total += fn;
		sequence.pop();
		n++;
	}
	
out:
	for (int i = 0; i < input.size(); i++)
		for (int j = 0; j < input.size(); j++)
			if (input[j].index == i)
				cout << input[j].fn << endl;
}

int main(int ac, char *av[])
{
	//self_describing_by_recurrence();
	self_describing_by_iterate();
	
	return 0;
}
