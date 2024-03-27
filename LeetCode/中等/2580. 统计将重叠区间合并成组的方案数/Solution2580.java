/*
url: https://leetcode.cn/problems/count-ways-to-group-overlapping-ranges/description/?envType=daily-question&envId=2024-03-27
相关: LeetCode56. 合并区间, LeetCode57. 插入区间, LeetCode715. Range 模块
标签: 区间合并
*/

import java.util.*;

public class Solution2580 {
    public int countWays(int[][] ranges) {
        // 区间合并问题，考虑用LeetCode56. 合并区间的技巧
        // 只能分为两个组，且有重叠的必须在同一个组，那么A放入1组，B与A有重叠，区间合并之后成A+B，则C若与A或B有重叠等价于与A+B有重叠
        // 区间的重叠合并会传染，最终形成连通分量，那么答案就是将连通分量分配到两个组，每个连通分量两种选择，答案为2^连通分量
        List<int[]> intervals = new ArrayList<>();
        Arrays.sort(ranges, (x, y) -> x[0] - y[0]);
        for (int[] arr : ranges) {
            if (intervals.isEmpty()) intervals.add(arr);
            else {
                int[] last = intervals.get(intervals.size() - 1);
                if (arr[0] > last[1]) {
                    intervals.add(arr);
                }
                else {
                    last[1] = Math.max(last[1], arr[1]);
                }
            }
        }
        // 数据不溢出的话这里该是return 1 << intervals.size();
        final int MOD = 1_000_000_007;
        int ans = 1;
        for (int i = 0; i < intervals.size(); i++) {
            ans = ans * 2 % MOD;
        }
        return ans;
    }

    // 优化下，只需要知道连通分量个数，不需要求具体的合并结果
    public int countWays_implementation2(int[][] ranges) {
        Arrays.sort(ranges, (x, y) -> x[0] - y[0]);
        int lastRight = ranges[0][1]; // 最后一个区间的右端点
        int count = 1; // 连通分量个数
        for (int[] arr : ranges) { // 这里也可以从下标1开始，不过从0开始相当于把第一个区间重复了下，不影响结果
            if (arr[0] <= lastRight) { // 合并
                lastRight = Math.max(lastRight, arr[1]);
            }
            else { // 新连通分量
                count++;
                lastRight = arr[1];
            }
        }
        final int MOD = 1_000_000_007;
        int ans = 1;
        for (int i = 0; i < count; i++) {
            ans = ans * 2 % MOD;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2580 solu = new Solution2580();
        System.out.println(solu.countWays(new int[][]{{1,3},{10,20},{2,5},{4,8}}));
        System.out.println(solu.countWays_implementation2(new int[][]{{1,3},{10,20},{2,5},{4,8}}));
    }
}
