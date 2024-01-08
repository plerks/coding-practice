// https://leetcode.cn/problems/number-of-boomerangs/description/?envType=daily-question&envId=2024-01-08

import java.util.*;

public class Solution447 {
    public int numberOfBoomerangs(int[][] points) {
        int n = points.length;
        List<Map<Integer, Integer>> list = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            list.add(new HashMap<>());
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                int dis = getDistanceSquare(i, j, points);
                Map<Integer, Integer> map = list.get(i);
                map.put(dis, map.getOrDefault(dis, 0) + 1);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            Map<Integer, Integer> map = list.get(i);
            for (int val : map.values()) {
                ans += val * (val - 1);
            }
        }
        return ans;
    }

    // 返回距离的平方
    private int getDistanceSquare(int i, int j, int[][] points) {
        int a = points[i][0] - points[j][0];
        int b = points[i][1] - points[j][1];
        return a * a + b * b;
    }

    public static void main(String[] args) {
        Solution447 solu = new Solution447();
        System.out.println(solu.numberOfBoomerangs(new int[][]{{1,1},{2,2},{3,3}}));
    }
}
