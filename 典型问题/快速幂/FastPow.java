/*
描述: 在θ(logn)的时间内计算a^n的小技巧，而暴力的计算需要θ(n)的时间
参考: https://oi-wiki.org/math/binary-exponentiation/
相关: LeetCode1969. 数组元素的最小非零乘积
*/

public class FastPow {
    // 递归版
    public long fastPow(long a, long b) {
        if (b == 0) return 1;
        long res = fastPow(a, b / 2);
        if (b % 2 == 0) return res * res;
        else return a * res * res;
    }

    // 迭代版，一个帮助理解代码逻辑的例子是3^13 = 3^(0b1101) = 3^8 * 3^4 * 3^1
    public long fastPow_implementation2(long a, long b) {
        long res = 1;
        while (b > 0) {
            if ((b & 1) != 0) res = res * a;
            a = a * a;
            b >>= 1;
        }
        return res;
    }

    /* 这里[oi wiki](https://oi-wiki.org/math/binary-exponentiation/#%E6%A8%A1%E6%84%8F%E4%B9%89%E4%B8%8B%E5%8F%96%E5%B9%82)
    上还提到了一个计算x^n mod m的问题，取模的运算不会干涉乘法运算，即(a * b) % p = (a % p * b % p) % p。
    这个应该是用于x和x^n都较大，可能溢出数据范围，而m在数据范围内的情景，运用这个性质，上面代码(以迭代版为例)，a可以在进来时直接
    a %= m，res = res * a和a = a * a也可以改为res = res * a % m和a = a * a % m。

    LeetCode上经常会有这种，例如`LeetCode2731. 移动机器人`中："由于答案可能很大，请你将答案对10^9 + 7取余后返回"，题目可能需要涉及多次
    加减乘计算得出答案，但是，上面的性质并不意味着可以随便放%MOD，因为"取模的运算不会干涉乘法运算"这一性质并不考虑实际有溢出的问题，
    (a % MOD) * (b % MOD)和(a * b) % MOD，当a * b就直接溢出数据范围时还是不等的，因此遇到这种还是可能因为运算步骤写得不一样过不了用例，得对着
    官方题解来写运算步骤和%MOD的位置。
    */

    public static void main(String[] args) {
        FastPow fastPow = new FastPow();
        System.out.println(fastPow.fastPow(2, 10));
        System.out.println(fastPow.fastPow_implementation2(2, 10));

        /* int a = Integer.MAX_VALUE - 12;
        int b = Integer.MAX_VALUE - 73;
        final int MOD = 1000_000_007;
        System.out.println((a % MOD) * (b % MOD));
        System.out.println((a * b) % MOD); */
    }
}
