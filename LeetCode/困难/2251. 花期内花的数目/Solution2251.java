/*
url: https://leetcode.cn/problems/number-of-flowers-in-full-bloom/?envType=daily-question&envId=2023-09-28
LeetCode参考: https://leetcode.cn/problems/number-of-flowers-in-full-bloom/solutions/1444982/by-tsreaper-s39k/
              https://leetcode.cn/problems/number-of-flowers-in-full-bloom/solutions/1445000/chai-fen-pythonjavacgo-by-endlesscheng-wz35/
相关: /典型问题/求一组点被几个区间覆盖
标签: 求一组点被几个区间覆盖
*/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Solution2251 {
    public int[] fullBloomFlowers(int[][] flowers, int[] people) {
        /* 基础想法是t时刻能看到的花的数目为{<=t之前开的花} - {<t时刻凋谢的花}，所以可以分别排序开花和凋谢时间后二分搜索数量。
        但是参考题解有更好的解题方式，将开花点，凋谢点和人的时间点排序，遍历，用一个变量now表示当前活跃的花，若花开则now++，若是人则当前能看到now朵花，
        花谢则now-- */
        List<Point> list = new ArrayList<>();
        for (int[] arr : flowers) {
            // 拆成2个点
            list.add(new Point(arr[0], Integer.MIN_VALUE));
            list.add(new Point(arr[1], Integer.MAX_VALUE));
        }
        for (int i = 0; i < people.length; i++) {
            list.add(new Point(people[i], i)); // 直接可以通过Point.y找到原来的位置
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
        /* 若x相同，则要按花开(Integer.MIN_VALUE)，人(i)，花谢(Integer.MAX_VALUE)来处理，同一时刻花开人能看到花，花谢人也能看到，这样计数才是对的。
        所以y要那样取值，排序后遍历list刚好会是这个处理顺序 */
        int now = 0;
        for (Point point : list) {
            if (point.y == Integer.MIN_VALUE) now++;
            else if (point.y == Integer.MAX_VALUE) now--;
            else people[point.y] = now; // 直接复用people
        }
        return people;
    }

    public static void main(String[] args) {
        Solution2251 solu = new Solution2251();
        System.out.println(Arrays.toString(solu.fullBloomFlowers(new int[][]{{1,6},{3,7},{9,12},{4,13}}, new int[]{2,3,7,11})));
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