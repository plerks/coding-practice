/*
url: https://leetcode.cn/problems/power-of-heroes/
LeetCode参考: https://leetcode.cn/problems/power-of-heroes/solutions/2367175/python3javacgotypescript-yi-ti-yi-jie-pa-lgos/
我的题解: https://leetcode.cn/problems/power-of-heroes/solutions/2367734/can-kao-ling-yi-wei-de-ti-jie-xie-yi-xia-kciv/
*/

import java.util.Arrays;

/*
要对nums的所有非空子集进行计算，每个子集起作用的为最小值和最大值，先排序。

每个以a[i]为最小值的子集对最终的值的贡献分两部分，一部分是选出的子集为{a[i]}时，贡献为ai^3，只有一项，系数为1。

另外一种情况是ai和其它项组合，现求以a[i]为最小值，a[n]为最大值的子集个数。

若子集有2项，则有一种情况{a[i],a[n]}，若有3项，则有Cn-i-1,1种(从(i,n)中选一项)，这样递推下去，一共1+Cn-i-1,1+Cn-i-1,2+...+1 = 2^(n-i-1)种情况(二项式定理)。
即，以ai为最小值的子集对最终值的贡献为ai*(ai^2+a[i+1]^2+2*a[i+2]^2+...+2^n-i-1*an^2)。

这里的2^n-i-1，还有一种理解方式，以a[i]为最小值，a[n]为最大值，中间一共n-i-1个空位，每个空位可选可不选，一共2^n-i-1种情况。

为了计算，从右往左遍历nums，为了计算和其它项组合的部分，需要用到这样变化的项p：0, a[n]^2, 2*a[n]^2 + a[n-1]^2, 4a[n]^2 + 2a[n-1]^2 + a[n-2]^2...

每次累加先加a[i]^3，再加a[i]*p，这两项即为以a[i]为最小值的子集对最终的值的贡献。

另一种思路是，以a[i]为最大值的子集对最终值的贡献为a[i]^3 + a[i]^2 * a[i-1] + ... + 2^(i-1)a[i]^2a[1]。
此时应从左向右遍历nums，p应该这样变化：0, a[1], 2a[1] + a[2], 4a[1] + 2a[2] + a[3], ...
*/

public class Solution2681 {
    public int sumOfPower(int[] nums) {
        Arrays.sort(nums);
        long ans = 0;
        long p = 0;
        int mod = (int)1e9 + 7;
        for (int i = nums.length - 1; i >= 0; i--) {
            long x = nums[i]; // 必须将nums[i]转为long, 否则x * x就会溢出int
            // ans = ((ans + (x * x % mod) * x) % mod + (p * x % mod)) % mod;
            ans = (ans + (x * x % mod) * x) % mod;
            ans = (ans + p * x % mod) % mod;
            p = (p * 2 % mod + x * x % mod) % mod;
        }
        return (int)ans;
    }

    public int sumOfPower_implementation2(int[] nums) {
        Arrays.sort(nums);
        long ans = 0;
        long p = 0;
        int mod = (int)1e9 + 7;
        for (int i = 0; i < nums.length; i++) {
            long x = nums[i]; // 必须将nums[i]转为long, 否则x * x就会溢出int
            ans = (ans + (x * x % mod) * x) % mod;
            ans = (ans + (p * x) % mod * x % mod) % mod;
            p = (p * 2 % mod + x) % mod;
        }
        return (int)ans;
    }

    public static void main(String[] args) {
        Solution2681 solu = new Solution2681();
        System.out.println(solu.sumOfPower(new int[]{1, 2, 4}));
        System.out.println(solu.sumOfPower_implementation2(new int[]{1, 2, 4}));
    }
}