#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) {
		int width, height;
		cin >> width >> height;
		static char mapData[505][505];
		for (int y =0; y < height; y++)
			for (int x =0; x < width; x++)
				cin >> mapData[y][x];
		static int badCount[505], landCount[505], waterCount[505], roadCount[505];
		static int nextWater[505], nextRoad[505];
		int bestCategory = -1, bestArea = -1, bestX =0, bestY =0, bestRight =0, bestBottom =0;
		for (int top =0; top < height; top++) {
			memset(badCount,0, sizeof(badCount));
			memset(landCount,0, sizeof(landCount));
			memset(waterCount,0, sizeof(waterCount));
			memset(roadCount,0, sizeof(roadCount));
			if (top -1 >=0)
				for (int x =0; x < width; x++)
					if (mapData[top -1][x] == 'R')
						roadCount[x]++;
			for (int x =0; x < width; x++)
				if (mapData[top][x] == 'R')
					roadCount[x]++;
			for (int bottom = top; bottom < height; bottom++) {
				for (int x =0; x < width; x++) {
					if (mapData[bottom][x] == '#' || mapData[bottom][x] == 'R')
						badCount[x]++;
					if (mapData[bottom][x] == '-')
						landCount[x]++;
					if (mapData[bottom][x] == 'W')
						waterCount[x]++;
				}
				if (bottom +1 < height)
					for (int x =0; x < width; x++)
						if (mapData[bottom +1][x] == 'R')
							roadCount[x]++;
				nextWater[width] = width;
				nextRoad[width] = width;
				for (int x = width -1; x >=0; x--) {
					nextWater[x] = waterCount[x] >0 ? x : nextWater[x +1];
					nextRoad[x] = roadCount[x] >0 ? x : nextRoad[x +1];
				}
				int x =0;
				while (x < width) {
					if (badCount[x] >0) {
						x++;
						continue;
					}
					int start = x, end = x, lastLand = -1;
					while (end < width && badCount[end] ==0) {
						if (landCount[end] >0)
							lastLand = end;
						end++;
					}
					end--;
					if (lastLand >= start) {
						for (int left = start; left <= lastLand; left++) {
							int right = end;
							int waterFlag = nextWater[left] <= right;
							int roadStart = left -1 <0 ?0 : left -1;
							int roadEnd = right +1 >= width ? width -1 : right +1;
							int roadFlag = nextRoad[roadStart] <= roadEnd;
							int category = roadFlag *2 + waterFlag;
							int area = (right - left +1) * (bottom - top +1);
							bool better = false;
							if (category > bestCategory)
								better = true;
							else if (category == bestCategory) {
								if (area > bestArea)
									better = true;
								else if (area == bestArea) {
									if (left < bestX)
										better = true;
									else if (left == bestX) {
										if (top < bestY)
											better = true;
										else if (top == bestY && right > bestRight)
											better = true;
									}
								}
							}
							if (better) {
								bestCategory = category;
								bestArea = area;
								bestX = left;
								bestY = top;
								bestRight = right;
								bestBottom = bottom;
							}
						}
					}
					x = end +1;
				}
			}
		}
		if (bestCategory == -1)
			cout << "No good places.\n";
		else cout << bestX << ' ' << bestY << ' ' << bestRight - bestX +1 << ' ' << bestBottom - bestY +1 << '\n';
	}
	return 0;
}
