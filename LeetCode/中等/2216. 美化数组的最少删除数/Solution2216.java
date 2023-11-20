// https://leetcode.cn/problems/minimum-deletions-to-make-array-beautiful/?envType=daily-question&envId=2023-11-21

public class Solution2216 {
    public int minDeletion(int[] nums) {
        int i = 0;
        int ans = 0;
        while (i < nums.length) {
            int j = i + 1;
            while (j < nums.length && nums[i] == nums[j]) {
                j++;
                ans++;
            }
            i = j + 1; // 下一个删除元素后的偶数位置
        }
        if ((nums.length - ans) % 2 == 1) ans++; // 题目要求美丽数组长度为偶数，若最后为奇数，删除最后一个元素
        return ans;
    }

    public static void main(String[] args) {
        Solution2216 solu = new Solution2216();
        System.out.println(solu.minDeletion(new int[]{1,1,2,2,3,3}));
    }
}
