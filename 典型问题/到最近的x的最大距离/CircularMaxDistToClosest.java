/*
描述: 和MaxDistToClosest.java类似，一个数组nums，其中某些元素是x，对nums的每个位置i，其离最近的x有一个距离，求这个距离能达到的最大值，区别在于数组是首尾相接的循环数组。
相关: 典型问题/到最近的x的所有距离, LeetCode849. 到最近的人的最大距离, LeetCode2808. 使循环数组所有元素相等的最少秒数, LeetCode514. 自由之路
*/

import java.util.*;

public class CircularMaxDistToClosest {
    /* 最简明的做法，遍历一遍nums用一个list记录x出现的下标，然后逐对计算，对于数组是循环数组的特殊性，只需单独计算一次x第一次出现和最后一次出现位置的距离，
    或者在list末尾增加一个n+x第一次出现的index，然后当数组不循环做。
    循环数组不需要考虑x第一次出现的左侧和最后一次出现的右侧这种情况。 */
    public int maxDistToClosest(int[] nums, int x) {
        int n = nums.length;
        List<Integer> list = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (nums[i] == x) list.add(i);
        }
        int max = 0;
        for (int i = 1; i < list.size(); i++) {
            max = Math.max(max, list.get(i) - list.get(i - 1));
        }
        max = Math.max(max, n - (list.get(list.size() - 1) - list.get(0)));
        return max / 2;
    }

    // 用双指针的做法
    public int maxDistToClosest_implementation2(int[] nums, int x) {
        int n = nums.length;
        int left = 0;
        while (nums[left] != x) left++;
        int firstIndex = left;
        int right = left;
        int lastIndex = firstIndex;
        int max = 0;
        while (++right < n) {
            if (nums[right] == x) {
                lastIndex = right;
                max = Math.max(max, right - left);
                left = right;
            }
        }
        max = Math.max(max, n - (lastIndex - firstIndex)); // n - (lastIndex - firstIndex)为从firstIndex反向走到lastIndex的距离
        return max / 2;
    }

    public static void main(String[] args) {
        CircularMaxDistToClosest cmdtc = new CircularMaxDistToClosest();
        System.out.println(cmdtc.maxDistToClosest(new int[]{1,0,0,0,1,0,1}, 1));
        System.out.println(cmdtc.maxDistToClosest_implementation2(new int[]{1,0,0,0,1,0,1}, 1));
        System.out.println(cmdtc.maxDistToClosest(new int[]{1,2,1,2}, 2));
        System.out.println(cmdtc.maxDistToClosest_implementation2(new int[]{1,2,1,2}, 2));
        System.out.println(cmdtc.maxDistToClosest(new int[]{2,1,3,3,2}, 3));
        System.out.println(cmdtc.maxDistToClosest_implementation2(new int[]{2,1,3,3,2}, 3));
    }
}
