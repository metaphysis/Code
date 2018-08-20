// The 3n+1 Problem （3n+1 问题）
// PC/UVa IDs: 110101/100, Popularity: A, Success rate: low Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-22
// UVa Run Time: 0.032s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net。
//
// [问题描述]
// 考虑如下的序列生成算法：从整数 n 开始，如果 n 是偶数，把它除以 2；如果 n 是奇数，把它乘 3 加
// 1。用新得到的值重复上述步骤，直到 n = 1 时停止。例如，n = 22 时该算法生成的序列是：
//
// 22，11，34，17，52，26，13，40，20，10，5，16，8，4，2，1
//
// 人们猜想（没有得到证明）对于任意整数 n，该算法总能终止于 n = 1。这个猜想对于至少 1 000 000
// 内的整数都是正确的。
//
// 对于给定的 n，该序列的元素（包括 1）个数被称为 n 的循环节长度。在上述例子中，22 的循环节长度
// 为 16。输入两个数 i 和 j，你的任务是计算 i 到 j（包含 i 和 j）之间的整数中，循环节长度的最大
// 值。
//
// [输入]
// 输入每行包含两个整数 i 和 j。所有整数大于 0，小于 1 000 000。
//
// [输出]
// 对于每对整数 i 和 j，按原来的顺序输出 i 和 j，然后输出二者之间的整数中的最大循环节长度。这三
// 个整数应该用单个空格隔开，且在同一行输出。对于读入的每一组数据，在输出中应位于单独的一行。
//
// [样例输入]
// 1 10
// 100 200
// 201 210
// 900 1000
//
// [样例输出]
// 1 10 20
// 100 200 125
// 201 200 89
// 900 1000 174
//
// [解题方法]
// 计算每个数的循环节长度，求给定区间的最大值。
//
// 需要注意：
// 1. 中间计算过程会超过 int 或 long （如果 int 或 long 型均为 4 字节存储空间） 型数据所能
//    表示的范围，故需要选择 long long （8 字节存储空间）型整数。
// 2. 输入时可能较大的数在前面，需要调整顺序，这个是导致算法正确却 WA 的重要原因。
// 3. 采用填表的方法保存既往计算结果，可以显著减少计算时间。
//
// 从网络上看了许多别人的解题方案，大多数都是忽略了第一点，求循环节长度的过程中，选择了 int 或
// long （按 32 位 CPU 来假定，4 字节存储空间）类型的数据，当计算 （n * 3 + 1） 时会超出 32
// 位整数的表示范围而得到错误答案，只不过 Programming Challenges 和 UVa 上的测试数据不是很强，
// 所以尽管不完善但都会获得 AC。在 1 - 999999 之间共有 41 个数在中间计算过程中会得到大于 32 位
// 无符号整数表示范围的整数，当测试数据包含这些数时，选用 int 或 long 类型有可能会得到错误的答案。
//
// 在中间计算过程中会超过 32 位整数表示范围的整数（括号内为循环节长度）：
// 159487（184）  270271（407）  318975（185）  376831（330）  419839（162）
// 420351（242）  459759（214）  626331（509）  655359（292）  656415（292）
// 665215（442）  687871（380）  704511（243）  704623（504）  717695（181）
// 730559（380）  736447（194）  747291（248）  753663（331）  763675（318）
// 780391（331）  807407（176）  822139（344）  829087（194）  833775（357）
// 839679（163）  840703（243）  847871（326）  859135（313）  901119（251）
// 906175（445）  917161（383）  920559（308）  937599（339）  944639（158）
// 945791（238）  974079（383）  975015（321）  983039（290）  984623（290）
// 997823（440）
	
#include <bits/stdc++.h>

using namespace std;

#define MAXSIZE 1000000
	
int cache[MAXSIZE] = {};

int getCycle1(int n)
{
    long long int nn = n;
    int length = 1;
    while (nn > 1)
    {
        nn = (nn & 1) ? (nn + (nn << 1) + 1) : (nn >> 1);
        length += 1;
    }
    return length;
}

// 计算循环节长度。
int getCycle(long long number)
{
	if (number == 1) return 1;
	
	// 模 2 计算可用与计算代替，除 2 计算可用右移计算代替。
	if (number & 1) number += (number << 1) + 1;
	else number >>= 1;
	
	// 若 number 在缓存范围内则根据情况取用。
	if (number < MAXSIZE )
	{
		if (!cache[number]) cache[number] = getCycle(number);
		return 1 + cache[number];
	}
	
	return 1 + getCycle(number);
}
	
int main(int ac, char *av[])
{
    ios::sync_with_stdio(false);
    
	// 对于 GUN C++ 编译器，使用默认参数，在编译时会自动将全局数组 cache 中未初始化
	// 的元素初始化为 0，故可以不需要显式的进行初始化的工作。对于其他编译器应该根据情况调整。
	//
	// memset(cache, 0, sizeof(cache));
	//
	int first, second, start, end;

	while (cin >> first >> second)
	{
		// 得到给定范围的上下界。
		start = min(first, second);
		end = max(first, second);
		
		// 查找最大步长值。
		int result = 0, steps;
		for (int i = start; i <= end; i++)
			if ((steps = getCycle(i)) > result)
				result = steps;

		// 输出。
		cout << first << " " << second << " " << result << endl;
	}
	
	return 0;
}