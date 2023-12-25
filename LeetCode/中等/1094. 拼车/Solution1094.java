// https://leetcode.cn/problems/car-pooling/

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

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

    public static void main(String[] args) {
        Solution1094 solu = new Solution1094();
        System.out.println(solu.carPooling(new int[][]{{2,1,5},{3,3,7}}, 4));
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