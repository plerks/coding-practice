/*
url: https://leetcode.cn/problems/find-the-k-sum-of-an-array/description/?envType=daily-question&envId=2024-03-09
LeetCode参考: https://leetcode.cn/problems/find-the-k-sum-of-an-array/solutions/1764389/zhuan-huan-dui-by-endlesscheng-8yiq/
              https://leetcode.cn/problems/find-the-k-sum-of-an-array/solutions/2668280/zhao-chu-shu-zu-de-di-k-da-he-by-leetcod-z5kq/
标签: 子序列和, 子序列和递增生成, k子序列和选取
*/

import java.util.*;

/* 这题难度大，且两个解法都非常精彩，无论是解法一的剪枝细节还是解法二能直接递增生成子序列和，都非常奇妙。
这题能和LeetCode2127. 参加会议的最多员工数, LeetCode466. 统计重复个数相提并论。
*/
public class Solution2386 {
    /* 第k个最大子序列和，将nums所有非负数加起来得到sum，sum为最大的子序列。
    那么nums的所有子序列，都相当于从sum中减去非负或者加上负数得到。
    将nums所有元素取绝对值，则无论是减去非负还是加上负数，都可以统一为减去|nums[i]|，
    sum减去的数越小，对应的子序列和越大。
    因此，等价于变成了求nums取绝对值后的第k小（很关键）。
    */

    /* 灵茶山艾府题解解法一，暴力搜索，但是加上二分的技巧，二分搜索|nums|的第k小的序列和的值x，
    x越大，|nums|和小于等于x的子序列个数越大，于是，对于是否有k个子序列，其和<=x，x的取值
    范围区间呈现[否...是]变化，第一个是的位置就是|nums|第k小的子序列和。
    由于问题变成了求nums取绝对值后的第k小，那么虽然要暴力2的指数级搜索，但是一旦对x找
    够k个，或者和已经大于x(需要排序)，则可以不用递归下去，从而剪枝。这题1 <= k <= min(2000, 2^n)，k不算大。
    */
    int count = 0;

    public long kSum(int[] nums, int k) {
        long sum = 0;
        long right = 0; // 二分右边界为nums所有元素绝对值之和
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] >= 0) sum += nums[i];
            else nums[i] = -nums[i];
            right += nums[i];
        }
        /* 这里排序是要为后面的子序列选取剪枝做准备，非常关键！如果不先排序，对[4,2,2]，x==2，第一个选4就return;不再递归下去了，
        但是实际可以放弃4，后面选出[2]。这里排完序后再做子序列选取实际是优先选小的，当|nums[i]|>x导致子序列不能选|nums[i]|时，实际
        可以考虑选后面更小的数，这样是不能剪枝的，排序的话就可以剪枝了。
        */
        Arrays.sort(nums); // 排序后的|nums|选出的子序列也是排序前的|nums|的子序列，只要把元素的相对顺序还原即可
        long left = 0;
        // 闭区间写法
        while (left <= right) {
            long mid = (left + right) / 2;
            count = k - 1; // 这里是k - 1，因为下面dfs()会漏掉全不选的情况
            dfs(0, mid, nums);
            if (count == 0) { // 够k个
                right = mid - 1;
            }
            else left = mid + 1;
        }
        return sum - left;
    }

    /* 这里的dfs类似求幂集的递归，但是有奇妙的不同。
    这里并不是在递归终点才考虑结果，而是直接就count--;了，这样为什么不会导致：第一个位置不选和所有位置不选（得到的是同一子序列），两种情况重复计数？
    这里count--;考虑的情况是选出|nums[i]|，若|nums[i]|能选则选，但是要分选i和不选i两种情况递归下去。
    */
    private void dfs(int i, long x, int[] nums) {
        // 剪枝，需要先把|nums|排序，非常关键！
        if (count == 0 || i == nums.length || nums[i] > x) {
            return;
        }
        count--; // 这里count--代表选上|nums[i]|，子序列和<=x，所以可以选，但是后面|nums[i]|选和没选两种情况都要考虑
        // 考虑在i位置选或不选两种情况
        dfs(i + 1, x - nums[i], nums); // 选i
        dfs(i + 1, x, nums); // 不选i
    }

    // 灵茶山艾府题解解法二。子序列和居然是有办法可以依次递增生成的！
    public long kSum_implementation2(int[] nums, int k) {
        long sum = 0;
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] >= 0) sum += nums[i];
            else nums[i] = -nums[i];
        }
        Arrays.sort(nums); // 要排序
        PriorityQueue<long[]> q = new PriorityQueue<>((x, y) -> x[0] < y[0] ? -1 : 1);
        q.offer(new long[]{0, 0});
        while (--k > 0) { // 这里要--k而不是k--应该是因为要提前减去全空的那个子序列
            long[] arr = q.poll();
            long s = arr[0];
            int i = (int)arr[1]; // i为子序列最后一个元素的下标
            if (i < nums.length) {
                q.offer(new long[]{s + nums[i], i + 1}); // 加一个，加上下一个位置的数
                if (i > 0) {
                    q.offer(new long[]{s + nums[i] - nums[i - 1], i + 1}); // 换一个，把最后一个元素换成下一个位置的数
                }
            }
        }
        return sum - q.peek()[0];
    }

    public static void main(String[] args) {
        Solution2386 solu = new Solution2386();
        System.out.println(solu.kSum(new int[]{2,4,-2}, 5));
        System.out.println(solu.kSum_implementation2(new int[]{2,4,-2}, 5));
    }
}
