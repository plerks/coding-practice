/*
url: https://leetcode.cn/problems/maximize-distance-to-closest-person/
LeetCode参考: https://leetcode.cn/problems/maximize-distance-to-closest-person/solutions/2393766/dao-zui-jin-de-ren-de-zui-da-ju-chi-by-l-zboe/
标签: 双指针
*/

public class Solution849 {
    public int maxDistToClosest(int[] seats) {
        int left = 0;
        while (seats[left] != 1) left++;
        int right = left;
        int ans = left - 0;
        while (true) {
            right++;
            if (right == seats.length) {
                ans = Math.max(ans, seats.length - 1 - left);
                break;
            }
            else if (seats[right] == 1) {
                ans = Math.max(ans, (right - left) / 2);
                left = right;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution849 solu = new Solution849();
        System.out.println(solu.maxDistToClosest(new int[]{1,0,0,0,1,0,1}));
    }
}