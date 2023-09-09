/*
url: https://leetcode.cn/problems/course-schedule-ii/?envType=daily-question&envId=2023-09-10
相关: https://leetcode.cn/problems/course-schedule/
标签: 拓扑排序
*/

public class Solution210 {
    public int[] findOrder(int numCourses, int[][] prerequisites) {
        int[] ans = new int[numCourses];
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
            ans[count] = node;
            count++;
            List<Integer> list = graph.get(node);
            for (int i = 0; i < list.size(); i++) {
                int to = list.get(i);
                indegrees[to]--;
                if (indegrees[to] == 0) queue.offer(to);
            }
        }
        return count == numCourses ? ans : new int[0];
    }

    public static void main(String[] args) {
    }
}