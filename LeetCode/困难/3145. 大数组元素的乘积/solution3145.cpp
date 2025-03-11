/*
url: https://leetcode.cn/problems/find-products-of-elements-of-big-array/description/
LeetCode参考: https://leetcode.cn/problems/find-products-of-elements-of-big-array/solutions/2774549/olog-shi-tian-fa-pythonjavacgo-by-endles-w2l4/
              https://www.bilibili.com/video/BV1cz421m786/
              https://leetcode.cn/circle/discuss/dHn9Vk/
相关: LeetCode3470. 全排列 IV
标签: LeetCode第130场双周赛, 数学, 试填法
*/

// 这次双周赛做出前3题

#include <bits/stdc++.h>

using namespace std;

class Solution3145 {
public:
    /* 参考灵茶山艾府题解，一个数的强数组是其2进制的1拆出来，考虑2^n形式的数为分隔线，
    0的强数组为[]

    1的强数组为[1]

    2的强数组为[2]
    3的强数组为[1, 2]
    
    4的强数组为[4]
    5的强数组为[1, 4]
    6的强数组为[2, 4]
    7的强数组为[1, 2, 4]
    
    8的强数组为[8]
    ...

    设a(i)为前2^i个强数组总共有多少个数(或者说2^i这个数前面[0, 2^i - 1]这些正整数的强数组有多少个数)
    则a(i) = 2 * a(i - 1) + 2^(i - 1)，a(0) = 0，a(1) = 1 ...
    两边除以2^(i - 1)，a(i) / 2^(i - 1)为公差为1的等差数列，解出来a(n) = n * 2^(n - 1)
    或者这样定义，ones(n)为[0, n - 1]中的数字的二进制中1的总个数，则ones(2^i) = i * 2^(i - 1)，注意当2^i == 1即i == 0时不符合，得i >= 1

    各个强数组连起来构成big_nums，题目要求的是big_nums[from - to]的乘积，因此关心的是强数组中的数是2的多少幂次，也就是要直到指数之和。

    0的强数组指数为[]

    1的强数组指数为[0]

    2的强数组指数为[1]
    3的强数组指数为[0, 1]
    
    4的强数组指数为[2]
    5的强数组指数为[0, 2]
    6的强数组指数为[1, 2]
    7的强数组指数为[0, 1, 2]
    
    8的强数组指数为[3]

    记b(n)为前2^i个强数组的指数之和(或者说2^i这个数前面[0, 2^i - 1]这些正整数的强数组的数的指数之和)，则对与要求前2^i个强数组的指数之和，其是前2^(i-1)个强数组赋值一份，然后后一半的2^(i-1)每个多一个i-1
    于是，b(i) = 2 * b(i - 1) + (i - 1) * 2^(i - 1)，b(0) = 0
    两边同除以2^(i - 1)，解出来b(n) = n(n-1)/2 * 2^(n-1)，注意n == 0时不成立，得n >= 1

    对于某个query，包含两个位置from和to，要求的是big_nums[from] * ... * big_nums[to]，big_nums的数都是以2为底，因此实际是要求
    [from, to]的big_nums的和，这可以转化成前缀和相减

    对于位置k，需要直到big_nums[0, k]的和，big_nums[0, k]涵盖到的是一些数的强数组和某个数的强数组的一部分。
    我们期望求的是，k在哪个数n的强数组里。

    用的做法是[试填法](https://leetcode.cn/circle/discuss/dHn9Vk/)，也就是从高位开始不断试每个数位，然后看ones(n)和k的关系

    上面求出了当n为2的幂次时，ones(2^i)的公式，我们先找k里的指数规模，也就是先找对于2^i，i最大为多大，使得ones(n) <= k
    再去试填低位。

    比如k为10，
    当n = 2^3时，ones(2^3) = 3 * 2^2 = 12，超过k，不行
    当n = 2^2时，ones(2^2) = 4 < k，说明k = 10的位置在第2^2个强数组和2^3个强数组之间

    再找k = 10具体是在哪个数的强数组里面，

    现在n为100，试填为110，增加了谁的强数组？
    增加了100和101的强数组，它俩的强数组有几个数？
    高位都是1，增加了1 * 2 + [00, 01]的强数组的数的个数(也是0和1的二进制中1的个数)，[00, 01]的强数组的数的个数是前2^1个强数组的数的个数，这可以套ones公式

    于是，若是110，则[0, 110 - 1]的强数组的数的总数为4 + 1 * 2 + ones(2^1) = 7

    现在n是110，再尝试能不能最后一位填1，最后一位填1，增加的数字是110，同理，高位有2个1，增加的数是在低位遍取，增加的数是7 + 2 * 1 + ones(2^0) = 9 < 10，可以填

    也就是说，加入现在n试填为了1011000，现在要尝试第2个0能不能填1，也就是1011100，新引入的正整数范围为[1011000, 1011100),
    要计算这些数的强数组的数的个数，也就是计算这些数中1的个数，这些数高位都是1011不变，低位是从000到100 - 1变化，刚好是ones(100)的定义

    目前为止计数为9，n为111，意思是0，1，... 6的强数组的数的个数为9，然后继续往下再找剩余的，这里只需从7的强数组里再找一个数就行。

    我们知道了如何找k在哪个数的强数组里面，但是关键要求的是big_nums前k个数的和，如何求？
    上面找位置的过程中可以同步去求，第一步找到2^i时，可以用b(n)的公式求前面的和，然后试填的过程中，例如
    "这些数高位都是1011不变，低位是从000到100 - 1变化"，这是用1011000乘数的个数 + b(100)

    求出指数和之和，用快速幂计算2的幂次即可

    注意: 当某个位置试填1时，例如1011*000，*位置填1，实际考虑的正整数范围是[0, 10110111]，没有包含10111000，这很关键

    */

    /* 这题真的麻，巨难搞。
    回过头来看，当把
    1
    2
    3
    4
    5
    ...
    的强数组列出来后，对于query[to]，[0, to]有to + 1个数，于是想到，要把big_nums第to + 1个数找到，首先考虑的是整的强数组
    有多少。也就是，覆盖的整的正整数有多少个([1, n - 1]是完整的强数组)，然后再用n的强数组，补其中的0个或多个数。在找位置的过程中，也要注意，题目要求
    的是big_nums[from] * ... * big_nums[to]，于是在过程中，还需要求指数之和。
    求n考虑用试填法，当n的某一位xxx*000取1时，其相对上一步，增加了[xxx0000, xxx1000)的正整数的强数组，刚好2^3个，
    这些正整数的强数组构成如何？
    高位的2的幂次都是有的，然后低位则是[0, 1000)的强数组的个数，这可以通过对2^i的i考虑，发现递推关系，求出公式。
    总之，这题入手点应该是在考虑用试填法求出big_nums[to]在哪个正整数的强数组的哪个位置，试填这个n的每一位，然后会顺着考虑出a(n)和b(n)

    参考题解还提了个变式，题目中求的是big_nums[from] * ... * big_nums[to]，如果改成求big_nums[from] + ... + big_nums[to]要怎么做？
    求big_nums之和要简单点，一个数的强数组之和就是等于这个数的值，找到n的位置，[0, n - 1]的强数组之和就是1 + 2 + ... + (n - 1)，然后余下
    的部分单独处理即可。
    */
    vector<int> findProductsOfElements(vector<vector<long long>>& queries) {
        vector<int> ans;
        for (auto &query : queries) {
            long long sum1 = sum(query[1] + 1); // 找big_nums[0 ... to]的和，注意: 一共to + 1个数的和，**传进去的是强数组的数的个数**
            long long sum2 = sum(query[0]);
            // 用快速幂算
            ans.push_back(pow(2, sum1 - sum2, query[2]));
        }
        return ans;
    }

    long long sum(long long k) {
        long long n = 0; // n为现在填成的数，我们要找的是[0, n)的强数组的数的个数 + n的强数组的一部分数 个数刚好为k个
        long long ans = 0; // 强数组的数的指数之和
        // cntOne是已经填了的1的个数，sumI为已经填了的1对应的2的指数之和，例如现在填成10110000，前面部分有3个1，3个1对应的指数之和是4+5+7
        long long cntOne = 0, sumI = 0;
        long long totalCount = 0; // totalCount为强数组的数的总数
        /* __builtin_clzll()当输入为0时是ub，所以k加上1，k + 1 >= 1，i从63 - __builtin_clzll(k + 1)
        的位置开始试填，因为当i > 63 - __builtin_clzll(k + 1)时，n在这种i位置不可能为1，否则[1, n]
        每个数强数组至少为1，数的个数一定大于k
        */
        for (long long i = 63 - __builtin_clzll(k + 1); i > 0; i--) {
            /* i位置填1，新增高位不变，当前位为1，低位从0...00到1...11的正整数，
            也就是1011*000，*位置填1，增加的正整数是10111000 - 10111111。
            新增的强数组的数的个数是这些数中1的个数，增加的正整数个数为2^3，高位都是相同的，
            因此记录高位有多少个1，再用数的个数相乘，低位则是ones(2^3)
            */
            // c为这次试填1，新增的强数组数的个数，c = (cntOne * 2^i) + ones(2^i)。实际是算出了[0, 10111000)的强数组数的个数以及幂次之和
            long long c = (cntOne << i) + (i << (i - 1));
            if (totalCount + c <= k) { // i位置可填1，求强数组数的个数和幂次之和
                totalCount += c;
                // 某个位置填1，新增的正整数个数为2^i
                ans += (sumI << i) + ((i * (i - 1) / 2) << (i - 1)); // sumI * 2^i + b(i)
                sumI += i;
                cntOne++;
                n |= 1LL << i;
            }
        }
        // a(n)和b(n)都得i >= 1时才成立，所以最低位单独判断能否填1
        // 最低位填1，增加的正整数是xxx...xx0
        if (cntOne + totalCount <= k) {
            totalCount += cntOne;
            ans += sumI;
            sumI += 0;
            cntOne++;
            n |= 1LL << 0;
        }
        while (totalCount < k) {
            ans += __builtin_ctzll(n);
            n = n & (n - 1); // 这里是每次取n最低位的1，然后把最低位1变0，也就是用n中的2^i来补最后几个数，直到k
            totalCount++;
        }
        return ans;
    }

    long long pow(long a, long b, int mod) {
        long res = 1;
        while (b > 0) {
            if ((b & 1) != 0) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res % mod;
    }
};

int main(int argc, char const *argv[]) {
    Solution3145 solu;
    vector<vector<long long>> queries = {{2,5,3},{7,7,4}};
    solu.findProductsOfElements(queries);
    return 0;
}
