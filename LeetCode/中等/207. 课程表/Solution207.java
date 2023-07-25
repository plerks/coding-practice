// https://leetcode.cn/problems/course-schedule/

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

class Solution207 {
    public boolean canFinish(int numCourses, int[][] prerequisites) {
        List<List<Integer>> edges = new ArrayList<List<Integer>>();
        for (int i = 0; i < numCourses; ++i) {
            edges.add(new ArrayList<Integer>());
        }
        int[] indegree = new int[numCourses];
        for(int[] arr:prerequisites){
            indegree[arr[0]]++;
            edges.get(arr[1]).add(arr[0]);
        }
        Queue<Integer> q = new LinkedList<Integer>();
        for(int i = 0;i<indegree.length;i++){
            if(indegree[i]==0){
                q.add(i);
            }
        }
        int count = 0;
        while(!q.isEmpty()){
            int node = q.poll();
            count++;
            for(int i = 0;i <edges.get(node).size();i++){
                indegree[edges.get(node).get(i)]--;
                if(indegree[edges.get(node).get(i)]==0){
                    q.add(edges.get(node).get(i));
                }
            }
        }
        return count==numCourses;
    }

	public static void main(String[] args) {
		
	}
    
}
