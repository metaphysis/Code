// Faucet Flow
// UVa ID: 10366
// Verdict: Accepted
// Submission Date: 2025-11-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct divider {
    int p, idx, height;
};

int main()
{
    int leftIdx, rightIdx;
    while (cin >> leftIdx >> rightIdx) {
        if (leftIdx == 0 && rightIdx == 0) break;
        vector<divider> ds;
        int leftEndIdx = -1, rightStartIdx = -1;
        for (int i = leftIdx, j = 0, h; i <= rightIdx; j++, i += 2) {
            cin >> h;
            ds.push_back(divider{i, j, h});
            if (i == -1) leftEndIdx = j;
            if (i == 1) rightStartIdx = j;
        }
        int n = ds.size();
        // 从位置0开始，向左、向右各自找到第一块具有最大高度的隔板
        int leftHighest = leftEndIdx;
        for (int i = leftEndIdx - 1; i >= 0; i--)
            if (ds[i].height > ds[leftHighest].height)
                leftHighest = i;
        int rightHighest = rightStartIdx;
        for (int i = rightStartIdx + 1; i < n; i++)
            if (ds[i].height > ds[rightHighest].height)
                rightHighest = i;
                
        //cout << "Left First Highest: " << ds[leftHighest].p << ' ' << ds[leftHighest].idx << ' ' << ds[leftHighest].height << '\n';
        //cout << "Right First Highest: " << ds[rightHighest].p << ' ' << ds[rightHighest].idx << ' ' << ds[rightHighest].height << '\n';
    
        if (ds[leftHighest].height == ds[rightHighest].height) {
            int leftVolume = 0;
            int currentHighest = 0;
            for (int i = 1; i <= leftHighest; i++)
                if (ds[i].height >= ds[currentHighest].height) {
                    leftVolume += (ds[i].p - ds[currentHighest].p) * ds[currentHighest].height;
                    currentHighest = i;
                }
            int rightVolume = 0;
            currentHighest = n - 1;
            for (int i = n - 2; i >= rightHighest; i--)
                if (ds[i].height >= ds[currentHighest].height) {
                    rightVolume += (ds[currentHighest].p - ds[i].p) * ds[currentHighest].height;
                    currentHighest = i;
                }
            int elapsed = 2 * min(leftVolume, rightVolume) + (ds[rightHighest].p - ds[leftHighest].p) * ds[leftHighest].height;
            cout << elapsed << '\n';
        } else {
            // 如果左边高于右边，翻转，统一调整为右边高于左边
            if (ds[leftHighest].height > ds[rightHighest].height) {
                reverse(ds.begin(), ds.end());
                for (int i = 0; i < ds.size(); i++) {
                    ds[i].p = -ds[i].p;
                    ds[i].idx = i;
                }
                leftEndIdx = n - 1 - leftEndIdx;
                rightStartIdx = n - 1 - rightStartIdx;
                swap(leftEndIdx, rightStartIdx);
                leftHighest = n - 1 - leftHighest;
                rightHighest = n - 1 - rightHighest;
                swap(leftHighest, rightHighest);
            }

            // 由于右边高于左边，那么水必定从左侧溢出，确定时间
            // 首先确定左侧第一个出现的具有最高高度的隔板和
            // 右侧第一个出现的具有最高高度的隔板之间是否还存在影响水流动的隔板
            // 举个例子，假设左侧最先出现的具有最高高度的隔板高度为 3，
            // 右侧最先出现具有最高高度的隔板高度为 10，那么可以确定，水从左边流出，
            // 但是，这两个隔板之间，也就是位置 0 的右侧，可能存在隔板高度为 3 或者 5 的隔板，
            // 也就是说，水往右侧流动，可能无法到达高度为 10 的隔板，可能中途就被截止了，因此
            // 需要从位置 0 开始，往右找到第一个高度大于或等于左侧最高高度的隔板
            int firstKeyIdx = leftHighest;
            for (int i = rightStartIdx; i <= rightHighest; i++)
                if (ds[i].height >= ds[firstKeyIdx].height) {
                    firstKeyIdx = i;
                    break;
                }
                
            // 检查找到的隔板是否与左侧最高的隔板的高度相同，
            // 如果相同，则水会先填充两者之间的区域，之后再向两侧继续流动，
            // 否则的话，水只往左侧移动
            if (ds[firstKeyIdx].height == ds[leftHighest].height) {
                // 水先充盈两个等高隔板之间的空间，充盈速度为 1 单位体积每秒
                int elapsed = ds[leftHighest].height * (ds[firstKeyIdx].p - ds[leftHighest].p);
                
                // 等高隔板充盈后，水向两边充盈，充盈速度变为 0.5 单位体积每秒，此时需要
                // 检查左侧是否可以在右侧充盈完毕之前就已经溢出，如果左侧在右侧充盈完毕之前还未溢出
                // 那么左侧的充盈速度会恢复为 1 单位体积每秒
                
                // 先确定左侧需要充盈的单位体积
                int leftVolume = 0;
                int currentHighest = 0;
                for (int i = 1; i <= leftHighest; i++)
                    if (ds[i].height >= ds[currentHighest].height) {
                        leftVolume += (ds[i].p - ds[currentHighest].p) * ds[currentHighest].height;
                        currentHighest = i;
                    }
                    
                // 确定右侧隔板还需要充盈的单位体积，截止条件是找到一块具有更高高度的隔板，
                // 这肯定可以找到，因为我们处理的是右侧最高高度大于左侧最高高度的情形
                int rightVolume = 0;
                for (int i = firstKeyIdx + 1; i <= rightHighest; i++)
                    if (ds[i].height > ds[firstKeyIdx].height) {
                        rightVolume = ds[firstKeyIdx].height * (ds[i].p - ds[firstKeyIdx].p);
                        break;
                    }
                    
                // 比较左右两侧还需充盈的单位体积，如果左侧还需充盈的单位体积小于右侧，
                // 那么左侧一直以 0.5 单位体积每秒的速度充盈直到左侧溢出
                if (leftVolume <= rightVolume) elapsed += 2 * leftVolume;
                else {
                    // 右侧先以 0.5 单位体积每秒的速度充盈满，接着停止充盈，
                    // 左侧接着以 1 单位体积每秒的速度充盈，也就是说，
                    // 左侧先以 0.5 单位体积每秒的速度充盈 rightVolume 单位体积，再继续以
                    // 1 单位体积每秒的速度继续充盈 (leftVolume - rightVolume) 单位体积
                    // 最终就是左侧待充盈体积和右侧待充盈体积之和
                    elapsed += 2 * rightVolume + (leftVolume - rightVolume);
                }
                cout << elapsed << '\n';
            } else {
                int leftVolume = 0;
                int currentHighest = 0;
                for (int i = 1; i <= leftHighest; i++)
                    if (ds[i].height >= ds[currentHighest].height) {
                        leftVolume += (ds[i].p - ds[currentHighest].p) * ds[currentHighest].height;
                        currentHighest = i;
                    }
                int elapsed = leftVolume + ds[leftHighest].height * (ds[firstKeyIdx].p - ds[leftHighest].p);
                cout << elapsed << '\n';
            }
        }
    }

    return 0;
}
