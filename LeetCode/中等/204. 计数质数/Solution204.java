/*
url: https://leetcode.cn/problems/count-primes/description/
相关: 典型问题/筛法, LeetCode1390. 四因数, LeetCode2867. 统计树中的合法路径数目
标签: 数论, 埃拉托斯特尼筛法, 欧拉筛法
*/

import java.util.*;

public class Solution204 {
    // 埃拉托斯特尼筛法
    public int countPrimes(int n) {
        int N = n - 1; // 题目是求<n范围内的
        boolean[] isPrime = new boolean[N + 1];
        Arrays.fill(isPrime, true);
        int count = 0;
        // 这里筛法代码参考[oi wiki](https://oi-wiki.org/math/number-theory/sieve/)
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) { // 根据不变性，i还没被<i的范围内的数筛掉，说明这些数都不是i的因子，说明i是质数
                count++;
            }
            if ((long)i * i > N) continue; // 这里i * i可能溢出int范围，提前转long判断一下
            for (int j = i * i; j <= N; j += i) { // 这里不需要从2i开始筛，因为2的时候已经把2i筛了，直接从i*i筛
                isPrime[j] = false;
            }
        }
        return count;
    }

    // 埃拉托斯特尼筛法，只筛至平方根
    public int countPrimes_implementation2(int n) {
        int N = n - 1;
        boolean[] isPrime = new boolean[N + 1];
        Arrays.fill(isPrime, true);
        int count = 0;
        /* 只需到用根号N筛，其实上面的写法当第一次i * i > N后后续都有i * i > N，所以相当于可以直接break。
        但是这样虽然isPrime是正确的，i却没有遍历完[2, N]，count没计数全，需要单独再遍历一次。 */
        for (int i = 2; i * i <= N; i++) {
            for (int j = i * i; j <= N; j += i) {
                isPrime[j] = false;
            }
        }
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) count++;
        }
        return count;
    }

    // 埃拉托斯特尼筛法，加上判偶
    public int countPrimes_implementation3(int n) {
        int N = n - 1;
        boolean[] isPrime = new boolean[N + 1];
        Arrays.fill(isPrime, true);
        int count = 0;
        for (int i = 2; i <= N; i++) {
            if (i > 2 && i % 2 == 0) { // 偶数除了2，一定不是素数
                isPrime[i] = false;
                continue; // 不需再用i去筛右边，因为能被i筛掉的一定是偶数，那么那些数就算不筛后面也会被i % 2 == 0判断掉
            }
            if (isPrime[i]) {
                count++;
            }
            if ((long)i * i > N) continue;
            for (int j = i * i; j <= N; j += i) {
                isPrime[j] = false;
            }
        }
        return count;
    }

    // 欧拉筛法
    public int countPrimes_implementation4(int n) {
        int N = n - 1;
        boolean[] isPrime = new boolean[N + 1];
        Arrays.fill(isPrime, true);
        List<Integer> primes = new ArrayList<>();
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.add(i);
            }
            for (int prime : primes) {
                if (i * prime > N) break;
                isPrime[i * prime] = false;
                if (i % prime == 0) {
                    break;
                }
            }
        }
        return primes.size();
    }

    public static void main(String[] args) {
        Solution204 solu = new Solution204();
        System.out.println(solu.countPrimes(10));
        System.out.println(solu.countPrimes_implementation2(10));
        System.out.println(solu.countPrimes_implementation3(10));
        System.out.println(solu.countPrimes_implementation4(10));
    }
}
