// Tobby Bones
// UVa ID: 13094
// Verdict: Accepted
// Submission Date: 2025-10-25
// UVa Run Time: 8.130s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int MAX_N = 600010;  // 最大槽位数
const int INF = 0x3f3f3f3f;  // 无穷大值，表示空槽位

class BoneShelf {
private:
    vector<int> originalArray;  // 原始数组，存储每个位置的骨头尺寸
    vector<int> sortedBlocks;   // 分块排序后的数组
    int blockSize;              // 每个块的大小
    int totalBlocks;            // 总块数
    
    // 在指定块中统计尺寸不超过 limit 的骨头数量
    int countInBlock(int blockIndex, int limit) {
        int blockStart = blockIndex * blockSize;
        int blockEnd = blockStart + blockSize;
        
        // 二分查找第一个大于 limit 的位置
        int left = blockStart, right = blockEnd;
        while (left < right) {
            int mid = (left + right) >> 1;
            if (sortedBlocks[mid] > limit) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return right - blockStart;  // 返回满足条件的元素个数
    }
    
    // 对指定块进行重新排序
    void sortBlock(int blockIndex) {
        int blockStart = blockIndex * blockSize;
        int blockEnd = min(blockStart + blockSize, (int)originalArray.size());
        
        // 将原数组数据拷贝到分块数组中
        for (int i = blockStart; i < blockEnd; i++) {
            sortedBlocks[i] = originalArray[i];
        }
        // 对当前块进行排序
        sort(sortedBlocks.begin() + blockStart, sortedBlocks.begin() + blockEnd);
    }
    
public:
    // 构造函数：初始化架子
    BoneShelf(int shelfSize) {
        originalArray.resize(shelfSize, INF);
        sortedBlocks.resize(shelfSize, INF);
        blockSize = sqrt(shelfSize);
        if (blockSize == 0) blockSize = 1;  // 防止除零错误
        totalBlocks = (shelfSize + blockSize - 1) / blockSize;
    }
    
    // 更新操作：在指定位置放置骨头
    void updateBone(int position, int boneSize) {
        originalArray[position] = boneSize;
        // 重新排序所在块
        sortBlock(position / blockSize);
    }
    
    // 查询操作：统计区间内尺寸不超过 limit 的骨头数量
    int queryExhibition(int left, int right, int limit) {
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;
        int count = 0;
        
        // 情况 1：查询区间完全在同一个块内
        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++) {
                if (originalArray[i] <= limit) {
                    count++;
                }
            }
            return count;
        }
        
        // 情况 2：查询区间跨越多个块
        // 2.1 处理左边界块
        int leftBlockEnd = (leftBlock + 1) * blockSize;
        for (int i = left; i < leftBlockEnd; i++) {
            if (originalArray[i] <= limit) {
                count++;
            }
        }
        
        // 2.2 处理中间完整块（使用二分查找优化）
        for (int blockIdx = leftBlock + 1; blockIdx < rightBlock; blockIdx++) {
            count += countInBlock(blockIdx, limit);
        }
        
        // 2.3 处理右边界块
        int rightBlockStart = rightBlock * blockSize;
        for (int i = rightBlockStart; i <= right; i++) {
            if (originalArray[i] <= limit) {
                count++;
            }
        }
        
        return count;
    }
};

int main() {
    int slotCount, operationCount;
    while (scanf("%d%d", &slotCount, &operationCount) != EOF) {
        BoneShelf shelf(slotCount);
        
        for (int i = 0; i < operationCount; i++) {
            int operationType, param1, param2, param3;
            scanf("%d%d%d", &operationType, ¶m1, ¶m2);
            
            if (operationType == 0) {
                // 更新操作：在位置 param1 放置尺寸为 param2 的骨头
                shelf.updateBone(param1, param2);
            } else {
                // 查询操作：区间 [param1, param2] 内尺寸不超过 param3 的骨头数量
                scanf("%d", ¶m3);
                printf("%d\n", shelf.queryExhibition(param1, param2, param3));
            }
        }
    }
    return 0;
}
