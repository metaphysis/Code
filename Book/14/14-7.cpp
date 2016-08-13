const double MAX_DISTANCE = 1e20;

// 分治法求最近点对距离。
double closestDistance(int P[], int Pn, int X[], int Xn, int Y[], int Yn)
{
	// 递归调用的出口，当拆分后点数小于等于3个时，使用穷举法计算最近距离。注意初始距
	// 离应设为“无限大”，“无限大”的具体值应该根据具体应用设置。
	if (Pn <= 3)
	{
		double distance = MAX_DISTANCE;
		for (int i = 0; i < Pn - 1; i++)
			for (int j = i + 1; j < Pn; j++)
			{
				double tmp = distanceOfPoint(points[P[i]], points[P[j]]);
				distance = min(distance, tmp);
			}
			
		return distance;
	}

	// 分解：把点集P划分为两个集合Pl和Pr。并得到相应的Xl，Xr，Yl，Yr。
	int Pl[MAXN], Pln, Pr[MAXN], Prn;
	int Xl[MAXN], Xln, Xr[MAXN], Xrn;
	int Yl[MAXN], Yln, Yr[MAXN], Yrn;

	// 标记某点是否在划分的集合Pl中。初始时，所有点不在集合Pl中。
	bool inPl[MAXN];
	memset(inPl, false, sizeof(inPl));

	// 将数组P划分为两个数量接近的集合Pl和Pr。Pl中的所有点在线l上或在l的左侧，Pr中
	// 的所有点在线l上或在l的右侧。数组X被划分为两个数组Xl和Xr，分别包含Pl和Pr中的
	// 点，并按x坐标单调递增的顺序排序。类似的，数组Y被划分为两个数组Yl和Yr，分别包
	// 含Pl和Pr中的点，并按y坐标单调递增的顺序进行排序。对于Xl，Xr，Yl，Yr，由于参
	// 数X和Y均已排序，只需从中拆分出相应的点即可，并不需要再次排序，拆分后的数组仍
	// 保持排序的性质不变，这是获得O（nlog2n）运行时间的关键，否则若再次排序，运行
	// 时间将为O（n（log2n）^2）。
	int middle = Pn / 2;
	Pln = Xln = middle;
	for (int i = 0; i < Pln; i++)
	{
		Pl[i] = Xl[i] = X[i];
		inPl[X[i]] = true;
	}
	Prn = Xrn = (Pn - middle);
	for (int i = 0; i < Prn; i++)
		Pr[i] = Xr[i] = X[i + middle];

	// 根据某点所属集合，划分Yl和Yr。
	Yln = Yrn = 0;
	for (int i = 0; i < Yn; i++)
		if (inPl[Y[i]])
			Yl[Yln++] = Y[i];
		else
			Yr[Yrn++] = Y[i];

	// 解决：把P划分为Pl和Pr后，再进行两次递归调用，一次找出Pl中的最近点对，另一次
	// 找出Pr中的最近点对。
	double distanceL = closestDistance(Pl, Pln, Xl, Xln, Yl, Yln);
	double distanceR = closestDistance(Pr, Prn, Xr, Xrn, Yr, Yrn);

	// 合并：最近点对要么是某次递归调用找出的距离为distance的点对，要么是Pl中的一个
	// 点与Pr中的一个点组成的点对，算法确定是否存在其距离小于distance的一个点对。
	double minDistance = min(distanceL, distanceR);

	// 建立一个数组Y'，它是把数组Y中所有不在宽度为2*minDistance的垂直带形区域内去掉
	// 后所得的数组。数组Y'与Y一样，是按y坐标顺序排序的。
	int tmpY[MAXN], tmpYn = 0;
	for (int i = 0; i < Yn; i++)
		if (fabs(points[Y[i]].x - points[X[middle]].x) <= minDistance)
			tmpY[tmpYn++] = Y[i];

	// 对数组Y'中的每个点p，算法试图找出Y'中距离p在minDistance单位以内的点。仅
	// 需要考虑在Y'中紧随p后的7个点。算法计算出从p到这7个点的距离，并记录下Y'
	// 的所有点对中，最近点对的距离tmpDistance。
	double tmpDistance = MAXDISTANCE;
	for (int i = 0; i < tmpYn; i++)
	{
		int top = ((i + 7) < tmpYn ? (i + 7) : (tmpYn - 1));
		for (int j = i + 1; j <= top; j++)
		{
			double tmp = calDistance(points[tmpY[i]], points[tmpY[j]]);
			tmpDistance = min(tmpDistance, tmp);
		}	
	}

	// 如果tmpDistance小于minDistance，则垂直带形区域内，的确包含比根据递归调用所找
	// 出的最近距离更近的点对，于是返回该点对及其距离tmpDistance。否则，就返回递归
	// 调用中发现的最近点对及其距离minDistance。
	return min(minDistance, tmpDistance);
}
