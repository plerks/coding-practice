/*
url: https://leetcode.cn/problems/factorial-trailing-zeroes/description/
LeetCode参考: https://leetcode.cn/problems/factorial-trailing-zeroes/solutions/1360892/jie-cheng-hou-de-ling-by-leetcode-soluti-1egk/
相关: 典型问题/质因数分解
标签: 阶乘, 质因数分解, 数论, [2,n]中质因子p的个数, 勒让德定理
*/

import java.util.*;

public class Solution172 {
    public int trailingZeroes(int n) {
        /* n!形如xxx...000，分为xxx...和1000...，则第一部分不能为10的倍数，第二部分为多个10相乘。
        考虑做质因数分解，则第一部分不能同时有2和5，第二部分为成对的2和5。则最终答案为2和5的出现次数的较小者。
        */
        Map<Integer, Integer> map = new HashMap<>();
        // 质因数分解的过程，外循环n次，对每个i分解最坏j一直++，需要j次，时间复杂度O(n^2)
        for (int i = 2; i <= n; i++) { // 对n!中每个数做分解
            int x = i;
            int j = 2; // 轮到分解出j时，若j不是质数，则x中j的质因子的部分已在之前被分解出，x除以j一定不会是整数，因此不需要担心分解出一个4是因子这样
            while (x != 1) {
                if (x % j == 0) {
                    map.put(j, map.getOrDefault(j, 0) + 1);
                    x /= j;
                }
                else {
                    j++;
                }
            }
        }
        return Math.min(map.getOrDefault(2, 0), map.getOrDefault(5, 0));
    }

    // 只关心2和5，因此不用做完全的质因数分解
    public int trailingZeroes_implementation2(int n) {
        int count2 = 0, count5 = 0; // 因数中2和5的个数
        // 时间复杂度取决于2和5的个数，但循环至少会执行n次，时间复杂度Ω(n)
        for (int i = 2; i <= n; i++) {
            int x = i;
            while (x % 2 == 0) {
                count2++;
                x /= 2;
            }
            while (x % 5 == 0) {
                count5++;
                x /= 5;
            }
        }
        return Math.min(count2, count5);
    }

    /* 考虑2能出现在2...n哪些数中，考虑2: 2*1,2*2...,2*(n/2)。
        考虑4: 4*1,...,4*(n/4)
        考虑8: 8*1,...8*(n/2)
        但是2的倍数里也会有4的倍数，这部分重复不知道怎么办
    */

    /* 参考题解的解法二，考虑2和5能出现在2...n哪些数中是对的，但是计数时需要技巧，单纯考虑能有1个2的，2个2的，3个2的，
    不知道怎么处理重复的计算。但是可以这样，当计算完2的倍数个数后，对于能成为4的倍数的，不应想着这些数有2个2(这样会去考虑这轮能有2*(n/4)个2，但是无法处理一部分数是上一轮2的倍数的问题)，
    而是这些数是上一轮数的子集(4的倍数必定是2的倍数)，但是由于他们能整除4，于是这部分数相对上一轮能添(n/4)个2，同理可以这样迭代下去。
    因此，对于求[2,n]中质因子p的个数，有这样的结论:
    [2,n]中质因子p的个数为⌊n/p⌋ + ⌊n/p^2⌋ + ⌊n/p^3⌋ + ⌊n/p^4⌋ + ⌊n/p^5⌋ + ...
    若p不是质数结论是否仍然成立？不行，例如9!里面至少一个27，但是按上面算出来会是0。归其原因在于若p是质数，则2*3*...*n中拆p一定是从2,3,...n中
    单独拆出来的，而不像9!与27的情况，27可以从3*9出来。
    */
    public int trailingZeroes_implementation3(int n) {
        // 根据推出来的公式，2...n中因子5的个数一定比2的少(或者相等)(n不变，p越大，质因子个数越少)，因此只需考虑计算有多少个5
        // 时间复杂度O(logn)
        int ans = 0;
        while (n / 5 > 0) {
            ans += n / 5;
            n /= 5;
        }
        return ans;
    }

    // 参考题解的解法一，和trailingZeroes_implementation2()差不多，但是有了参考题解的结论，只需考虑5即可（5个数比2少），且能更精准地分析时间复杂度
    public int trailingZeroes_implementation4(int n) {
        int ans = 0;
        // 由结论，[2,n]中质因子p的个数为⌊n/p⌋ + ⌊n/p^2⌋ + ⌊n/p^3⌋ + ⌊n/p^4⌋ + ⌊n/p^5⌋ + ... = O(n)，则能确定时间复杂度为O(n)，不会更高
        for (int i = 2; i <= n; i++) {
            int x = i;
            while (x % 5 == 0) {
                ans++;
                x /= 5;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution172 solu = new Solution172();
        System.out.println(solu.trailingZeroes(5));
        System.out.println(solu.trailingZeroes_implementation2(5));
        System.out.println(solu.trailingZeroes_implementation3(5));
        System.out.println(solu.trailingZeroes_implementation4(5));
    }
}
