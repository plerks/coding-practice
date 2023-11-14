// https://leetcode.cn/problems/maximum-sum-with-exactly-k-elements/?envType=daily-question&envId=2023-11-15

public class Solution2656 {
    public int maximizeSum(int[] nums, int k) {
        int max = Integer.MIN_VALUE;
        for (int i = 0; i < nums.length; i++) {
            max = Math.max(max, nums[i]);
        }
        return (max + max + k - 1) * k / 2;
    }

    public static void main(String[] args) {
        Solution2656 solu = new Solution2656();
        System.out.println(solu.maximizeSum(new int[]{1,2,3,4,5}, 3));
    }
}
