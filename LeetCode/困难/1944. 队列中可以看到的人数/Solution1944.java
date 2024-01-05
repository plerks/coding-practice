/*
url: https://leetcode.cn/problems/number-of-visible-people-in-a-queue/description/?envType=daily-question&envId=2024-01-05
LeetCode参考: https://leetcode.cn/problems/number-of-visible-people-in-a-queue/solutions/896102/dui-lie-zhong-ke-yi-kan-dao-de-ren-shu-b-k442/
标签: 单调栈
*/

import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;

public class Solution1944 {
    public int[] canSeePersonsCount(int[] heights) {
        int[] ans = new int[heights.length];
        Deque<Integer> stack = new LinkedList<>();
        int n = heights.length;
        // 看右边的人数，得从右往左遍历
        for (int i = n - 1; i >= 0; i--) {
            int count = 0;
            // i号人能看到的是比自己矮的和第一个比自己高的(或者等高)
            while (!stack.isEmpty() && stack.peek() < heights[i]) {
                stack.pop();
                count++;
            }
            if (!stack.isEmpty()) count++;
            ans[i] = count;
            stack.push(heights[i]);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1944 solu = new Solution1944();
        System.out.println(Arrays.toString(solu.canSeePersonsCount(new int[]{10,6,8,5,11,9})));
    }
}
