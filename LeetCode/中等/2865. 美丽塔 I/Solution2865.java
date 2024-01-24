/*
url: https://leetcode.cn/problems/beautiful-towers-i/description/?envType=daily-question&envId=2024-01-24
LeetCode参考: https://leetcode.cn/problems/beautiful-towers-i/solutions/2614597/mei-li-ta-i-by-leetcode-solution-uqnf/
标签: 动态规划, 单调栈
*/

import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;

public class Solution2865 {
    // 容易想到的暴力解法，时间复杂度O(n^2)
    public long maximumSumOfHeights(List<Integer> maxHeights) {
        // 山峰位置一定会取maxHeight
        int n = maxHeights.size();
        long ans = 0;
        for (int i = 0; i < n; i++) {
            long sum = 0;
            sum += maxHeights.get(i);
            int lastTowerHeight = maxHeights.get(i);
            for (int j = i - 1; j >= 0; j--) {
                int towerHeight = Math.min(lastTowerHeight, maxHeights.get(j));
                sum += towerHeight;
                lastTowerHeight = towerHeight;
            }
            lastTowerHeight = maxHeights.get(i);
            for (int j = i + 1; j < n; j++) {
                int towerHeight = Math.min(lastTowerHeight, maxHeights.get(j));
                sum += towerHeight;
                lastTowerHeight = towerHeight;
            }
            ans = Math.max(ans, sum);
        }
        return ans;
    }

    /* 参考题解的解法，我只想到了可能需要动态规划，用dpLeft[]和dpRight[]分别计算左侧单增和右侧单减的和的最大值，
    但是没想出来状态如何转移，因为对i位置取maxHeight[i]之后，左侧的塔高能取的值会变化，没想出来这个变化关系
    */
    public long maximumSumOfHeights_implementation2(List<Integer> maxHeights) {
        int n = maxHeights.size();
        long[] prefix = new long[n]; // prefix[i]表示i左侧单增数组的最大和
        long[] suffix = new long[n]; // suffix[i]表示i右侧单减数组的最大和
        Deque<Integer> stack1 = new LinkedList<>();
        Deque<Integer> stack2 = new LinkedList<>();
        for (int i = 0; i < n; i++) {
            while (!stack1.isEmpty() && maxHeights.get(stack1.peek()) > maxHeights.get(i)) {
                stack1.pop();
            }
            // (j,i]只能取maxHeight[i]，而(0,j]由于maxHeight[x]小于maxHeight[i]，不会违反单增性，无需调整
            if (stack1.isEmpty()) {
                prefix[i] = (i - (-1)) * (long)maxHeights.get(i);
            }
            else {
                int j = stack1.peek();
                prefix[i] = prefix[j] + (i - j) * (long)maxHeights.get(i);
            }
            stack1.push(i);
        }
        for (int i = n - 1; i >= 0; i--) {
            while (!stack2.isEmpty() && maxHeights.get(stack2.peek()) > maxHeights.get(i)) {
                stack2.pop();
            }
            if (stack2.isEmpty()) {
                suffix[i] = ((n - 1) - i + 1) * (long)maxHeights.get(i);
            }
            else {
                int j = stack2.peek();
                suffix[i] = suffix[j] + (j - i) * (long)maxHeights.get(i);
            }
            stack2.push(i);
        }
        long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = Math.max(ans, prefix[i] + suffix[i] - maxHeights.get(i));
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2865 solu = new Solution2865();
        System.out.println(solu.maximumSumOfHeights(Arrays.asList(5,3,4,1,1)));
        System.out.println(solu.maximumSumOfHeights_implementation2(Arrays.asList(5,3,4,1,1)));
    }
}
