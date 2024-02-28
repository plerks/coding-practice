/*
描述: 筛法求<=N范围内哪些是素数
参考: https://oi-wiki.org/math/number-theory/sieve/
相关: LeetCode204. 计数质数, LeetCode1390. 四因数, LeetCode2867. 统计树中的合法路径数目
*/

import java.util.*;

public class Sieve {
    // 埃拉托斯特尼筛法
    private List<Integer> sieve(int N) {
        boolean[] isPrime = new boolean[N + 1];
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        List<Integer> primes = new ArrayList<>();
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) { // 根据不变性，i还没被<i的范围内的数筛掉，说明这些数都不是i的因子，说明i是质数
                primes.add(i);
            }
            if ((long)i * i > N) continue; // 这里i * i可能溢出int范围，提前转long判断一下
            for (int j = i * i; j <= N; j += i) { // 这里不需要从2i开始筛，因为2的时候已经把2i筛了，直接从i*i筛
                isPrime[j] = false;
            }
        }
        return primes;
    }

    // 埃拉托斯特尼筛法，加上判偶
    private List<Integer> sieve_implementation2(int N) {
        boolean[] isPrime = new boolean[N + 1];
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        List<Integer> primes = new ArrayList<>();
        for (int i = 2; i <= N; i++) {
            if (i > 2 && i % 2 == 0) { // 偶数除了2，一定不是素数
                isPrime[i] = false;
                continue; // 不需再用i去筛右边，因为能被i筛掉的一定是偶数，那么那些数就算不筛后面也会被i % 2 == 0判断掉
            }
            if (isPrime[i]) {
                primes.add(i);
            }
            if ((long)i * i > N) continue;
            for (int j = i * i; j <= N; j += i) {
                isPrime[j] = false;
            }
        }
        return primes;
    }

    // 埃拉托斯特尼筛法，只筛至平方根
    // 只筛至平方根不好和判偶结合，这里如果循环里加上：
    /* if (i > 2 && i % 2 == 0) {
        isPrime[i] = false;
        continue;
    } */
    // 由于循环只到根号n，很多偶数没有机会被标记为isPrime[i] = false
    private List<Integer> sieve_implementation3(int N) {
        boolean[] isPrime = new boolean[N + 1];
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        List<Integer> primes = new ArrayList<>();
        /* 只需到用根号N筛，其实上面的写法当第一次i * i > N后后续都有i * i > N，所以相当于可以直接break。
        但是这样虽然isPrime是正确的，已经筛好了，i却没有遍历完[2, N]，为了填充primes需要单独再遍历一次。 */
        for (int i = 2; i * i <= N; i++) {
            for (int j = i * i; j <= N; j += i) {
                isPrime[j] = false;
            }
        }
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) primes.add(i);
        }
        return primes;
    }

    // 欧拉筛法，也称线性筛法，埃拉托斯特尼筛法会将一个合数多次标记，欧拉筛法可以避免这个问题
    private List<Integer> sieve_implementation4(int N) {
        boolean[] isPrime = new boolean[N + 1];
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        List<Integer> primes = new ArrayList<>();
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.add(i);
            }
            for (int prime : primes) {
                if (i * prime > N) break;
                /* primes存了<=i的素数，筛的过程是
                2 * primes[0], 2 * primes[1].., 2 * primes[size]
                3 * primes'[0], 3 * primes'[1].., 3 * primes'[size']
                4 * primes''[0], 4 * primes''[1].., 4 * primes''[size'']
                */
                isPrime[i * prime] = false;
                /* 为什么这里i % prime == 0直接break了，不再去筛i * 后面的prime？
                因为i是prime的倍数，则i * 后面的prime一定会是break时候的prime的倍数，
                则在后面的行一定会通过prime的更大倍数把之前没筛掉的i * 后面的prime筛掉。
                这样一来一个合数只会由其因子中最小的素数筛掉，因此避免了一个合数被多次标记。(oi wiki没详细解释欧拉筛法为什么能避免一个合数被多次标记，应该是这样)
                */
                if (i % prime == 0) {
                    break;
                }
            }
        }
        return primes;
    }
    public static void main(String[] args) {
        Sieve sieve = new Sieve();
        System.out.println(sieve.sieve(10));
        System.out.println(sieve.sieve_implementation2(10));
        System.out.println(sieve.sieve_implementation3(10));
        System.out.println(sieve.sieve_implementation4(10));
    }
}
