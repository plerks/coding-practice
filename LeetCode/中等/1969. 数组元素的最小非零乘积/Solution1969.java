/*
url: https://leetcode.cn/problems/minimum-non-zero-product-of-the-array-elements/description/?envType=daily-question&envId=2024-03-20
LeetCode参考: https://leetcode.cn/problems/minimum-non-zero-product-of-the-array-elements/solutions/936621/tan-xin-ji-qi-shu-xue-zheng-ming-by-endl-uumv/
              https://leetcode.cn/problems/minimum-non-zero-product-of-the-array-elements/solutions/2688955/shu-zu-yuan-su-de-zui-xiao-fei-ling-chen-xti0/
相关: 典型问题/快速幂
标签: 数学, 快速幂
*/

public class Solution1969 {
    /* 我能想到的：对于两个数形如1a和0b，何时应该选择交换?
    交换前，乘积为(2^k + a) * b = b * 2^k + ab，交换后，乘积为a * (2^k + b) = a * 2^k + ab。这样看来
    当a小时，应当实施交换，当a大时应该不交换，然后不知道该怎么继续做。
    */

    /* 参考题解，应当尽量把1给别人凑大，把0给自己凑小。
    原数组除去最后的2^p-1，其余可以两两配对，即i和2^p-1-i进行配对，其相加为2^p-1(二进制位全1)，说明二者数位互补，则可以完美使用上述规则，
    将二者变为1(最后一位为1，题目要求乘积非0)和2^p-2(除最后一位其它位全为1)。最终有2^(p-1)-1个{1,2^p-2}对和一个2^p-1。答案为(2^p-2)^(2^(p-1)-1) * (2^p-1)
    */

    final long MOD = (long)1e9 + 7;

    public int minNonZeroProduct(int p) {
        long t = 1L << p; // 1 <= p <= 60，2^p在long范围内
        long x = fastPow((t - 2) % MOD, (t >> 1) - 1);
        return (int)((t - 1) % MOD * x % MOD);
    }

    // 快速幂
    private long fastPow(long a, long b) {
        long res = 1;
        while (b > 0) {
            if ((b & 1) != 0) {
                res = res * a % MOD;
            }
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    public static void main(String[] args) {
        Solution1969 solu = new Solution1969();
        System.out.println(solu.minNonZeroProduct(3));
    }
}
