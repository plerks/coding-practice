/*
url: https://leetcode.cn/problems/course-schedule-iii/?envType=daily-question&envId=2023-09-11
LeetCode参考: https://leetcode.cn/problems/course-schedule-iii/solutions/1155605/ke-cheng-biao-iii-by-leetcode-solution-yoyz/
*/

import java.util.Arrays;
import java.util.PriorityQueue;

public class Solution630 {
    public int scheduleCourse(int[][] courses) {
        Arrays.sort(courses, (x, y) -> {
            return x[1] - y[1];
        });
        PriorityQueue<Integer> pq = new PriorityQueue<>((x, y) -> y - x);
        int tsum = 0;
        for (int[] course : courses) {
            int ti = course[0], di = course[1];
            if (tsum + ti <= di) {
                pq.offer(ti);
                tsum += ti;
            }
            else {
                // 按结束时间遍历的课程，di一定比抽出来的那门课程的结束时间大
                if (!pq.isEmpty() && pq.peek() > ti) {
                    tsum -= pq.poll();
                    pq.offer(ti);
                    tsum += ti;
                }
            }
        }
        return pq.size();
    }

    public static void main(String[] args) {
        Solution630 solu = new Solution630();
        System.out.println(solu.scheduleCourse(new int[][]{{1,2}}));
    }
}