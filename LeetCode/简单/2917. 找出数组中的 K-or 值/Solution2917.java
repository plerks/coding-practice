// https://leetcode.cn/problems/find-the-k-or-of-an-array/description/?envType=daily-question&envId=2024-03-06

public class Solution2917 {
    public int findKOr(int[] nums, int k) {
        int[] count = new int[32];
        for (int x : nums) {
            for (int i = 0; i < 32; i++) {
                if ((x & (1 << i)) > 0) {
                    count[i]++;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < 32; i++) {
            if (count[i] >= k) {
                ans |= (1 << i);
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2917 solu = new Solution2917();
        System.out.println(solu.findKOr(new int[]{7,12,9,8,9,15}, 4));
    }
}
