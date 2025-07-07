/*
url: https://leetcode.cn/problems/gray-code/
参考: https://leetcode.cn/problems/gray-code/solutions/13637/gray-code-jing-xiang-fan-she-fa-by-jyd/
      https://leetcode.cn/problems/gray-code/solutions/1198215/gong-shui-san-xie-dui-cheng-xing-gou-zao-9ap1/
相关: LeetCode1238. 循环码排列, LeetCode1611. 使整数变为 0 的最少操作次数
标签: 【算法题单】位运算, 格雷码构造, 格雷码公式
*/
#include <bits/stdc++.h>

using namespace std;

class Solution89 {
public:
    /* 参考题解<https://leetcode.cn/problems/gray-code/solutions/13637/gray-code-jing-xiang-fan-she-fa-by-jyd/>，
    如何构造格雷码？
    假如已经有了 n 位的格雷码序列(2^n个数)，如何构造 n + 1 位的格雷码序列？
    1. 将原有的 2^n 个数首位补0
    2. 对于原有的 2^n 个数的翻转序列，首位补1
    例如，00 01 11 10
    1. 首位补0，得到 000 001 011 010
    2. 翻转得到 10 11 01 00，首位补1，得到 110 111 101 100
    于是，3位的格雷码序列为 000 001 011 010 110 111 101 100
    
    这样做的正确性：
    假如原有序列为 G = [g0, g1, ... , gk]
    那么后半段为 G = [1 + gk, ... , 1 + g0]
    两部分合并，[g0, g1, ... , gk, 1 + gk, ... , 1 + g0] 是否满足格雷码的性质？
    前半部分和后半部分都是满足的，gk和1 + gk也是满足的，g0和1+g0也是满足的。所以，得到了加一位的格雷码。
    */
    vector<int> grayCode(int n) {
        vector<int> ans;
        ans.push_back(0); // n位的格雷码有2^n个数，这个0相当于0位的格雷码
        for (int i = 0; i < n; i++) { // 位数
            int sz = ans.size();
            for (int j = sz - 1; j >= 0; j--) { // 上一步的序列倒序遍历，相当于翻转
                ans.push_back((1 << i) | ans[j]);
            }
        }
        return ans;
    }

    /* 上面的方法新增的一位在首位，宫水三叶题解里新增的一位在末尾：
    (其实也可以往中间插位，例如在从左往右第二位插：
    [00 01 11 10] 翻转序列为 [10 11 01 00]，中间插位(0x0)
    [000 001 101 100] [110 111 011 010] 也是可以的，不过没必要选中间的位置)

    这也说明了，格雷码不止一种方案。不过一般是grayCode()/grayCode_implementation3()生成的序列。
    */
    vector<int> grayCode_implementation2(int n) {
        vector<int> ans;
        ans.push_back(0);
        while (n-- > 0) {
            int sz = ans.size();
            for (int j = sz - 1; j >= 0; j--) {
                ans[j] <<= 1; // 原序列末尾插0
                ans.push_back(ans[j] | 1); // 原序列末尾插1得到第二部分
            }
        }
        return ans;
    }

    // 参考题解评论区的解法<https://leetcode.cn/problems/gray-code/solutions/13637/gray-code-jing-xiang-fan-she-fa-by-jyd/comments/1035072/>
    /* 格雷码是有公式的：
    n位的格雷码，编号从0到2^n - 1，则第i个格雷码：
    
    gray(i) = i ^ (i >> 1)
    直接从编号就可以得到gray码的值

    怎么证明这个公式的正确性？
    直观上来看，i ^ (i >> 1) 的结果相当于 gray(i) 的值为：编号 i 的首位不变，其余位为 i的这一位 ^ i的高一位 的结果。
    那么此公式得到的 gray(i) 和 gray(i + 1) ，是否只有一位不同？
    是的，考虑 i + 1 和 i 的关系，+1 会产生进位，进位可能连锁发生，但是进位这一路上每位都反转了，直到结束的那位。
    相邻位都反转，异或结果(相异性)是不变的，于是，gray(i + 1) 相对 gray(i)，只有进位结束的那位的值会改变，符合格雷码的定义。
    还需看 gray(0) 和 gray(2^n - 1) 是否满足格雷码定义(2^n - 1 + 1，会溢出n位)，容易知道二者分别为 00..0 和 10..0 ，也是满足的。
    */
    vector<int> grayCode_implementation3(int n) {
        vector<int> ans(1 << n);
        // 编号为i的格雷码为 i ^ (i >> 1) (0 <= i <= 2^n - 1)
        for (int i = 0; i < (1 << n); i++) ans[i] = i ^ (i >> 1);
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution89 solu;
    auto a = solu.grayCode(2);
    auto b = solu.grayCode_implementation2(2);
    auto c = solu.grayCode_implementation3(2);
    return 0;
}