/*
url: https://leetcode.cn/problems/minimize-manhattan-distances/description/
LeetCode参考: https://leetcode.cn/problems/minimize-manhattan-distances/solutions/2716755/tu-jie-man-ha-dun-ju-chi-heng-deng-shi-b-op84/
其它参考: https://oi-wiki.org/geometry/distance/#%E8%AF%81%E6%98%8E
相关: LeetCode1954. 收集足够苹果的最小花园周长
标签: LeetCode第391场周赛, 数学, 平面几何, 曼哈顿距离, 切比雪夫距离, 有序集合, TreeMap
*/

import java.util.*;

/* 这题的基础问题应该是：给定n个平面上的点，求点之间的最大曼哈顿距离。暴力法需要O(n^2)时间，用这题转为切比雪夫距离的办法，
只需要在转换坐标时记录x'和y'的最大最小，TreeMap都不需要，神奇地只要O(n)时间！

如果是求点之间的最小曼哈顿距离好像就不能这么做了，求最大的特殊性在于max(max(|x1' - x2'|, |y1' - y2'|), max(|x1' - x3'|, |y1' - y3'|), ...)（O(n^2)组点对）
可以拆成max(|x1' - x2'|,|x1' - x3'|, ..., |y1' - y2'|, |y1' - y3'|, ...)（也是O(n^2)组，甚至常系数变大成2了），但是可以将x和y分开考虑，且**求xi-xj和yi-yj的最
大值只需求xy最大最小**，于是只需O(n)时间。

若是最小曼哈顿距离，则min(max(), max(),...)则不能把坐标拆开独立看。比如|x1'-x2'|可能很小，但是|y1'-y2'|大于|x1'-x2'|，曼哈顿距离根本取不到|x1'-x2'|。不知道
有没有非暴力的做法。
*/
public class Solution3102 {
    // 周赛时写的暴力解法，519 / 536 个通过的测试用例，超时
    public int minimumDistance_exceed_time_limit(int[][] points) {
        int n = points.length;
        int[][][] dis = new int[n][n][3];
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int d = Math.abs(points[i][0] - points[j][0]) + Math.abs(points[i][1] - points[j][1]);
                dis[i][j] = new int[]{d, i, j};
                dis[j][i] = new int[]{d, j, i};
            }
        }
        int ans = Integer.MAX_VALUE;
        for (int x = 0; x < n; x++) { // 暴力枚举删除的点x
            int max = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (j == i) continue;
                    int[] arr = dis[i][j];
                    if (arr[1] != x && arr[2] != x) {
                        max = Math.max(max, arr[0]);
                    }
                }
            }
            ans = Math.min(ans, max);
        }
        return ans;
    }

    /* 灵茶山艾府题解解法一，
    关键式子: |x1 - x2| + |y1 - y2| = max(|x1' - x2'|, |y1' - y2'|)，其中(x', y') = (x + y, x - y)。
    这样就去掉了绝对值并可以将x', y'分开考虑，用TreeMap记录x', y'，|x1' - x2'|最大为用最大的x'减最小的x'。
    */
    public int minimumDistance(int[][] points) {
        TreeMap<Integer, Integer> xs = new TreeMap<>();
        TreeMap<Integer, Integer> ys = new TreeMap<>();
        for (int[] p : points) {
            int x = p[0] + p[1];
            int y = p[0] - p[1];
            xs.merge(x, 1, Integer::sum);
            ys.merge(y, 1, Integer::sum);
        }
        int ans = Integer.MAX_VALUE;
        // 枚举删除的点
        for (int[] p : points) {
            int x = p[0] + p[1];
            int y = p[0] - p[1];
            xs.merge(x, -1, Integer::sum);
            ys.merge(y, -1, Integer::sum);
            if (xs.get(x) == 0) xs.remove(x);
            if (ys.get(y) == 0) ys.remove(y);
            ans = Math.min(ans, Math.max(xs.lastKey() - xs.firstKey(), ys.lastKey() - ys.firstKey()));
            xs.merge(x, 1, Integer::sum);
            ys.merge(y, 1, Integer::sum);
        }
        return ans;
    }

    /* 灵茶山艾府题解解法二，这里会考虑每种去掉一个点的情况，只需要维护最大次大，最小次小的x和y即可知道每种情况下的最大最小x和y。
    注意，如果是单纯动态地添加数，只需维护最大值即可在加值过程中知道最大值，如果是单纯动态地减少数，维护最小次小没法在过程中知道
    最小值，例如前两次直接把最小次小都删了。这里是每次只忽略一个数，所以维护最大次大最小次小能获取最大最小。
    */
    public int minimumDistance_implementation2(int[][] points) {
        int maxX = Integer.MIN_VALUE, subMaxX = Integer.MIN_VALUE;
        int minX = Integer.MAX_VALUE, subMinX = Integer.MAX_VALUE;
        int maxY = Integer.MIN_VALUE, subMaxY = Integer.MIN_VALUE;
        int minY = Integer.MAX_VALUE, subMinY = Integer.MAX_VALUE;
        for (int[] p : points) {
            int x = p[0] + p[1];
            int y = p[0] - p[1];
            if (x > maxX) {
                subMaxX = maxX;
                maxX = x;
            }
            else if (x > subMaxX) subMaxX = x;
            if (x < minX) {
                subMinX = minX;
                minX = x;
            }
            else if (x < subMinX) subMinX = x;

            if (y > maxY) {
                subMaxY = maxY;
                maxY = y;
            }
            else if (y > subMaxY) subMaxY = y;
            if (y < minY) {
                subMinY = minY;
                minY = y;
            }
            else if (y < subMinY) subMinY = y;
        }
        int ans = Integer.MAX_VALUE;
        // 枚举删除的点
        for (int[] p : points) {
            int x = p[0] + p[1];
            int y = p[0] - p[1];
            int tminX, tmaxX;
            int tminY, tmaxY;
            tminX = x == minX ? subMinX : minX;
            tmaxX = x == maxX ? subMaxX : maxX;
            tminY = y == minY ? subMinY : minY;
            tmaxY = y == maxY ? subMaxY : maxY;
            ans = Math.min(ans, Math.max(tmaxX - tminX, tmaxY - tminY));
        }
        return ans;
    }

    /* 灵茶山艾府题解解法三，在解法二的基础上更进一步。最大值最小一定出现在删最大最小xy的情况，其它情况下|x1' - x2'|, |y1' - y2'|
    都会同时取最大值，最大距离一定会更大。因此维护最大最小xy的下标，只需遍历那几个位置。
    */
    public int minimumDistance_implementation3(int[][] points) {
        int maxX = Integer.MIN_VALUE, subMaxX = Integer.MIN_VALUE;
        int minX = Integer.MAX_VALUE, subMinX = Integer.MAX_VALUE;
        int maxY = Integer.MIN_VALUE, subMaxY = Integer.MIN_VALUE;
        int minY = Integer.MAX_VALUE, subMinY = Integer.MAX_VALUE;
        int maxXIndex = 0, minXIndex = 0, maxYIndex = 0, minYIndex = 0;
        for (int i = 0; i < points.length; i++) {
            int[] p = points[i];
            int x = p[0] + p[1];
            int y = p[0] - p[1];
            if (x > maxX) {
                subMaxX = maxX;
                maxX = x;
                maxXIndex = i;
            }
            else if (x > subMaxX) subMaxX = x;
            if (x < minX) {
                subMinX = minX;
                minX = x;
                minXIndex = i;
            }
            else if (x < subMinX) subMinX = x;

            if (y > maxY) {
                subMaxY = maxY;
                maxY = y;
                maxYIndex = i;
            }
            else if (y > subMaxY) subMaxY = y;
            if (y < minY) {
                subMinY = minY;
                minY = y;
                minYIndex = i;
            }
            else if (y < subMinY) subMinY = y;
        }
        int ans = Integer.MAX_VALUE;
        /* 只需枚举删除最大最小xy的情况，这里有个奇妙的点，只枚举了4个删除位置，例如若最大x有多个点可以取得，不枚举所有最大最小点会不会导致
        求出的最大距离的最小值ans不对？
        
        以下以maxX,subMaxX,minX,subMinX记最大次大最小次小x，maxY,subMaxY,minY,subMinY记最大次大最小次小y, tMaxX,tMinX,tMaxY,tMinY
        记删除某一个点后，其对应剩下的点中的最大最小xy。

        否，假设(x1, y1)和(x2, y2)都取x的最大值(x1==x2==maxX)，只考虑了删除(x1, y1)的情况，下证漏掉枚举删除(x2, y2)的情况，最终的ans仍然正确。
        
        这里如果删除(x2, y2)比删除(x1, y1)更优（最大距离更小），说明(x2, y2)的y2是y的最大或最小(否则在tMaxX相等的情况下(x1,y1)还有机会取y的
        最大最小, (x2,y2)绝不会更优)，以下以y2取maxY为例。

        删除(x1, y1)时，最大距离<=max(maxX-minX, maxY-minY)（注意由于还有x2==maxX，则tMaxX1==maxX-minX，可能取小于是因为y1可能取y的最大最小）；
        
        删除(x2, y2)时，
        若取maxY的点不止(x2, y2)，则最大距离为max(maxX-minX, maxY-minY)，不会更优；
        若取maxY的点只有(x2, y2)，则最大距离为max(maxX-minX, subMaxY-minY)，确实可能比(x1, y1)的情况小，但由于取maxY的点只有(x2, y2)，
        (x2, y2)一定会被考虑删除，因此最终ans不会错。
        */
        for (int i : new int[]{maxXIndex, minXIndex, maxYIndex, minYIndex}) {
            int[] p = points[i];
            int x = p[0] + p[1];
            int y = p[0] - p[1];
            int tminX, tmaxX;
            int tminY, tmaxY;
            tminX = x == minX ? subMinX : minX;
            tmaxX = x == maxX ? subMaxX : maxX;
            tminY = y == minY ? subMinY : minY;
            tmaxY = y == maxY ? subMaxY : maxY;
            ans = Math.min(ans, Math.max(tmaxX - tminX, tmaxY - tminY));
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution3102 solu = new Solution3102();
        System.out.println(solu.minimumDistance(new int[][]{{3,10},{5,15},{10,2},{4,4}}));
        System.out.println(solu.minimumDistance_implementation2(new int[][]{{3,10},{5,15},{10,2},{4,4}}));
        System.out.println(solu.minimumDistance_implementation3(new int[][]{{3,10},{5,15},{10,2},{4,4}}));
    }
}
