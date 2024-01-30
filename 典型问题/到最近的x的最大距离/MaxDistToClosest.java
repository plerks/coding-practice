/*
描述: 一个数组nums，其中某些元素是x，对nums的每个位置i，其离最近的x有一个距离，求这个距离能达到的最大值
相关: 典型问题/到最近的x的所有距离, LeetCode849. 到最近的人的最大距离, LeetCode2808. 使循环数组所有元素相等的最少秒数, LeetCode514. 自由之路, 典型问题/到最近的x的所有距离
*/

public class MaxDistToClosest {
    // 双指针，用left和right指向x出现的位置，但是要单独考虑x第一次出现的左侧和最后一次出现的右侧
    public int maxDistToClosest(int[] nums, int x) {
        int n = nums.length;
        int left = 0;
        while (nums[left] != x) left++;
        int ans = left;
        int right = left;
        while (true) {
            right++;
            if (right == n) {
                ans = Math.max(ans, n - 1 - left);
                break;
            }
            else if (nums[right] == x) {
                ans = Math.max(ans, (right - left) >> 1);
                left = right;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        MaxDistToClosest mdtc = new MaxDistToClosest();
        System.out.println(mdtc.maxDistToClosest(new int[]{1,0,0,0,1,0,1}, 1));
    }
}
