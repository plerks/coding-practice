/*
描述: 质因数分解，对N求出所有质因数
参考: https://oi-wiki.org/math/number-theory/pollard-rho/
相关: LeetCode172. 阶乘后的零, LeetCode1390. 四因数
待做: [oi wiki](https://oi-wiki.org/math/number-theory/pollard-rho/#pollard-rho-%E7%AE%97%E6%B3%95)上还有个Pollard Rho算法，以后再说
*/

import java.util.*;

public class PrimeFactorization {
    // 朴素算法，计算每个因子有多少个。时间复杂度O(N)，虽然N在循环过程中会减小，但是例如N本身为质数，外循环会跑满。
    public List<Integer> primeFactorization(int N) {
        List<Integer> ans = new ArrayList<>();
        for (int i = 2; i <= N; i++) { // 轮到分解出i时，若i不是质数，则N中i的质因子的部分已在之前被分解出，x除以i一定不会是整数，因此不需要担心当i循环到合数时把i分解出来
            while (N % i == 0) {
                ans.add(i);
                N /= i;
            }
        }
        return ans;
    }

    // 朴素算法2，时间复杂度O(N^{1/2})，参考<https://oi-wiki.org/math/number-theory/pollard-rho/#%E6%9C%B4%E7%B4%A0%E7%AE%97%E6%B3%95>
    public List<Integer> primeFactorization_implementation2(int N) {
        List<Integer> ans = new ArrayList<>();
        /* 质因数会成对存在，一个在[2, N^{1/2}]，一个在[N^{1/2}, N - 1)，除非N当前已经是质数，
        每次循环，对当时的N找出了较小的一个，漏了较大的一个，所以循环结束后要单独判断一次。
        */
        for (int i = 2; i * i <= N; i++) {
            while (N % i == 0) {
                ans.add(i);
                N /= i;
            }
        }
        if (N != 1) { // N经过操作之后留下了一个素数
            ans.add(N);
        }
        return ans;
    }

    public static void main(String[] args) {
        PrimeFactorization pf = new PrimeFactorization();
        System.out.println(pf.primeFactorization(120));
        System.out.println(pf.primeFactorization_implementation2(120));
    }
}
