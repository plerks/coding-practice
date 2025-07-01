/*
url: https://leetcode.cn/problems/find-xor-beauty-of-array/
参考: https://leetcode.cn/problems/find-xor-beauty-of-array/solutions/2050235/chai-wei-hua-jian-cheng-yi-ge-piao-liang-pun6/
相关: LeetCode2317. 操作后的最大异或和
标签: 【算法题单】位运算, 拆位
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2527 {
public:
    /* 参考灵茶题解：位运算经典技巧：由于每个比特位互不相干，所以拆分成每个比特位分别计算。拆位
    (a|b)&c，对异或有影响的是1，所以(a, b, c)的组合，在每位上有多少个1？
    (a|b)&c为1，则c为1，且a,b至少一个1，此题0 <= i, j, k < n，假设nums某位总共y个1，则有n-y个0，
    (a|b)&c为1总共有 y * (n^2 - (n - y)^2) = 2ny^2 + y^3。
    把这些1异或起来，只需考虑个数，2ny^2为偶数，y^3的奇偶性与y的奇偶性相同（分y=2k/2k+1二项式展开即可），
    所以，答案为nums所有元素异或起来就行。

    题解中提到了一个变式，把此题的「异或」换成「求和」，怎么做？
    对求和有影响的也只是1，知道了一位的1的个数为2ny^2 + y^3，再乘位的权值 1 << i，最后再把每位的结果加起来即可。
    */
    int xorBeauty(vector<int>& nums) {
        int ans = 0;
        for (int& x : nums) ans ^= x;
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2527 solu;
    cout << solu.xorBeauty(*new vector<int>{1, 4}) << endl;
    return 0;
}