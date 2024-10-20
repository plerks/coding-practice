/*
url: https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/description/
LeetCode参考: https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/solutions/1501230/zui-shao-yi-dong-ci-shu-shi-shu-zu-yuan-xt3r2/
相关: LeetCode215. 数组中的第K个最大元素, 典型问题/k选取, LeetCodeLCP 24. 数字游戏
标签: k选取, 中位数, 快速排序
*/

// 此题使用`LeetCode215. 数组中的第K个最大元素`，`LeetCodeLCP 24. 数字游戏`使用到此题
public class Solution462 {
    /* 最终要变化为的值x为nums的中位数，若nums.length为奇数，则x为排好序后中间那个数，若nums.length为偶数，则x选[下中位数, 上中位数]范围内任一个值都可。
    假设最终变化为x，则开销为Σ|nums[i]-x|，相当于数轴上的点nums[i]到x的距离之和。对于nums排好序后的数组S，将S[0], S[n - 1]和S[1], S[n - 2]，...配对考虑，x在中间时和最小，
    从而有以上结论。
    */
    public int minMoves2(int[] nums) {
        int n = nums.length;
        int x = kSelect(nums, n / 2); // n为奇，上下中位数在n/2重合；n为偶，n/2为上中位数
        int ans = 0;
        for (int i = 0; i < n; i++) ans += Math.abs(x - nums[i]);
        return ans;
    }

    public int kSelect(int[] nums, int k) {
        int lo = 0, hi = nums.length - 1;
        while (lo < hi) {
            int i = lo, j = hi;
            // 这里选择随不随机在LeetCode上跑，用时有明显差别
            int rand = (int)(Math.random() * (hi - lo + 1)) + lo;
            int t = nums[lo];
            nums[lo] = nums[rand];
            nums[rand] = t;
            int pivot = nums[lo];
            while (i < j) {
                while (i < j && nums[j] > pivot) j--;
                if (i < j) nums[i++] = nums[j];
                while (i < j && nums[i] < pivot) i++;
                if (i < j) nums[j--] = nums[i];
            }
            nums[i] = pivot;
            if (i == k) return nums[i];
            else if (i > k) hi = i - 1;
            else lo = i + 1;
        }
        return nums[lo];
    }

    public static void main(String[] args) {
        Solution462 solu = new Solution462();
        System.out.println(solu.minMoves2(new int[]{1,10,2,9}));
    }
}
