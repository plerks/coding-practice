/*
url: https://leetcode.cn/problems/non-overlapping-intervals/
LeetCode参考: https://leetcode.cn/problems/non-overlapping-intervals/solutions/541543/wu-zhong-die-qu-jian-by-leetcode-solutio-cpsb/
相关: LeetCode2251. 花期内花的数目, /典型问题/求一组点被几个区间覆盖/IntervalCover.java
标签: 贪心, 区间
*/

import java.util.Arrays;

public class Solution435 {
    public int eraseOverlapIntervals(int[][] intervals) {
        int chosenFirstIntervalRight = Integer.MIN_VALUE;
        Arrays.sort(intervals, (x, y) -> {
            return x[1] - y[1];
        });
        int chosenCount = 0;
        // 按区间右端点排序，每次选出头部的一个新区间加入后，下一个加入的为左端点在最新加入的区间右边的
        for (int i = 0; i < intervals.length; i++) {
            int[] interval = intervals[i];
            if (interval[0] >= chosenFirstIntervalRight) {
                chosenFirstIntervalRight = interval[1];
                chosenCount++; // 这个区间可以选出来
            }
        }
        return intervals.length - chosenCount;
    }

    public static void main(String[] args) {
        Solution435 solu = new Solution435();
        System.out.println(solu.eraseOverlapIntervals(new int[][]{{1,2},{2,3},{3,4},{1,3}}));
    }
}
