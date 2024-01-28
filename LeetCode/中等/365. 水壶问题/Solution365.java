/*
url: https://leetcode.cn/problems/water-and-jug-problem/description/?envType=daily-question&envId=2024-01-28
LeetCode参考: https://leetcode.cn/problems/water-and-jug-problem/solutions/161010/shui-hu-wen-ti-by-leetcode-solution/
其它参考: https://oi-wiki.org/math/number-theory/bezouts/
标签: 水壶问题, 数论, 裴蜀定理, 进制表示法
*/

import java.util.HashSet;

public class Solution365 {
    // 题目是要用以上水壶中的一或两个来盛放取得的 targetCapacity 升水，我这样写的是用额外一个容器来存倒出的水
    /* HashSet<Long> set;
    static final long N = 1000001;

    public boolean canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity) {
        set = new HashSet<>();
        return myCanMeasureWater(jug1Capacity, 0, jug2Capacity, 0, 0, targetCapacity);
    }

    private boolean myCanMeasureWater(int jug1Capacity, int fill1, int jug2Capacity, int fill2, int capacity, int targetCapacity) {
        if (capacity == targetCapacity) return true;
        if (capacity > targetCapacity) return false;
        if (set.contains(fill1 * N * N + fill2 * N + capacity)) return false;
        set.add(fill1 * N * N + fill2 * N + capacity);
        boolean ans = false;

        // 给1装满水
        ans |= myCanMeasureWater(jug1Capacity, jug1Capacity, jug2Capacity, fill2, capacity, targetCapacity);

        // 给2装满水
        ans |= myCanMeasureWater(jug1Capacity, fill1, jug2Capacity, jug2Capacity, capacity, targetCapacity);

        int amount;

        // 1的水倒到2
        amount = Math.min(fill1, jug2Capacity - fill2);
        ans |= myCanMeasureWater(jug1Capacity, fill1 - amount, jug2Capacity, fill2 + amount, capacity, targetCapacity);

        // 2的水倒到1
        amount = Math.min(fill2, jug1Capacity - fill1);
        ans |= myCanMeasureWater(jug1Capacity, fill1 + amount, jug2Capacity, fill2 - amount, capacity, targetCapacity);

        // 倒出1的水
        ans |= myCanMeasureWater(jug1Capacity, 0, jug2Capacity, fill2, capacity + fill1, targetCapacity);

        // 倒出2的水
        ans |= myCanMeasureWater(jug1Capacity, fill1, jug2Capacity, 0, capacity + fill2, targetCapacity);

        return ans;
    } */

    /* 暴力解法，递归枚举每步能做的操作，用set存之前尝试过的操作，防止重复递归。暴力法对一些用例会stackoverflow，要把栈设置得很大才能跑，
    `java -Xss128m Solution365.java`(jdk11往上可以直接这样运行一个single-file source-code program，不用先javac编译)。

    官方题解的做法一也是暴力解法，不过用了栈来模拟递归防止爆栈。
    */

    HashSet<Long> set;
    static final long N = 1000001;

    public boolean canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity) {
        set = new HashSet<>();
        return myCanMeasureWater(jug1Capacity, 0, jug2Capacity, 0, targetCapacity);
    }

    private boolean myCanMeasureWater(int jug1Capacity, int fill1, int jug2Capacity, int fill2, int targetCapacity) {
        if (fill1 == targetCapacity || fill2 == targetCapacity || fill1 + fill2 == targetCapacity) {
            set.add(fill1 * N * N + fill2 * N);
            return true;
        }
        if (set.contains(fill1 * N * N + fill2 * N)) return false;
        boolean ans = false;
        set.add(fill1 * N * N + fill2 * N); // 防止其它递归实例尝试以此为开头的情况

        // 给1装满水
        // 防止尝试的情况和现状相同
        if (!(fill1 == jug1Capacity))
        ans |= myCanMeasureWater(jug1Capacity, jug1Capacity, jug2Capacity, fill2, targetCapacity);

        // 给2装满水
        if (!(fill2 == jug2Capacity))
        ans |= myCanMeasureWater(jug1Capacity, fill1, jug2Capacity, jug2Capacity, targetCapacity);

        int amount;

        // 1的水倒到2
        amount = Math.min(fill1, jug2Capacity - fill2);
        if (!(amount == 0))
        ans |= myCanMeasureWater(jug1Capacity, fill1 - amount, jug2Capacity, fill2 + amount, targetCapacity);

        // 2的水倒到1
        amount = Math.min(fill2, jug1Capacity - fill1);
        if (!(amount == 0))
        ans |= myCanMeasureWater(jug1Capacity, fill1 + amount, jug2Capacity, fill2 - amount, targetCapacity);

        // 倒出1的水
        if (!(fill1 == 0))
        ans |= myCanMeasureWater(jug1Capacity, 0, jug2Capacity, fill2, targetCapacity);

        // 倒出2的水
        if (!(fill2 == 0))
        ans |= myCanMeasureWater(jug1Capacity, fill1, jug2Capacity, 0, targetCapacity);

        return ans;
    }

    /* 每次操作只会让水的总量增加或减少jug1Capacity(记为x)或jug2Capacity(记为y)，问题等价于ax + by = targetCapacity有解，
    由[裴蜀定理](https://oi-wiki.org/math/number-theory/bezouts/)，若有解，则targetCapacity一定为gcd(x,y)的倍数，否则违背:
    对任意a，b，满足gcd(x,y) | ax + by
    另一方面，若targetCapacity为gcd(x,y)的倍数，则一定有对应的a，b使得ax + by = targetCapacity。
    因此，只需判断targetCapacity是否为gcd(x,y)的倍数，然后考虑实际情况即可。
    */
    public boolean canMeasureWater_implementation2(int jug1Capacity, int jug2Capacity, int targetCapacity) {
        if (jug1Capacity == 0 || jug2Capacity == 0) return targetCapacity == 0 || jug1Capacity + jug2Capacity == targetCapacity;
        if (jug1Capacity + jug2Capacity < targetCapacity) return false;
        return targetCapacity % gcd(jug1Capacity, jug2Capacity) == 0;
    }

    private int gcd(int a, int b) {
        while (a % b != 0) {
            int r = a % b;
            a = b;
            b = r;
        }
        return b;
    }

    public static void main(String[] args) {
        Solution365 solu = new Solution365();
        // 这个用例要把栈设置得很大才能跑，不然会stackoverflow，`java -Xss128m Solution365.java`(jdk11往上可以直接这样运行一个single-file source-code program，不用先javac编译)
        // System.out.println(solu.canMeasureWater(104693, 104701, 324244));

        System.out.println(solu.canMeasureWater_implementation2(104693, 104701, 324244));
    }
}
