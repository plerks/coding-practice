/*
url: https://leetcode.cn/problems/merge-intervals/
LeetCode参考: https://leetcode.cn/problems/merge-intervals/solutions/203562/he-bing-qu-jian-by-leetcode-solution/
相关: https://leetcode.cn/problems/insert-interval/
*/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution56 {
    public int[][] merge(int[][] intervals) {
        Arrays.sort(intervals, (x, y) -> {
            return x[0] - y[0];
        });
        List<int[]> merged = new ArrayList<>();
        for (int i = 0; i < intervals.length; i++) {
            int[] interval = intervals[i];
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
        Solution56 solu = new Solution56();
        System.out.println(Arrays.deepToString(solu.merge(new int[][]{{1,3},{2,6},{8,10},{15,18}})));
    }
}