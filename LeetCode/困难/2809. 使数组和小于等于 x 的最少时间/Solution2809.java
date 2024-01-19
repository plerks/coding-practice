/*
url: https://leetcode.cn/problems/minimum-time-to-make-array-sum-at-most-x/description/?envType=daily-question&envId=2024-01-19
LeetCode参考: https://leetcode.cn/problems/minimum-time-to-make-array-sum-at-most-x/solutions/2607454/shi-shu-zu-he-xiao-yu-deng-yu-x-de-zui-s-fufg/
              https://leetcode.cn/problems/minimum-time-to-make-array-sum-at-most-x/solutions/2374920/jiao-ni-yi-bu-bu-si-kao-ben-ti-by-endles-2eho/
相关: 典型问题/背包问题/0-1背包问题
标签: 动态规划, 标号数组
*/

import java.util.Arrays;
import java.util.List;

public class Solution2809 {
    /* 我的想法，每次操作后的num1的和的增量按照如下变化：
    0
    deltaSum - nums1[i] - nums2[i]
    deltaSum - nums1[j] - 2 * nums2[j]
    ...
    假定每次的选取的下标互不相同（我没想出来怎么证，但是参考题解有说，如果两次操作同一个位置，则只需简单移除前一次操作），
    对于选取元素位置的策略，关键的减少在于d * nums2[k]上，因此将nums2排序，越大的值放后面，
    减少的量d * nums2[k]就大。这样做的问题是，这样能求出total的最小值，但是可能某一步操作后，某一个位置
    的num1[i]特别大，直接将其变为0，立刻能让总和<=x，根本不需要那么多步。

    操作n次之后，每个位置nums1[i]的成分都被清除，若还不能使和<=x(在按上文所证nums2的序删除的情况下)，在>=n+1的某次再做操作，以第n+1次为例，
    增加的量为deltaSum，减少的量为(n-出现编号(从1开始)+1)*nums2[i]，
    例如，若第一次删除的是nums1[i]，则其在第n+1次操作前积累了(n-1)次nums1[i]，第n+1次操作删除nums1[i]的话增量为deltaSum - n * nums1[i]>=0，其它位置同理。
    
    所以才要用dp换一种思路，第1次操作后能得到的最小值为多少，第2次操作后能得到的最小值为多少...而非只求第n次后能得到的最小值。
    对每个t，虽然知道要按nums2的值排序，但不知道具体应该选哪些数出来操作，因此是二维dp。
    */
    public int minimumTime_wrong(List<Integer> nums1, List<Integer> nums2, int x) {
        int total = 0;
        int n = nums1.size();
        Integer[] arr = new Integer[n];
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
        int deltaSum = 0;
        for (int i = 0; i < n; i++) {
            total += nums1.get(i);
            deltaSum += nums2.get(i);
        }
        Arrays.sort(arr, (i, j) -> {
            return nums2.get(i) - nums2.get(j);
        });
        for (int i = 0; i < n; i++) {
            total = total + deltaSum - nums1.get(arr[i]) - (i + 1) * nums2.get(arr[i]);
            if (total <= x) return i + 1;
        }
        return -1;
    }

    public int minimumTime(List<Integer> nums1, List<Integer> nums2, int x) {
        int n = nums1.size();
        Integer[] arr = new Integer[n]; // 用标号数组排序
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < n; i++) {
            arr[i] = i;
            sum1 += nums1.get(i);
            sum2 += nums2.get(i);
        }
        Arrays.sort(arr, (i, j) -> {
            return nums2.get(i) - nums2.get(j);
        });
        // 类似0-1背包问题，dp[i][t]表示从nums1[0, i]中选t个数出来操作能减小的最大值，0 <= t <= i <=n，分nums1[i]选不选两种情况
        int[][] dp = new int[n + 1][n + 1];
        for (int i = 1; i < n + 1; i++) {
            for (int t = 1; t <= i; t++) { // dp[i][t]只取决于上面和左上的值，与左侧无关，因此这里还可以写成for (int t = i; t > 0; t--)
                dp[i][t] = Math.max(dp[i - 1][t], dp[i - 1][t - 1] + nums1.get(arr[i - 1]) + t * nums2.get(arr[i - 1]));
            }
        }
        for (int t = 0; t < n + 1; t++) {
            if (sum1 + t * sum2 - dp[n][t] <= x) return t;
        }
        return -1;
    }

    // dp[i]状态只与dp[i - 1]有关，优化空间，去除i这个维度
    public int minimumTime_implementation2(List<Integer> nums1, List<Integer> nums2, int x) {
        int n = nums1.size();
        Integer[] arr = new Integer[n];
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < n; i++) {
            arr[i] = i;
            sum1 += nums1.get(i);
            sum2 += nums2.get(i);
        }
        Arrays.sort(arr, (i, j) -> {
            return nums2.get(i) - nums2.get(j);
        });
        int[] dp = new int[n + 1];
        for (int i = 1; i < n + 1; i++) {
            for (int t = i; t > 0; t--) { // 这个优化空间的技巧，t必须从大到小，这样dp[t - 1]刚好为上一行的dp[i - 1][t - 1]
                dp[t] = Math.max(dp[t], dp[t - 1] + nums1.get(arr[i - 1]) + t * nums2.get(arr[i - 1]));
            }
        }
        for (int t = 0; t < n + 1; t++) {
            if (sum1 + t * sum2 - dp[t] <= x) return t;
        }
        return -1;
    }

    /* 这个写法和minimumTime_implementation2()基本相似，但是放LeetCode上运行用时少很多，可能nums1和nums2实际类型是LinkedList，
    get(i)比较耗时，而minimumTime_implementation2()需要O(n^2)级别的get(i)?*/
    public int minimumTime_implementation3(List<Integer> nums1, List<Integer> nums2, int x) {
        int n = nums1.size();
        int sum1 = 0, sum2 = 0;
        int[][] pairs = new int[n][2];
        for (int i = 0; i < n; i++) {
            int a = nums1.get(i);
            int b = nums2.get(i);
            pairs[i][0] = a;
            pairs[i][1] = b;
            sum1 += a;
            sum2 += b;
        }
        Arrays.sort(pairs, (a, b) -> {
            return a[1] - b[1];
        });
        int[] dp = new int[n + 1];
        for (int i = 1; i < n + 1; i++) {
            for (int t = i; t > 0; t--) {
                dp[t] = Math.max(dp[t], dp[t - 1] + pairs[i - 1][0] + t * pairs[i - 1][1]);
            }
        }
        for (int t = 0; t < n + 1; t++) {
            if (sum1 + t * sum2 - dp[t] <= x) return t;
        }
        return -1;
    }

    public static void main(String[] args) {
        Solution2809 solu = new Solution2809();
        System.out.println(solu.minimumTime(Arrays.asList(1,2,3), Arrays.asList(1,2,3), 4));
        System.out.println(solu.minimumTime(Arrays.asList(7,9,8,5,8,3), Arrays.asList(0,1,4,2,3,1), 37));
        System.out.println(solu.minimumTime_implementation2(Arrays.asList(7,9,8,5,8,3), Arrays.asList(0,1,4,2,3,1), 37));
        System.out.println(solu.minimumTime_implementation3(Arrays.asList(7,9,8,5,8,3), Arrays.asList(0,1,4,2,3,1), 37));
    }
}
