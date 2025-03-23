/*
url: https://leetcode.cn/problems/merge-intervals/
LeetCode参考: https://leetcode.cn/problems/merge-intervals/solutions/203562/he-bing-qu-jian-by-leetcode-solution/
相关: LeetCode57. 插入区间, LeetCode715. Range 模块, LeetCode2580. 统计将重叠区间合并成组的方案数, LeetCode2276. 统计区间中的整数数目, LeetCode986. 区间列表的交集
标签: 区间合并
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