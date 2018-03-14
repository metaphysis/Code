// Graphical Editor （图形化编辑器）
// PC/UVa IDs: 110105/10267, Popularity: B, Success rate: low Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-16
// UVa Run Time: 0.060s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
	
#define SWAP(x, y, type) \
	{\
		if (x > y)\
		{\
			type tmp = x;\
			x = y;\
			y = tmp;\
		}\
	}
	
// 输出图形矩阵的内容。
ostream& operator<<(ostream &out, const vector < vector < char > > &matrix)
{
	for (vector < vector < char > >::const_iterator p = matrix.begin(); 
		p != matrix.end(); p++)
	{
		copy((*p).begin(), (*p).end(), ostream_iterator < char >(out, ""));
		out << endl;
	}

	return out;
}
	
// 重置字符矩阵。
void reset(vector < vector < char > > &matrix)
{
	// 注意是初始化为大写字母O而不是数字0.
	for (vector < vector < char > >::iterator p = matrix.begin(); 
		p != matrix.end(); p++)
		fill((*p).begin(), (*p).end(), 'O');
}
	
// 设置点（x，y）的颜色为c。
void set_pixel(vector < vector < char > > &matrix, int x, int y, char c)
{
	matrix[y][x] = c;
}
	
// 填充左上角为（x1，y1），右下角为（x2，y2）的矩形区域为颜色c。
void fill_rect(vector < vector < char > > &matrix, int x1, int y1, 
	int x2, int y2, char c)
{
	for (int i = y1; i <= y2; i++)
		for (int j = x1; j <= x2; j++)
			matrix[i][j] = c;
}
	
// 填充包含点（x，y）的区域为颜色newColor。
void fillRegion(vector<vector<char>> &matrix, int x, int y, char oldColor, char newColor)
{
	// 当新旧颜色相同时需要结束递归，否则会形成无限循环。
	if (oldColor == newColor) return;
	
	matrix[y][x] = newColor;
	
	if (x > 0 && matrix[y][x - 1] == oldColor)
		fillRegion(matrix, x - 1, y, oldColor, newColor);
	
	if (x < matrix[y].size() - 1 && matrix[y][x + 1] == oldColor)
		fillRegion(matrix, x + 1, y, oldColor, newColor);
	
	if (y > 0 && matrix[y - 1][x] == oldColor)
		fillRegion(matrix, x, y - 1, oldColor, newColor);
	
	if (y < matrix.size() - 1 && matrix[y + 1][x] == oldColor)
	    fillRegion(matrix, x, y + 1, oldColor, newColor);
}
	
int main(int argc, char *argv[])
{
	// 使用二维向量来保存字符矩阵。
	vector < vector < char > > matrix;
	string line;
	// 用于表示图像的一些变量。
	int width, height, x, y, x1, x2, y1, y2;
	char command, color;
	
	while (getline(cin, line), line[0] != 'X')
	{
		istringstream iss(line);
	
		// 读入命令。
		iss >> command;
		switch (command)
		{
			// 初始化图像为宽为width，高为height。
			case 'I':
				iss >> width >> height;
	
				matrix.clear();
				matrix.resize(height);
				for (vector < vector < char > >::iterator 
					p = matrix.begin(); p != matrix.end(); p++)
					(*p).resize(width);

				reset(matrix);
				break;
			// 重置矩阵。	
			case 'C':
				reset(matrix);
				break;
			// 设置某点颜色。	
			case 'L':
				iss >> x >> y >> color;
				x--;
				y--;

				set_pixel(matrix, x, y, color);
				break;
			// 绘制竖线。
			case 'V':
				iss >> x >> y1 >> y2 >> color;
				x--;
				y1--;
				y2--;

				SWAP(y1, y2, int);

				fill_rect(matrix, x, y1, x, y2, color);
				break;
			// 绘制水平线。	
			case 'H':
				iss >> x1 >> x2 >> y >> color;
				x1--;
				x2--;
				y--;

				SWAP(x1, x2, int);

				fill_rect(matrix, x1, y, x2, y, color);
				break;
			// 填充矩形区域。	
			case 'K':
				iss >> x1 >> y1 >> x2 >> y2 >> color;
				x1--;
				y1--;
				x2--;
				y2--;

				SWAP(x1, x2, int);
				SWAP(y1, y2, int);

				fill_rect(matrix, x1, y1, x2, y2, color);
				break;
			// 填充包含点（x，y）的区域为颜色color。	
			case 'F':
				iss >> x >> y >> color;
				x--;
				y--;

				fill_region(matrix, x, y, matrix[y][x], color);
				break;
			// 按 MSDOS 8.3命名格式输出文件名。	
			case 'S':
				string file_name;
				iss >> file_name;
				
				if (file_name.length() > 12)
					file_name = file_name.substr(0, 12);
				cout << file_name << endl;
				cout << matrix;
				break;
		}
	}
	
	return 0;
}
