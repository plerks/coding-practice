/*
url: https://leetcode.cn/problems/car-pooling/
LeetCode参考: https://leetcode.cn/problems/car-pooling/solutions/2550264/suan-fa-xiao-ke-tang-chai-fen-shu-zu-fu-9d4ra/
标签: 差分数组, TreeMap
*/

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class Solution1094 {

    // 参考典型问题/求一组点被几个区间覆盖/IntervalCover.java中getCoverCount_implementation2()的技巧
    public boolean carPooling(int[][] trips, int capacity) {
        List<Point> list = new ArrayList<>();
        for (int i = 0; i < trips.length; i++) {
            list.add(new Point(trips[i][0], trips[i][1], 1));
            list.add(new Point(trips[i][0], trips[i][2], -1));
        }
        Collections.sort(list, (p1, p2) -> {
            if (p1.x != p2.x) return p1.x - p2.x;
            return p1.y - p2.y; // 先处理下车的点
        });
        for (Point p : list) {
            if (p.y == -1) {
                capacity += p.count;
            }
            else {
                capacity -= p.count;
                if (capacity < 0) return false;
            }
        }
        return true;
    }

    public boolean carPooling_implementation2(int[][] trips, int capacity) {
        // 0 <= fromi < toi <= 1000，用差分数组记录变化
        int[] arr = new int[1001];
        for (int i = 0; i < trips.length; i++) {
            int count = trips[i][0], from = trips[i][1], to = trips[i][2];
            arr[from] += count;
            arr[to] -= count;
        }
        int passengers = 0;
        for (int i = 0; i < arr.length; i++) {
            passengers += arr[i];
            if (passengers > capacity) return false;
        }
        return true;
    }

    // 还可以用treemap取代用长的数组
    public boolean carPooling_implementation3(int[][] trips, int capacity) {
        Map<Integer, Integer> map = new TreeMap<>();
        for (int i = 0; i < trips.length; i++) {
            int count = trips[i][0], from = trips[i][1], to = trips[i][2];
            map.merge(from, count, Integer::sum);
            map.merge(to, -count, Integer::sum);
        }
        int passengers = 0;
        for (int val : map.values()) {
            passengers += val;
            if (passengers > capacity) return false;
        }
        return true;
    }

    public static void main(String[] args) {
        Solution1094 solu = new Solution1094();
        System.out.println(solu.carPooling(new int[][]{{2,1,5},{3,3,7}}, 4));
        System.out.println(solu.carPooling_implementation2(new int[][]{{2,1,5},{3,3,7}}, 4));
        System.out.println(solu.carPooling_implementation3(new int[][]{{2,1,5},{3,3,7}}, 4));
    }
}

class Point {
    int count;
    int x;
    int y;

    Point(int count, int x, int y) {
        this.count = count;
        this.x = x;
        this.y = y;
    }
}