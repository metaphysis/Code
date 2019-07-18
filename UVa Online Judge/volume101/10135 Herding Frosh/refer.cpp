#include <bits/stdc++.h>

using namespace std;

#define MAXPOLY 1010
#define EPSILON (1E-9)

struct point
{
	double x;
	double y;
};

point origin = (point){0.0, 0.0};

struct polygon
{
	int vertexNumber;
	point vertex[MAXPOLY];
};

double calDistance(point first, point second)
{
	return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

double crossProduct(point first, point second, point third)
{
	return (second.x - first.x) * (third.y - first.y) -
				 (second.y - first.y) * (third.x - first.x);
}

bool leftLower(point first, point second)
{
	if (first.x == second.x)
	{
		return first.y < second.y;
	}
	else
	{
		return first.x < second.x;
	}
}

void convexHull(point vertex[], int vertexNumber, polygon &container)
{
		if (vertexNumber <= 3)
	{
		for (int i = 0; i < vertexNumber; i++)
		{
			container.vertex[i] = vertex[i];
		}
		container.vertexNumber = vertexNumber;
		return;
	}
		sort(vertex, vertex + vertexNumber, leftLower);
	point upper[MAXPOLY], lower[MAXPOLY];
	int top;
		upper[0] = vertex[0];
	upper[1] = vertex[1];
	top = 2;
	for (int i = 2; i < vertexNumber; i++)
	{
		upper[top] = vertex[i];
		while (top >= 2 && crossProduct(upper[top - 2], upper[top - 1], upper[top]) >= 0)
		{
			upper[top - 1] = upper[top];
			top--;
		}
		top++;
	}
	container.vertexNumber = 0;
	for (int i = 0; i < top; i++)
	{
		container.vertex[container.vertexNumber++] = upper[i];
	}
		lower[0] = vertex[vertexNumber - 1];
	lower[1] = vertex[vertexNumber - 2];
	top = 2;
	for (int i = vertexNumber - 3; i >= 0; i--)
	{
		lower[top] = vertex[i];
		while (top >= 2 && crossProduct(lower[top - 2], lower[top - 1], lower[top]) >= 0)
		{
			lower[top - 1] = lower[top];
			top--;
		}
		top++;
	}
		for (int i = 1; i < top - 1; i++)
	{
		container.vertex[container.vertexNumber++] = lower[i];
	}
}

double convexHullLength(polygon &container)
{
	double length = 0.0;
	for (int i = 0; i < container.vertexNumber; i++)
	{
		int j = (i + 1) % container.vertexNumber;
		length += calDistance(container.vertex[i], container.vertex[j]);
	}
	return length;
}

bool smallerAngle(point first, point second)
{
		if (first.y == 0 && second.y == 0 && first.x * second.x <= 0)
	{
		return first.x > second.x;
	}
	if (first.y == 0 && first.x >= 0 && second.y != 0)
	{
		return true;
	}
	if (second.y == 0 && second.x >= 0 && first.y != 0)
	{
		return false;
	}
	if (first.y * second.y < 0)
	{
		return first.y > second.y;
	}
		double cp = crossProduct(origin, first, second);
	return cp > 0 || (cp == 0 && fabs(first.x) < fabs(second.x));
}

double minConvexHullLength(point in[], int &n)
{
	double length = 1e20;
			sort(in, in + n, leftLower);
	int hole = 0;
	for (int i = 0; i < n; i++)
	{
		if (in[i].x == 0 && in[i].y == 0)
		{
			continue;
		}
		if (hole == 0)
		{
			in[hole++] = in[i];
		}
		else if (in[hole - 1].x == in[i].x && in[hole - 1].y == in[i].y)
		{
			continue;
		}
		else
		{
			in[hole++] = in[i];
		}
	}
	n = hole;
		sort(in, in + n, smallerAngle);
		polygon out;
	for (int i = 0; i < n; i++)
	{
		int top = 1, current = i + 1;
		out.vertex[0] = origin;
		out.vertex[1] = in[i];
		while (current < (i + n))
		{
									if (top >= 1 && crossProduct(out.vertex[top - 1], out.vertex[top], in[current % n]) <= 0)
			{
				top--;
			}
			else
			{
				top++;
				out.vertex[top] = in[current % n];
				current++;
			}
		}
				top++;
		out.vertex[top] = in[(i - 1 + n) % n];
		out.vertexNumber = top;
				length = min(length, convexHullLength(out));
	}
	return length;
}

int main(int ac, char *av[])
{
	point frosh[MAXPOLY];
	polygon silk;
	int cases, vertexNumber, froshNumber;
	bool printBlankLine = false;
	cout.precision(2);
	cout.setf(ios::fixed | ios::showpoint);
	cin >> cases;
	while (cases--)
	{
		cin >> froshNumber;
		frosh[0] = origin;
		for (int i = 1; i <= froshNumber; i++)
		{
			cin >> frosh[i].x >> frosh[i].y;
		}
		froshNumber++;
		convexHull(frosh, froshNumber, silk);
				double minLength = convexHullLength(silk) + 2.0;
				bool onPolygon = false;
		for (int i = 0; i < silk.vertexNumber; i++)
		{
			int j = (i + 1) % silk.vertexNumber;
						if (fabs(crossProduct(origin, silk.vertex[i],
														silk.vertex[j])) <= EPSILON)
			{
				onPolygon = true;
				break;
			}
		}
				if (!onPolygon)
		{
			minLength = minConvexHullLength(frosh, froshNumber) + 2.0;
		}
		if (printBlankLine)
		{
			cout << endl;
		}
		else
		{
			printBlankLine = true;
		}
		cout << minLength << endl;
	}
	return 0;
}

