#include <stdio.h>
#include <math.h>
#include <float.h>

int main()
{
	double n;
	double p;

	while (scanf("%lf%lf", &n, &p) != EOF)
	{
		int begin = 1;
		int end = 1000000000;
		int mid;

		// 二分查找。
		while (begin <= end)
		{
			mid = (begin + end) / 2;
			double temp = pow(mid, n);
			if (temp == p)
			{
				printf("%d\n", mid);
				break;
			}
			else if (temp > p)
				end = mid - 1;
			else
				begin = mid + 1;
		}
	}

	return 0;
}
