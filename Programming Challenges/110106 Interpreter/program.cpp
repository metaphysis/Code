// Interpreter （解释器）
// PC/UVa IDs: 110106/10033, Popularity: B, Success rate: low Level: 2
// Verdict: Accepted
// Submission Date: 2011-04-09
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <iostream>
#include <cstdlib>
#include <cstring>
	
using namespace std;
	
int execute(int *reg, int *mem)
{
	int pointer = 0, step = 0, code = mem[0], a, b, c;
	while (code != 100 && pointer < 1000)
	{
		code = mem[pointer];
		a = code / 100;		// 操作类型。
		b = (code / 10) % 10;	// 寄存器。
		c = code % 10;		// 操作数或地址或寄存器。
	
		switch (a)
		{
			// 如果寄存器c中的地址不为0，则跳转到寄存器b所指向的指令。
			case 0:
				if (reg[c] != 0)
					pointer = reg[b] - 1;
				break;
			// 100结束。
			case 1:
				if (!b && !c)
					return (1 + step);
			// 将寄存器b的值设置为c。
			case 2:
				reg[b] = c;
				break;
			// 将寄存器b的值增加c。
			case 3:
				reg[b] += c;
				break;
			// 将寄存器b的值自乘c。
			case 4:
				reg[b] *= c;
				break;
			// 将寄存器b的值设置为寄存器c的值。
			case 5:
				reg[b] = reg[c];
				break;
			// 将寄存器c的值加上寄存器b的值然后放到寄存器b中。
			case 6:
				reg[b] += reg[c];
				break;
			// 将寄存器b的值乘以寄存器c的值然后放到寄存器b中
			case 7:
				reg[b] *= reg[c];
				break;
			// 将寄存器b的值设置为寄存器c的值所指向的地址存储的值。
			case 8:
				reg[b] = mem[reg[c]];
				break;
			// 将地址为寄存器c的值的内容设置为寄存器b内所存储的值。
			case 9:
				mem[reg[c]] = reg[b];
				break;
		}
		
		// 所有结果均取1000的模。执行步骤和当前指令均自增1。
		reg[b] %= 1000;
		step++;
		pointer++;
	}
}

int main(int argc, char *argv[])
{
	int reg[10], mem[1000], cases = 0, i = 0, j = 0;
	string line;
	
	// 读入测试用例数。
	cin >> cases;
	cin.ignore();
	getline(cin, line);
	
	while (cases--)
	{
		// 重置存储内容。
		memset(mem, 0, sizeof(mem));
		memset(reg, 0, sizeof(reg));
		
		// 读入代码。
		for (int i = 0; getline(cin, line) && line.length(); i++)
			mem[i] = atoi(line.data());
	
		// 模拟执行过程。
		cout << execute(reg, mem) << endl;

		if (cases)
			cout << endl;

	}
	
	return 0;
}
