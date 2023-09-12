/*
url: https://leetcode.cn/problems/course-schedule-iv/?envType=daily-question&envId=2023-09-12
LeetCode参考: https://leetcode.cn/problems/course-schedule-iv/solutions/268367/pythonbu-fu-za-de-da-biao-fa-by-bestfitting/
标签: 建表, Floyd算法
 */

import java.util.ArrayList;

public class Solution1462 {
    public List<Boolean> checkIfPrerequisite(int numCourses, int[][] prerequisites, int[][] queries) {
        boolean[][] table = new boolean[numCourses][numCourses];
        for (int[] arr : prerequisites) {
            table[arr[0]][arr[1]] = true;
        }
        // 最外层的k为尝试的转接节点，用来尝试连通i,j
        for (int k = 0; k < numCourses; k++) {
            for (int i = 0; i < numCourses; i++) {
                for (int j = 0; j < numCourses; j++) {
                    if (table[i][k] && table[k][j]) {
                        table[i][j] = true;
                    }
                }
            }
        }
        List<Boolean> ans = new ArrayList<>();
        for (int[] arr : queries) {
            ans.add(table[arr[0]][arr[1]]);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1462 solu = new Solution1462();
        System.out.println(solu.solve());
    }
}