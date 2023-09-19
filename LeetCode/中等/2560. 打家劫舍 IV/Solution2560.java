/*
url: https://leetcode.cn/problems/house-robber-iv/?envType=daily-question&envId=2023-09-19
LeetCode参考: https://leetcode.cn/problems/house-robber-iv/solutions/2093952/er-fen-da-an-dp-by-endlesscheng-m558/
标签: 二分, 贪心, 动态规划
*/

public class Solution2560 {
    public int minCapability(int[] nums, int k) {
        int left = 1, right = 0;
        for (int val : nums) {
            right = Math.max(right, val);
        }
        // 二分列举窃取能力
        while (left < right) {
            int mid = (left + right) / 2;
            if (check(nums, mid, k)) {
                right = mid;
            }
            else left = mid + 1;
        }
        return right;
    }

    private boolean check(int[] nums, int x, int k) {
        int count = 0;
        /* 贪心检测当选<=x的数时能否偷够k间房屋。贪心的正确性在于，如果有异于贪心的序列能选更多个房屋（例如贪心方式选了i，另外一个序列不选i），
        则这第二个序列一定会选i+1，否则若其从i+2开始选，则贪心序列也能这样选，第二个序列选的数量不会更优。而其选了i+1之后，必须从i+3开始继续选，
        而贪心序列同样可以对i+3的位置开始做一样的选择，第二个序列能选的房屋数量不会比贪心序列更大，因此贪心序列能达到最大选择数量。
        也能用动态规划来求只能偷<=x的房间下能偷的最大房间数量。
        */
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] <= x) {
                count++;
                i++;
            }
        }
        return count >= k; // 对于限制金额为x的情况能否偷到k间房屋
    }

    public static void main(String[] args) {
        Solution2560 solu = new Solution2560();
        System.out.println(solu.minCapability(new int[]{2,3,5,9}, 2));
    }
}