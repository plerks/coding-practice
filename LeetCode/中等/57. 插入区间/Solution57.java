/*
url: https://leetcode.cn/problems/insert-interval/
相关: https://leetcode.cn/problems/merge-intervals/
*/

import java.util.*;

public class Solution57 {
    // 直接拿了<https://leetcode.cn/problems/merge-intervals/>的代码过来用
    public int[][] insert(int[][] intervals, int[] newInterval) {
        int[][] newIntervals = new int[intervals.length + 1][2];
        for (int i = 0; i < intervals.length; i++) {
            newIntervals[i] = intervals[i];
        }
        newIntervals[newIntervals.length - 1] = newInterval;
        Arrays.sort(newIntervals, (x, y) -> {
            return x[0] - y[0];
        });
        List<int[]> merged = new ArrayList<>();
        for (int i = 0; i < newIntervals.length; i++) {
            int[] interval = newIntervals[i];
            if (merged.size() == 0) {
                merged.add(interval);
            }
            else {
                if (interval[0] > merged.get(merged.size() - 1)[1]) {
                    merged.add(interval);
                }
                else {
                    merged.get(merged.size() - 1)[1] = Math.max(interval[1], merged.get(merged.size() - 1)[1]);
                }
            }
        }
        int[][] ans = new int[merged.size()][2];
        for (int i = 0; i < merged.size(); i++) {
            ans[i] = merged.get(i);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution57 solu = new Solution57();
        System.out.println(Arrays.deepToString(solu.insert(new int[][]{{1,3},{6,9}}, new int[]{2,5})));
    }
}