/*
url: https://leetcode.cn/problems/course-schedule/
标签: 拓扑排序
*/

import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;

class Solution207 {
    public boolean canFinish(int numCourses, int[][] prerequisites) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < numCourses; i++) {
            graph.add(new ArrayList<>());
        }
        int[] indegrees = new int[numCourses];
        for (int[] arr : prerequisites) {
            indegrees[arr[0]]++;
            graph.get(arr[1]).add(arr[0]);
        }
        Deque<Integer> queue = new LinkedList<>();
        for (int i = 0; i < indegrees.length; i++) {
            if (indegrees[i] == 0) queue.add(i);
        }
        int count = 0;
        while (!queue.isEmpty()) {
            int node = queue.poll();
            count++;
            List<Integer> list = graph.get(node);
            for (int i = 0; i < list.size(); i++) {
                int to = list.get(i);
                indegrees[to]--;
                if (indegrees[to] == 0) queue.offer(to);
            }
        }
        return count == numCourses;
    }

	public static void main(String[] args) {
		
	}
    
}
