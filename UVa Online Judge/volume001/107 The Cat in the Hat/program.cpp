// The Cat in the Hat
// UVa ID: 107
// Verdict: Accepted
// Submission Date: 2011-11-23
// UVa Run Time: 1.132s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 由于题目并未指明输入数据的范围，所以只有摸着石头过河。本题解是基于输入数据在 32 
// 位整数以内的假设。
//
// 当工作的猫只有一只时，则每顶帽子内只有一只猫或者只有初始给定的那只猫。当只有初始
// 给定的那只猫时，对应的输入应该是：1，1。
// 当每顶帽子只有一只猫时，对应的输入应该是：x，1。其中 x 为 2 的幂。这两种特殊情况
// 可以分开来解决。
//
// 对于一般的情况，设帽子的嵌套层数为 M，每只帽子内的猫数量为 N，初始猫高度为 A，工
// 作的猫数量为 B，则有下列方程成立（B >= 2，N >= 2，M >= 1）：
//
// （N + 1）^M = A
//  N^M = B
//
// 那么很明显，A 和 B 均是大于 1 的合数。假如输入数据在 32 位整数范围内，那么 A 和
// B 都可以分解为小于 2^16 的素数的乘积。对于 A 的分解，假设分解式为
//
// A = a^k * b^l * c^m * ... * g^q.
//
// 那么由于 A 是一个数的 M 次幂，则必有 A 的素因子的指数都是 M 的倍数。同样的，B 的
// 素因子分解式中，各素因子的指数同样是 M 的倍数，那么 M 必为所有素因子指数的最大公
// 约数（为什么？只需证明 N + 1 和 N 的素因子分解式中所有指数的最大公约数为 1 即可，
// 用反证法证明，假设 N + 1 和 N 的素因子分解式中，所有指数的最大公约数为一个大于 1
// 的数 w，那么不妨设：N + 1 = a^w，N = b^w，有
// a^w - b^w = 1，a，b，w >= 2，且为整数
// 又由于 N + 1 > N，故有 a > b，不妨设 a = b + x
// 其中 x >= 1，那么有
// （b + x）^w - b^w = 1，由于 w >= 2，x >= 1，则根据二项式定理，上式不可能成立）。
//
// 那么可以将 A 和 B 进行素因子分解，用求所有指数最大公约数的方法求得 M，进而根据素
// 因子分解的结果求得 N。
//
// 如果输入数据超出 32 位整数范围，只要素数分解的算法不是太慢，应该也能使用此种方法
// 解决，不过随着给定数据范围的加大，素数增多，就不能使用预先生成指定范围内素数的办
// 法，应该转而寻求其他不是太低效的办法。
//
// 另外一种解题的方法是根据方程使用二分法搜索 M 和 N 的值，这种方法我没有具体尝试过。

#include <bits/stdc++.h>

using namespace std;

#define MAXINT (1 << 16)
#define MAXN 6600

int prime[MAXN], nPrime = 0, factor[MAXN];

// 素数判定。
bool isPrime(int x)
{
    if (x <= 1)
        return false;

    if (x == 2)
        return true;

    if (x & 1)
    {
        int top = sqrt(x);
        for (int i = 3; i <= top; i += 2)
            if (x % i)
                continue;
            else
                return false;
        return true;
    }
    else
        return false;
}

// 生成指定范围内的所有素数。
void getPrime(void)
{
    for (int i = 2; i <= MAXINT; i++)
        if (isPrime(i))
            prime[nPrime++] = i;
}

// 求最大公约数。
int gcd(int x, int y)
{
    return x < y ? gcd(y, x) : (y ? gcd(y, x % y) : x);
}

// 素因子分解并求指数的最大公约数。
int factoring(int x)
{
    int y = 0;

    memset(factor, 0, sizeof(factor));

    for (int i = 0; i < nPrime && x > 1; i++)
        while (x % prime[i] == 0)
        {
            factor[i]++;
            x /= prime[i];
        }

    for (int i = 0; i < MAXN; i++)
        if (factor[i])
        {
            if (y)
                y = gcd(y, factor[i]);
            else
                y = factor[i];
        }

    return y;
}

// 特例处理。
void specialCase(int initCatHeight, int workerCatsNumber)
{
    if (initCatHeight == 1)
        cout << "0 1" << endl;
    else
    {
        int nest = 1;
        for (int i = 2; i < initCatHeight; i *= 2, nest++)
            ;
        cout << nest << " " << (pow(2, nest + 1) - 1) << endl;
    }
}

int main(int argc, char const *argv[])
{
    int nest, n;

    getPrime();

    int initCatHeight, workerCatsNumber;
    while (cin >> initCatHeight >> workerCatsNumber, initCatHeight
        || workerCatsNumber)
    {
        // 特例处理。
        if (workerCatsNumber == 1)
        {
            specialCase(initCatHeight, workerCatsNumber);
            continue;
        }

        // 利用素因子分解求嵌套层数。
        nest = factoring(initCatHeight);
        nest = gcd(nest, factoring(workerCatsNumber));

        // 利用素因子分解结果和嵌套层数求 N。
        n = 1;
        for (int i = 0; i < MAXN; i++)
            if (factor[i])
                n *= pow(prime[i], factor[i] / nest);

        // 求未工作的猫数量和所有猫的高度总和。
        int unworkCatsNumber = 0, totalHeight = 0;
        while (workerCatsNumber > 1)
        {
            workerCatsNumber /= n;
            unworkCatsNumber += workerCatsNumber;
        }

        int exponent = 1;
        while (initCatHeight >= 1)
        {
            totalHeight += initCatHeight * exponent;
            exponent *= n;
            initCatHeight /= (n + 1);
        }

        // 输出。
        cout << unworkCatsNumber << " " << totalHeight << endl;
    }

    return 0;
}
