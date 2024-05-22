/*
url: https://leetcode.cn/problems/four-divisors/description/
LeetCode参考: https://leetcode.cn/problems/four-divisors/solutions/166486/si-yin-shu-by-leetcode-solution/
其它参考: https://oi-wiki.org/math/number-theory/sieve/
相关: 典型问题/质因数分解, 典型问题/筛法, LeetCode2867. 统计树中的合法路径数目
标签: 质因数分解, 数论, 埃拉托斯特尼筛法, 欧拉筛法
*/

import java.util.*;

public class Solution1390 {
    public int sumFourDivisors(int[] nums) {
        /* 考虑nums[i]的质因数分解，若nums[i]质因数分解为x1,x2,...xn，出现次数分别为a1,a2,...an(ai>=1)。
        质因数的组成唯一确定一个数，不同的质因数组成对应的数一定不相同。则nums[i]因数个数为(a1+1)(a2+1)...(an+1)。在每个质因数有0-ai种选择。
        则要恰有4个因数，则只能是2*2或者4，即质因数个数组成只能是1,1或者3个一样的。
        */
        int ans = 0;
        int[] primeFactors = new int[]{-1, -1, -1};
        for (int x : nums) {
            Arrays.fill(primeFactors, -1);
            int count = 0; // count为质因数个数
            for (int i = 2; i * i <= x; i++) {
                while (x % i == 0) {
                    count++;
                    if (count >= 4) { // x不会是4因数
                        x /= i;
                        break;
                    }
                    primeFactors[count - 1] = i;
                    x /= i;
                }
            }
            if (count >= 4) continue;
            else if (x != 1) {
                count++;
                if (count <= 3) {
                    primeFactors[count - 1] = x;
                }
            }
            if (count == 2 && primeFactors[0] != primeFactors[1]) {
                ans += 1 + primeFactors[0] + primeFactors[1] + primeFactors[0] * primeFactors[1];
            }
            else if (count == 3 && primeFactors[0] == primeFactors[1] && primeFactors[1] == primeFactors[2]) {
                ans += 1 + primeFactors[0] + primeFactors[0] * primeFactors[0] + primeFactors[0] * primeFactors[0] * primeFactors[0];
            }
        }
        return ans;
    }

    // 官方题解解法一，直接找因数
    public int sumFourDivisors_implementation2(int[] nums) {
        int ans = 0;
        for (int x : nums) {
            int factorCount = 0;
            int factorSum = 0;
            for (int i = 1; i * i <= x; i++) {
                if (x % i == 0) {
                    factorCount++;
                    if (factorCount > 4) break;
                    factorSum += i;
                    if (i * i != x) {
                        factorCount++;
                        if (factorCount > 4) break;
                        factorSum += x / i;
                    }
                }
            }
            if (factorCount == 4) ans += factorSum;
        }
        return ans;
    }

    /* 官方题解解法二，与sumFourDivisors()的分析相同，四因数的质因数情况为有一个指数为3的质因数或者有2个指数为1的质因数。
    现在考虑找出所有nums范围内的四因数与其因数和。从而需要找出范围内的所有质数，然后a*b或者c*c*c即是四因数。题解提供了使用
    埃拉托斯特尼筛法和欧拉筛法的写法，这里用埃拉托斯特尼筛法。
    */
    /* 这种解法的实际运行耗时挺长，主要原因应该是针对<=N的范围计算primes素数表和map用时长，而且评测系统运行用例时应该是针对
    每个用例new一个Solution对象，然后调用sumFourDivisors()，这样对每个用例都计算了primes和map，实际本身只需要计算一次，应该
    是因为这个所以这种解法效率不行。不过这题是头一次遇到用素数筛法的题。
    */
    public int sumFourDivisors_implementation3(int[] nums) {
        // 1 <= nums[i] <= 10^5
        int N = 100000, N3 = 46; // 46^3 < 100000，47^3 > 100000
        boolean[] isPrime = new boolean[N + 1];
        Arrays.fill(isPrime, true);
        List<Integer> primes = new ArrayList<>();
        // 这里筛法代码参考[oi wiki](https://oi-wiki.org/math/number-theory/sieve/)
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) { // 根据不变性，i还没被<i的范围内的数筛掉，说明这些数都不是i的因子，说明i是质数
                primes.add(i);
            }
            if ((long)i * i > N) continue; // 这里i * i可能溢出int范围，提前转long判断一下
            for (int j = i * i; j <= N; j += i) { // 这里不需要从2i开始筛，因为2的时候已经把2i筛了，直接从i*i筛
                isPrime[j] = false;
            }
        }
        Map<Integer, Integer> map = new HashMap<>(); // 记录四因数和其因数和
        for (int c : primes) {
            if (c > N3) break; // c*c*c已经超过nums[i]可能出现的范围，无需考虑
            map.put(c * c * c, 1 + c + c * c + c * c * c);
        }
        // 找a * b <= N的所有可能性，a b的可能范围都比较大，不像c*c*c的情况只需到N3
        for (int i = 0; i < primes.size(); i++) {
            for (int j = i + 1; j < primes.size(); j++) {
                int a = primes.get(i);
                int b = primes.get(j);
                /* 这里写成a <= N / b可以，写成a * b <= N就会超时，整数整除(b>0)意义下a * b <= N和a <= ⌊N / b⌋好像是等价的，
                若a * b <= N，则实数意义下等价于a <= N / b，而a是整数，实际就是a <= ⌊N / b⌋，
                若a <= ⌊N / b⌋，则显然a * b <= N，故等价。
                但是就是会超时，奇怪。
                */
                if (a <= N / b) {
                    map.put(a * b, 1 + a + b + a * b);
                }
                else break;
            }
        }
        int ans = 0;
        for (int num : nums) {
            if (map.containsKey(num)) {
                ans += map.get(num);
            }
        }
        return ans;
    }

    /* 针对sumFourDivisors_implementation3()重复计算isPrime和map的问题，在LeetCode2867. 统计树中的合法路径数目的官方题解中发现
    可以使用static代码块的方式解决，但是实际写成下面这样之后LeetCode上的运行用时没有改善，甚至用时还高了一些(37ms -> 41ms)，奇怪
    
    补充: 参考<https://leetcode.cn/circle/discuss/j3S2cz/>, <https://pangin.pro/posts/computation-in-static-initializer>
    好像Java的static代码块就是很慢。
    */

    // 1 <= nums[i] <= 10^5
    static int N = 100000, N3 = 46; // 46^3 < 100000，47^3 > 100000
    static boolean[] isPrime = new boolean[N + 1];
    static Map<Integer, Integer> map = new HashMap<>(); // 记录四因数和其因数和
    static {
        Arrays.fill(isPrime, true);
        List<Integer> primes = new ArrayList<>();
        // 这里筛法代码参考[oi wiki](https://oi-wiki.org/math/number-theory/sieve/)
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) { // 根据不变性，i还没被<i的范围内的数筛掉，是质数
                primes.add(i);
            }
            if ((long)i * i > N) continue; // 这里i * i可能溢出int范围，提前转long判断一下
            for (int j = i * i; j <= N; j += i) { // 这里不需要从2i开始筛，因为2的时候已经把2i筛了，直接从i*i筛
                isPrime[j] = false;
            }
        }
        for (int c : primes) {
            if (c > N3) break; // c*c*c已经超过nums[i]可能出现的范围，无需考虑
            map.put(c * c * c, 1 + c + c * c + c * c * c);
        }
        // 找a * b <= N的所有可能性，a b的可能范围都比较大，不像c*c*c的情况只需到N3
        for (int i = 0; i < primes.size(); i++) {
            for (int j = i + 1; j < primes.size(); j++) {
                int a = primes.get(i);
                int b = primes.get(j);
                /* 这里写成a <= N / b可以，写成a * b <= N就会超时，整数整除(b>0)意义下a * b <= N和a <= ⌊N / b⌋好像是等价的，
                若a * b <= N，则实数意义下等价于a <= N / b，而a是整数，实际就是a <= ⌊N / b⌋，
                若a <= ⌊N / b⌋，则显然a * b <= N，故等价。
                但是就是会超时，奇怪。
                */
                if (a <= N / b) {
                    map.put(a * b, 1 + a + b + a * b);
                }
                else break;
            }
        }
    }

    public int sumFourDivisors_implementation4(int[] nums) {
        int ans = 0;
        for (int num : nums) {
            if (map.containsKey(num)) {
                ans += map.get(num);
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1390 solu = new Solution1390();
        System.out.println(solu.sumFourDivisors(new int[]{21,4,7}));
        System.out.println(solu.sumFourDivisors_implementation2(new int[]{21,4,7}));
        System.out.println(solu.sumFourDivisors_implementation3(new int[]{21,4,7}));
        System.out.println(solu.sumFourDivisors_implementation4(new int[]{21,4,7}));
    }
}
