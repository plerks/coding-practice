/*
给出横轴上的一些闭区间和一系列数，求每个数被几个区间覆盖。
相关: LeetCode35. 搜索插入位置 https://leetcode.cn/problems/search-insert-position/
      LeetCode2251. 花期内花的数目 https://leetcode.cn/problems/number-of-flowers-in-full-bloom/
标签: 求一组点被几个区间覆盖
*/

import java.util.*;

// 如果只是求一个点被几个区间覆盖，即xArr.length == 1，只需遍历一遍intervals判断即可
public class IntervalCover {
    // 将x包含的区间数量为{起点<=x的区间数量} - {终点<x的区间数量}
    public int[] getCoverCount(int[][] intervals, int[] xArr) {
        int n = intervals.length;
        int[] start = new int[n];
        int[] end = new int[n];
        for (int i = 0; i < n; i++) {
            start[i] = intervals[i][0];
            end[i] = intervals[i][1];
        }
        Arrays.sort(start);
        Arrays.sort(end);
        int[] ans = new int[xArr.length];
        for (int i = 0; i < xArr.length; i++) {
            ans[i] = getFirstLargerIndex(start, xArr[i]) - getFirstLargerOrEqualIndex(end, xArr[i]);
        }
        return ans;
    }

    // 找到arr中第一个>x的位置
    public int getFirstLargerIndex(int[] arr, int x) {
        int left = 0, right = arr.length;
        while (left < right) {
            int mid = (left + right) / 2;
            if (arr[mid] > x) {
                right = mid; // 转入[left, mid]
            }
            else {
                left = mid + 1; // 转入[mid + 1, right]
            }
        }
        return left;
    }


    // 找到arr中第一个>=x的位置
    public int getFirstLargerOrEqualIndex(int[] arr, int x) {
        int left = 0, right = arr.length;
        while (left < right) {
            int mid = (left + right) / 2;
            if (arr[mid] >= x) {
                right = mid; // 转入[left, mid]
            }
            else {
                left = mid + 1; // 转入[mid + 1, right]
            }
        }
        return left;
    }

    // 参考https://leetcode.cn/problems/number-of-flowers-in-full-bloom/solutions/1444982/by-tsreaper-s39k/中的解法
    public int[] getCoverCount_implementation2(int[][] intervals, int[] xArr) {
        List<Point> list = new ArrayList<>();
        for (int[] arr : intervals) {
            list.add(new Point(arr[0], Integer.MIN_VALUE));
            list.add(new Point(arr[1], Integer.MAX_VALUE));
        }
        for (int i = 0; i < xArr.length; i++) {
            list.add(new Point(xArr[i], i));
        }
        Collections.sort(list, (p1, p2) -> {
            if (p1.x != p2.x) {
                return p1.x < p2.x ? -1 : 1;
            }
            if (p1.y != p2.y) {
                return p1.y < p2.y ? -1 : 1; // 直接写p1.y - p2.y可能p1.y == Integer.MAX_VALUE导致溢出变成正的了
            }
            return 0;
        });
        /* 若x相同，则要按起点(Integer.MIN_VALUE)，x(i)，终点(Integer.MAX_VALUE)来处理，同一时刻区间开始会覆盖x，结束也是这个区间覆盖了x，这样计数才是对的。
        所以y要那样取值，排序后遍历list刚好会是这个处理顺序 */
        int now = 0;
        for (Point point : list) {
            if (point.y == Integer.MIN_VALUE) now++;
            else if (point.y == Integer.MAX_VALUE) now--;
            else xArr[point.y] = now; // 直接复用xArr
        }
        return xArr;
    }

    public static void main(String[] args) {
        IntervalCover intervalCover = new IntervalCover();
        System.out.println(Arrays.toString(intervalCover.getCoverCount(new int[][]{{1, 2}, {2, 3}, {5, 6}}, new int[]{2, 3, 7})));
        System.out.println(Arrays.toString(intervalCover.getCoverCount_implementation2(new int[][]{{1, 2}, {2, 3}, {5, 6}}, new int[]{2, 3, 7})));
    }
}


class Point {
    int x;
    int y;

    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }
}