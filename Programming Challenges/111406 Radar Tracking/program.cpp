// Radar Tracking （雷达追踪）
// PC/UVa IDs: 111406/849, Popularity: C, Success rate: low Level: 2
// Verdict: Wrong Answer
// Submission Date: 2011-11-14
// UVa Run Time: N/A
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 雷达的角速度为 PI 弧度每秒。所有物体均是沿直线运动（不考虑圆周运动或其他曲线运动的情况）。方程
// 是超越方程，需要使用近似解法来解方程。或者直接使用枚举的办法，因为角度要求是小数点后两位数。

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

#define MAXN 3
#define PI 3.141592653589793
#define EPSILON (1E-10)

#define COUNTER_CLOCKWISE 0
#define CLOCKWISE_SAME_SAME_CYCLE 1
#define CLOCKWISE_SAME_NEXT_CYCLE 2
#define CLOCKWISE_NEXT_NEXT_CYCLE 3

struct point
{
	double angle;
	double distance;
};

bool cmp(point a, point b)
{
	if (a.angle != b.angle)
		return a.angle < b.angle;
	return a.distance > b.distance;
}

double radians(double degree)
{
	return (degree / 180.0) * PI;
}

double degrees(double radian)
{
	return (radian / PI) * 180.0;
}

double value(double b, double c, double B, double C, double x, int type)
{
	switch (type)
	{
		case COUNTER_CLOCKWISE:
			return b * sin(x) - sin(B + C + x) * c * (2.0 * PI - x) / (2.0 * PI - C);
			break;
		case CLOCKWISE_SAME_SAME_CYCLE:
			return b * sin(x) - sin(B + C + x) * c * x / C;
			break;
		case CLOCKWISE_SAME_NEXT_CYCLE:
			return b * sin(x) - sin(B + C + x) * c * (2.0 * PI + x) / C;
			break;		
		case CLOCKWISE_NEXT_NEXT_CYCLE:
			return b * sin(x) - sin(B + C + x) * c * (2.0 * PI + x) / (2.0 * PI + C);
			break;
	}
}

double bisection(double b, double c, double B, double C, int type)
{
	// 设第三个观察位置与第二个观察位置的角度差为 x 弧度，则由三角关系和
	// 雷达的扫描角速度以及物体的运动速度，可以得到如下方程。
	//
	// b * sin(x) - sin(B + C + x) * c * (2 * PI - x) / (2 * PI - C) = 0。
	//
	// 由二分法得到近似解。x 的区间为 （0，PI - B - C）。首先找到大于
	// 0 时的 x 值，已经明确，当 x = 0 时，函数值小于 0，则需要找到一
	// 个值，使得函数值大于 0。
	double up = PI - B - C, down = 0.0;
	double x = (up + down) / 2.0;
	while (value(b, c, B, C, x, type) < 0)
		x = (up + x) / 2.0;

	// 此时函数值大于 0。
	up = x;

	// 目前 f（up） 和 f（down） 异号，则区间 （down，up） 有解。
	while (fabs(up - down) > EPSILON)
	{
		x = (up + down) / 2.0;
		if (value(b, c, B, C, x, type) * value(b, c, B, C, up, type) > 0)
			up = x;
		else
			down = x;
	}
	
	return x;
}

void possibleSolutions(point first, point second)
{
	point possible[MAXN];
	int solutions = 0;

	// 当前后两次的角度相同时，说明物体的运动轨迹在水平面的投影是过极点的直线，
	// 第一次观测和第二次观测时间相差 2 s。
	if (first.angle == second.angle)
	{
		// 正在向远离极点的方向运动。
		if (second.distance >= first.distance)
			possible[solutions++] = (point){first.angle, 
					second.distance + (second.distance - first.distance)};
		// 正在向靠近极点的方向运动，可能会越过极点到相对的另一侧。
		else
		{
			if (second.distance > (first.distance - second.distance))
				possible[solutions++] = (point) {first.angle, 
					second.distance - (first.distance - second.distance)};
			else
				possible[solutions++] = (point){
				((first.angle >= 180.0) ?
					(first.angle - 180.0) :
						(first.angle + 180.0)),
				fabs(second.distance - (first.distance - second.distance))};
		}
	}
	// 当前后两次观察到的位置极角相差 180 度时，说明物体的运动轨迹在平面上的
	// 投影是过极点的直线。
	else if (fabs(first.angle - second.angle) == 180.0)
	{
	    // 这里有两种情况，第一种是在第一次观察后，物体越过极点到达对侧，雷达
	    // 探测到该物体，时间间隔为 1 s；第二种情况是物体在第一次观察后，雷达
	    // 在回到第一次的观察的角度时，物体正好在雷达的上方而未探测到，当物体
	    // 越过极点后到达对侧，雷达探测到物体，此时共用时 3 s。
	    
		// 第一种情况：第二次观察时，时间为 1 s，第三次观察时，将是 3 s。故移
		// 动距离要增加两倍。
		possible[solutions++] = (point){second.angle, 
				3 * second.distance + 2 * first.distance};
				
		// 第二种情况：需要判断，如果第二次观察的距离为第一次的一半，则可能属于
		// 此种情况。
		if (fabs(2 * second.distance - first.distance) <= EPSILON)
		{
		    possible[solutions++] = (point){second.angle,
		        first.distance + second.distance};
		}
	}
	// 当第一次和第二次的极角不同，且相差不是 180 度时，物体的运动轨迹在平面上
	// 的投影是一条不过极点的直线。
	else
	{
		// 当第二次观察位置出现在第一次的逆时针方向，则表明雷达是在一个周期的
		// 时间内观察到两个位置。则第三次观察时只有一种可能的位置。
		double C = 0.0, finalAngle, finalDistance, x;
		double angleDiff = fabs(first.angle - second.angle);
		if ((first.angle > second.angle && angleDiff < 180.0) ||
			(first.angle < second.angle && angleDiff > 180.0))
		{
			// 二分数值法求近似解。
			// 先求出前后两次观察位置之间的角度差，设为角 C，对应边为 c。
			if (first.angle < second.angle && angleDiff > 180.0)
				C = radians(first.angle + (360.0 - second.angle));
			else
				C = radians(first.angle - second.angle);

			// 不失一般性，设第一次观察的位置距离为 a，第二次观察的距离为 b，可
			// 由正弦和余弦定理求出边 b 对应的角 B。先求边 c。
			double a = first.distance, b = second.distance;
			double c = sqrt(a * a + b * b - 2.0 * a * b * cos(C));
			double B = asin(sin(C) * b / c);

			x = bisection(b, c, B, C, COUNTER_CLOCKWISE);
			finalAngle = second.angle - degrees(x);
			if (finalAngle < 0.0)
				finalAngle += 360.0;
			finalDistance = b * sin(B + C) / sin(B + C + x);
			possible[solutions++] = (point){finalAngle, finalDistance};
		}
		// 第二个位置在第一个位置的顺时针方向，有两种可能，一种是在观察到第一个
		// 位置后的同一个扫描周期内观察到第二个位置，另外一种情况是在下一个扫描
		// 周期内观察到第二个位置。故有两种可能解。
		else
		{
			if (first.angle > second.angle && angleDiff > 180.0)
				C = radians(second.angle + (360.0 - first.angle));
			else
				C = radians(second.angle - first.angle);

			double a = first.distance, b = second.distance;
			double c = sqrt(a * a + b * b - 2.0 * a * b * cos(C));
			double B = asin(sin(C) * b / c);

			
			// 计算所有可能性。
			for (int i = CLOCKWISE_SAME_SAME_CYCLE; i <= CLOCKWISE_NEXT_NEXT_CYCLE; i++)
			{
				x = bisection(b, c, B, C, i);
				if (x == 0.0)
					continue;
				finalAngle = second.angle + degrees(x);
				if (finalAngle >= 360.0)
					finalAngle -= 360.0;
			    if (fabs(finalAngle - first.angle) < 0.01 ||
			        fabs(finalAngle - second.angle) < 0.01)
			        continue;
				finalDistance = b * sin(B + C) / sin(B + C + x);
				possible[solutions++] = (point){finalAngle, finalDistance};
			}

			// 判断那些解是有效解。
			// 检查计算结果是否满足物体的速度限制要求。若存在则有矛盾，该组结果丢弃。
			// 假设物体速度为 c / （C / PI），即在转过 C 角度的时间，物体运动距离
			// 为 c，计算第二次观察结果，若结果符合，则第一组结果有效，第二组结果
			// 无效，否则相反。
            

			// 物体速度为 c / （C / PI + 2.0），计算第二次观察结果，若符合则
			// 第三组结果有效，否则无效。
		}
	}

	// 按极角和距离排序。
	bool blank = false;
	sort(possible, possible + solutions, cmp);
	for (int i = 0; i < solutions; i++)
	{
		if (possible[i].distance == 0)
			continue;
		cout << (blank ? " " : "");
		blank = true;
		cout << possible[i].angle << " " << possible[i].distance;
	}
	cout << endl;
}

int main (int argc, char const* argv[])
{
	cout.precision(2);
	cout.setf(ios::fixed | ios::showpoint);

	point first, second;
	while (cin >> first.angle >> first.distance >> second.angle >> second.distance)
		possibleSolutions(first, second);

	return 0;
}
