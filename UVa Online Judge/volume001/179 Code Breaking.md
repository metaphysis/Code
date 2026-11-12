[UVa 179 Code Breaking](https://blog.csdn.net/metaphysis/article/details/160861147)

## 题目分析

题目描述了一种简单的加密方法：**周期置换加密**。给定一个周期 $k$ 和一个长度为 $k$ 的置换（即 $1$ 到 $k$ 的一个排列），将明文按 $k$ 个字符一组进行分组（最后一组不足时用 `?` 补齐），然后对每组应用该置换，得到密文。

输入包含若干个三元组 `(plaintext, ciphertext1, ciphertext2)`，每行一个字符串，以单独一行 `#` 结束。我们需要：

1. 判断是否存在某个周期 $k$ 和对应的置换，使得 `plaintext` 加密后得到 `ciphertext1`。
2. 如果存在，选择 **最小的 $k$**（题面保证此时置换唯一），然后将 `ciphertext2` 按照 **逆置换** 解密并输出（不足时补 `?`）。
3. 如果不存在这样的置换，则直接输出 `ciphertext2` 原样。

## 解题思路

### 1. 候选周期 $k$ 的筛选

对于某个 $k$，若存在一个置换将 `plaintext` 映射到 `ciphertext1`，则对于每个长度为 $k$ 的块（最后一组可以不足），块中字符的多重集必须相同。因为置换只是重新排列字符，不改变字符集合。

因此，我们可以枚举所有可能的 $k$（从 $1$ 到 `plaintext` 的长度），对每个 $k$ 将明文和密文按 $k$ 分组，比较每组的排序后结果是否一致。若所有组都一致，则 $k$ 是一个候选周期。

### 2. 验证置换的存在并找出最小 $k$

对于候选周期 $k$，需要判断是否存在一个长度为 $k$ 的置换将明文块映射到对应的密文块。由于 $k$ 较小（输入行长度不超过 $80$），我们可以采用以下两种方法：

- **全排列枚举**：当 $k \le 7$ 时，$k!$ 较小，可直接枚举所有排列进行验证。
- **回溯（$\texttt{DFS}$）匹配**：当 $k$ 较大时，利用每个位置上的字符对应关系进行约束回溯。因为一个置换将明文的第 $i$ 个字符映射到密文的第 $p(i)$ 个位置，实际上等价于寻找一个双射满足 `plaintext[i] == ciphertext1[p(i)]`。我们可以从第一个块中提取这种对应关系，然后递归构造置换。

由于 $k$ 从 $1$ 到 $n$ 递增进行尝试，第一个成功的就是最小的 $k$。

### 3. 解密 $\texttt{ciphertext2}$

找到置换后（存储在 `key` 数组中，`key[i]` 表示明文中第 $i$ 个字符在密文中的位置（从 $1$ 开始）），解密需要应用 **逆置换**：对于密文中的第 $j$ 个位置，它对应明文中的第 `pos[j]` 个位置。我们可以先求出逆置换 `inv`，然后按 $k$ 分组对 `ciphertext2` 进行解密，每组不足时用 `?` 补齐。

## 代码实现

```cpp
// Code Breaking
// UVa ID: 179
// Verdict: Accepted
// Submission Date: 2016-03-27
// UVa Run Time: 0.026s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

string plaintext, cyphertext1, cyphertext2;
vector<int> k, key;      // k存放所有候选周期，key存放找到的置换（1-indexed）

// 给定明文块，用当前key加密，返回密文块
string encrypt(string plain) {
    string encrypted(plain);
    for (int i = 0; i < (int)key.size(); i++)
        encrypted[key[i] - 1] = plain[i];
    return encrypted;
}

// 使用当前key对密文进行解密并输出（每组不足补?）
void decrypt(string encrypted) {
    int index = 0;
    int keyLength = key.size();
    int textLength = encrypted.length();

    while (index < textLength) {
        int subLength = min(keyLength, textLength - index);
        string subEncrypted = encrypted.substr(index, subLength);
        // 补全到keyLength长度，便于置换
        while ((int)subEncrypted.length() < keyLength)
            subEncrypted += '?';
        // 应用逆置换（key中存储的是正向映射，此处直接按正向输出即可）
        // 注意：这里的key在解密时实际上是正向映射，但因为我们加密时是encrypted[key[i]-1] = plain[i]
        // 所以解密时应该取encrypted的第j个字符放到plain的第?位，等价于正向映射本身。
        // 更准确地说，如果key[i]表示plain[i]去了密文的key[i]位置，则解密时密文位置key[i]-1的字符应回到i。
        // 这里的写法是直接按key索引输出，实际上是正确的，见题目样例验证。
        for (int i = 0; i < keyLength; i++)
            cout << subEncrypted[key[i] - 1];
        index += keyLength;
    }
}

// 验证当前key是否能将plaintext映射为cyphertext1
bool verifyKey() {
    int index = 0;
    int keyLength = key.size();
    int textLength = plaintext.length();

    while (index < textLength) {
        int subLength = min(keyLength, textLength - index);
        string subPlain = plaintext.substr(index, subLength);
        string subEncrypted = cyphertext1.substr(index, subLength);
        // 补全到keyLength长度
        while ((int)subPlain.length() < keyLength)
            subPlain += '?';
        while ((int)subEncrypted.length() < keyLength)
            subEncrypted += '?';
        if (encrypt(subPlain) != subEncrypted)
            return false;
        index += keyLength;
    }
    return true;
}

// 初始化key为[1,2,...,keyLength]
void initializeKey(int keyLength) {
    key.clear();
    for (int i = 1; i <= keyLength; i++)
        key.push_back(i);
}

// 小k时直接全排列验证
bool findPermutation(int keyLength) {
    initializeKey(keyLength);
    do {
        if (verifyKey())
            return true;
    } while (next_permutation(key.begin(), key.end()));
    return false;
}

// ---------- 回溯法找置换（大k时用） ----------
int maxTimesTry = 10000;   // 避免极端情况
int timesTried = 0;
bool keyFound = false, finish = false;
string source, target;     // 当前块的明文和密文
vector<bool> matched;      // 标记密文字符是否已被分配

void backtrack(int index, int keyLength) {
    if (index == keyLength) {
        if (verifyKey()) {
            keyFound = true;
            finish = true;
        }
        if (timesTried++ > maxTimesTry)
            finish = true;
        return;
    }

    // 明文第index个字符必须匹配密文的某个未被占用的位置的字符
    for (int i = 0; i < (int)target.length(); i++) {
        if (!matched[i] && source[index] == target[i]) {
            matched[i] = true;
            key[index] = i + 1;      // 置换值从1开始
            backtrack(index + 1, keyLength);
            if (finish) return;
            matched[i] = false;
        }
    }
}

// 利用第一个完整的块进行回溯匹配
bool findKeyByBacktrack(int keyLength) {
    // 找到第一个完整的块（长度等于keyLength）
    int index = 0;
    while (index < (int)plaintext.length()) {
        initializeKey(keyLength);
        finish = false;
        timesTried = 0;
        keyFound = false;
        source = plaintext.substr(index, keyLength);
        target = cyphertext1.substr(index, keyLength);
        if ((int)source.length() < keyLength) break;  // 最后一个不完整块不作为依据

        matched.assign(keyLength, false);
        backtrack(0, keyLength);

        if (keyFound) break;
        index += keyLength;
    }
    return keyFound;
}

// 在候选周期k中寻找可行置换
bool findKey() {
    for (int i = 0; i < (int)k.size(); i++) {
        // 小k直接全排列
        if (k[i] <= 7 && findPermutation(k[i]))
            return true;
        // 大k回溯
        if (findKeyByBacktrack(k[i]))
            return true;
    }
    return false;
}

// 筛选候选周期k（通过字符多重集比较）
bool findK() {
    k.clear();
    int keyLength = 1;
    int textLength = plaintext.length();
    while (keyLength <= textLength) {
        int index = 0;
        bool keyLengthMatched = true;
        while (index < textLength) {
            int subLength = min(keyLength, textLength - index);
            string subText1 = plaintext.substr(index, subLength);
            string subText2 = cyphertext1.substr(index, subLength);
            sort(subText1.begin(), subText1.end());
            sort(subText2.begin(), subText2.end());
            if (subText1 != subText2) {
                keyLengthMatched = false;
                break;
            }
            index += keyLength;
        }
        if (keyLengthMatched)
            k.push_back(keyLength);
        keyLength++;
    }
    return !k.empty();
}

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);

    while (getline(cin, plaintext), plaintext != "#") {
        getline(cin, cyphertext1);
        getline(cin, cyphertext2);

        if (findK() && findKey())
            decrypt(cyphertext2);
        else
            cout << cyphertext2;
        cout << "\n";
    }
    return 0;
}
```

## 算法复杂度

- 筛选候选 $k$：$O(n^2 \log n)$，$n$ 为字符串长度。
- 置换查找：小 $k$ 时 $O(k! \cdot n)$，大 $k$ 时通过回溯剪枝，实际效率很高。
- 整体可在输入规模下高效运行。

## 总结

本题的核心在于两点：

1. 利用 **字符多重集** 快速筛选可能的周期 $k$，避免无效枚举。
2. 对于给定的 $k$，通过 **置换匹配**（小范围枚举或回溯）确定具体的映射关系，并选择最小的可行 $k$。

解密时注意应用 **逆置换**，并正确处理末尾补 `?` 的情况。
