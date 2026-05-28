# Cricket Ranking
# UVa ID: 10458
# Verdict: Accepted
# Submission Date: 2026-05-28
# UVa Run Time: 0.020s
#
# 版权所有（C）2026，邱秋。metaphysis # yeah dot net

import sys
import math

def solve() -> None:
    data = sys.stdin.read().strip().split()
    if not data:
        return
    
    idx = 0
    results = []
    
    while idx < len(data):
        # 读取 K 和 N
        K = int(data[idx]); idx += 1
        N = int(data[idx]); idx += 1
        
        L = []
        U = []
        sumL = 0
        sumU = 0
        
        for _ in range(K):
            l = int(data[idx]); idx += 1
            u = int(data[idx]); idx += 1
            L.append(l)
            U.append(u)
            sumL += l
            sumU += u
        
        # 无解情况：最小值之和 > N 或 最大值之和 < N
        if sumL > N or sumU < N:
            results.append("0")
            continue
        
        S = N - sumL
        
        # 计算每个部门的可变化范围
        R = [U[i] - L[i] for i in range(K)]
        
        # 容斥原理
        ans = 0
        # 遍历所有子集 (2^K 种)
        for mask in range(1 << K):
            sumR = 0
            bits = 0
            for i in range(K):
                if mask >> i & 1:
                    sumR += R[i] + 1
                    bits += 1
            
            T = S - sumR
            if T < 0:
                continue
            
            # 计算组合数 C(T + K - 1, K - 1)
            n = T + K - 1
            k = K - 1
            
            if k == 0:
                # 只有一个部门时，组合数为 1（如果 T>=0）
                c = 1 if T >= 0 else 0
            else:
                if n < k:
                    c = 0
                else:
                    c = math.comb(n, k)
            
            if bits % 2 == 0:
                ans += c
            else:
                ans -= c
        
        results.append(str(ans))
    
    print("\n".join(results))

if __name__ == "__main__":
    solve()
