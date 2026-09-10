// Buddy Memory Allocator
// UVa ID: 827
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

struct Block {
    int size;
    char process; // 0 表示空闲
    int reqSize;  // 进程请求大小（仅当 process != 0）
};

class BuddyAllocator {
public:
    BuddyAllocator(int U, int L) {
        totalSize = 1 << U;
        minSize = 1 << L;
        blocks[0] = {totalSize, 0, 0};
        freeLists[totalSize].push_back(0);
        freeIter[0] = --freeLists[totalSize].end();
    }

    void allocateProcess(char P, int req) {
        int targetSize = 1;
        while (targetSize < req) targetSize <<= 1;
        if (targetSize < minSize) targetSize = minSize;

        // 若存在正好 targetSize 的空闲块，直接分配（取最近释放的尾部）
        if (!freeLists[targetSize].empty()) {
            int addr = freeLists[targetSize].back();
            freeLists[targetSize].pop_back();
            freeIter.erase(addr);
            blocks[addr].process = P;
            blocks[addr].reqSize = req;
            procAddress[P] = addr;
            return;
        }

        // 从更大的空闲块分裂
        int findSize = targetSize * 2;
        while (findSize <= totalSize) {
            if (!freeLists[findSize].empty()) {
                int addr = freeLists[findSize].back();
                freeLists[findSize].pop_back();
                freeIter.erase(addr);
                int curAddr = addr;
                int curSize = findSize;
                while (curSize > targetSize) {
                    int half = curSize / 2;
                    int leftAddr = curAddr;
                    int rightAddr = curAddr + half;
                    blocks.erase(curAddr); // 删除原块
                    blocks[leftAddr] = {half, 0, 0};
                    blocks[rightAddr] = {half, 0, 0};
                    freeLists[half].push_back(rightAddr);
                    freeIter[rightAddr] = --freeLists[half].end();
                    curAddr = leftAddr;
                    curSize = half;
                }
                // 最终左半块分配
                blocks[curAddr].process = P;
                blocks[curAddr].reqSize = req;
                procAddress[P] = curAddr;
                return;
            }
            findSize <<= 1;
        }
        // 题目保证总能分配，不会到达此处
    }

    void freeProcess(char P) {
        int addr = procAddress[P];
        procAddress.erase(P);
        Block &b = blocks[addr];
        int size = b.size;
        b.process = 0;
        b.reqSize = 0;
        // 尝试与伙伴合并
        while (true) {
            int buddy = addr ^ size;
            auto itBuddy = blocks.find(buddy);
            if (itBuddy != blocks.end() && itBuddy->second.process == 0 && itBuddy->second.size == size) {
                // 伙伴空闲，从空闲列表中删除伙伴
                auto iterIt = freeIter.find(buddy);
                if (iterIt != freeIter.end()) {
                    freeLists[size].erase(iterIt->second);
                    freeIter.erase(iterIt);
                }
                // 删除两个块
                blocks.erase(buddy);
                blocks.erase(addr);
                int newAddr = min(addr, buddy);
                int newSize = size * 2;
                blocks[newAddr] = {newSize, 0, 0};
                addr = newAddr;
                size = newSize;
            } else {
                // 不能合并，将当前块加入空闲列表（尾部即为最近释放）
                freeLists[size].push_back(addr);
                freeIter[addr] = --freeLists[size].end();
                break;
            }
        }
    }

    void printState() const {
        vector<int> addrs;
        addrs.reserve(blocks.size());
        for (const auto &kv : blocks) addrs.push_back(kv.first);
        sort(addrs.begin(), addrs.end());
        bool first = true;
        for (int addr : addrs) {
            const Block &b = blocks.at(addr);
            if (!first) cout << "\n";
            first = false;
            if (b.process == 0) cout << "Hole:" << b.size;
            else cout << b.process << ":" << b.reqSize;
        }
        cout << "\n";
    }

private:
    int totalSize;
    int minSize;
    unordered_map<int, Block> blocks;                     // 地址 -> 块信息
    unordered_map<int, list<int>> freeLists;              // 块大小 -> 空闲块地址列表（尾部为最近释放）
    unordered_map<int, list<int>::iterator> freeIter;     // 地址 -> 在对应空闲列表中的迭代器
    unordered_map<char, int> procAddress;                 // 进程标识 -> 分配的起始地址
};

int main() {
    int T;
    cin >> T;
    string line;
    getline(cin, line); // 消耗第一行后的换行
    string pendingLine = "";
    for (int caseIdx = 0; caseIdx < T; ++caseIdx) {
        string curLine;
        if (pendingLine.empty()) {
            do {
                getline(cin, curLine);
            } while (curLine.empty());
        } else {
            curLine = pendingLine;
            pendingLine = "";
        }
        stringstream ssCase(curLine);
        int U, L;
        ssCase >> U >> L;
        BuddyAllocator alloc(U, L);
        while (true) {
            if (pendingLine.empty()) {
                if (!getline(cin, line)) break;
            } else {
                line = pendingLine;
                pendingLine = "";
            }
            if (line.empty()) continue;
            size_t pos = line.find_first_not_of(" \t");
            if (pos == string::npos) continue;
            if (isupper(line[pos])) {
                stringstream ssReq(line);
                char P;
                int S;
                ssReq >> P >> S;
                if (S == 0) alloc.freeProcess(P);
                else alloc.allocateProcess(P, S);
            } else {
                pendingLine = line;
                break;
            }
        }
        if (caseIdx > 0) cout << "\n";
        alloc.printState();
    }
    return 0;
}
