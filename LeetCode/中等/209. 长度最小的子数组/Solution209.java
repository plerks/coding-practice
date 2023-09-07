/*
url: https://leetcode.cn/problems/minimum-size-subarray-sum/
LeetCode题解: https://leetcode.cn/problems/minimum-size-subarray-sum/solutions/305704/chang-du-zui-xiao-de-zi-shu-zu-by-leetcode-solutio/
标签: 滑动窗口, 双指针, 前缀和
*/

public class Solution209 {
    public int minSubArrayLen(int target, int[] nums) {
        int sum = 0;
        int left = 0, right = 0;
        int ans = Integer.MAX_VALUE;
        /* 枚举候选子数组的左边界(0到nums.length-1)，若不够，则right还需往右移动，若此刻和>=target，则应该从下一个left位置开始重新枚举，
        但是nums的元素全为正整数，则下一个候选子数组的right一定在更右边，因此不需要将right移到left的位置重新开始往右移动。
        */
        while (right < nums.length) {
            sum += nums[right];
            if (sum >= target) {
                while (sum >= target) {
                    ans = Math.min(ans, right - left + 1);
                    sum -= nums[left];
                    left++;
                }
            }
            right++;
        }
        return ans == Integer.MAX_VALUE ? 0 : ans;
    }

    public static void main(String[] args) {
        Solution209 solu = new Solution209();
        System.out.println(solu.minSubArrayLen(7, new int[]{2,3,1,2,4,3}));
    }
}