/*
url: https://leetcode.cn/problems/power-of-two/description/
相关: LeetCode3154. 到达第 K 级台阶的方案数, LeetCode342. 4的幂
标签: 2的幂, n & (n - 1)的位运算特征
*/

class Solution231 {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
