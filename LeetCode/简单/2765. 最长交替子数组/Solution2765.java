/*
url: https://leetcode.cn/problems/longest-alternating-subarray/description/?envType=daily-question&envId=2024-01-23
我的题解: https://leetcode.cn/problems/longest-alternating-subarray/solutions/2616302/yi-ge-xiao-wen-ti-guan-yu-wei-shi-yao-ke-ev72/
*/

public class Solution2765 {
    public int alternatingSubarray(int[] nums) {
        int ans = 0;
        int len = 1, currentDiff = -1;
        for (int i = 1; i < nums.length; i++) {
            int d = nums[i] - nums[i - 1];
            if (d == -currentDiff) { // 在交替
                len++;
                ans = Math.max(ans, len);
                currentDiff = -currentDiff;
            }
            else if (d == 1) { // 没交替，但是可以作为新的开头
                len = 2;
                currentDiff = 1;
            }
            else {
                len = 1;
                currentDiff = -1;
            }
        }
        return ans > 1 ? ans : -1;
    }

    public static void main(String[] args) {
        Solution2765 solu = new Solution2765();
        System.out.println(solu.alternatingSubarray(new int[]{1,2,2,1,2,3,6,2}));
    }
}
