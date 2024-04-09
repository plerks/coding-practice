/*
url: https://leetcode.cn/problems/pyramid-transition-matrix/description/
相关: LeetCode51. N 皇后
标签: 八皇后, 递归回溯
*/

import java.util.*;

public class Solution756 {
    int N = 26;

    public boolean pyramidTransition(String bottom, List<String> allowed) {
        // 类似八皇后问题的递归回溯过程，把金字塔看成类似数组，从下往上，从右往左dfs并回溯
        int n = bottom.length();
        // 预处理，记录上面那块的可选项
        Map<Integer, List<Character>> map = new HashMap<>();
        for (String s : allowed) {
            int u = s.charAt(0) - 'A';
            int v = s.charAt(1) - 'A';
            int key = u * N + v;
            if (!map.containsKey(key)) {
                List<Character> list = new ArrayList<>();
                list.add(s.charAt(2));
                map.put(key, list);
            }
            else map.get(key).add(s.charAt(2));
        }
        char[][] pyramid = new char[n + 1][n + 1];
        for (int i = 1; i <= n; i++) {
            pyramid[n][i] = bottom.charAt(i - 1);
        }
        return dfs(n - 1, n - 1, map, pyramid);
    }

    // i, j记录dfs到了第i层的第j列
    private boolean dfs(int i, int j, Map<Integer, List<Character>> map, char[][] pyramid) {
        if (i == 0) return true;
        int u = pyramid[i + 1][j] - 'A'; // 左孩子
        int v = pyramid[i + 1][j + 1] - 'A'; // 右孩子
        int key = u * N + v;
        if (map.get(key) == null) return false;
        for (char val : map.get(key)) {
            pyramid[i][j] = val;
            // 若dfs能成功摆满金字塔，则可以直接返回true，否则必须列举for循环的所有情况
            if (j == 1) {
                if (dfs(i - 1, i - 1, map, pyramid)) {
                    return true;
                }
            }
            else if (dfs(i, j - 1, map, pyramid)) {
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        Solution756 solu = new Solution756();
        // System.out.println(solu.pyramidTransition("BCD", Arrays.asList("BCC","CDE","CEA","FFF")));
        // System.out.println(solu.pyramidTransition("AABA", Arrays.asList("AAA","AAB","ABA","ABB","BAC")));
        System.out.println(solu.pyramidTransition("CBDDA", Arrays.asList("ACC","ACA","AAB","BCA","BCB","BAC","BAA","CAC","BDA","CAA","CCA","CCC","CCB","DAD","CCD","DAB","ACD","DCA","CAD","CBB","ABB","ABC","ABD","BDB","BBC","BBA","DDA","CDD","CBC","CBA","CDA","DBA","ABA")));
    }
}
