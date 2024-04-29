/*
url: https://leetcode.cn/problems/minimum-array-end/description/
LeetCode参考: https://leetcode.cn/problems/minimum-array-end/solutions/2759113/wei-yun-suan-jian-ji-xie-fa-pythonjavacg-nw8t/
标签: LeetCode第395场周赛, lowbit, 位运算
*/

public class Solution3133 {
    // 周赛时的解法，通过
    public long minEnd(int n, int x) {
        // 每个元素在x为1的位上也得都是1
        long num = x; // x的位上有0，把这些0单独拿出来看，其要变成n - 1。由于x在这些位上为0，最终&出来不会多冒出来1
        long add = n - 1;
        int p = 0;
        long ans = x;
        for (int i = 0; i < 64; i++) {
            if (((num >> i) & 1) > 0) {
                continue;
            }
            /* 这里要注意把1转成long，1左移超过位数的话不是变成0。见<https://blog.csdn.net/zjx409/article/details/37569055>，对Java，
            在移位运算中，如果被移位的操作数是int类型的，那么只会用到移位数的最低5位（这样刚好最多63）。
            如果是C++，见<https://learn.microsoft.com/zh-cn/cpp/cpp/left-shift-and-right-shift-operators-input-and-output?view=msvc-170>
            左移有符号数超过位数是未定义行为。 */
            if ((add & ((long)1 << p)) > 0) { // x在这一位上为0，add在这一位上为1
                ans |= ((long)1 << i);
            }
            p++;
        }
        return ans;
    }

    // 灵茶山艾府题解解法一，思路更清晰
    public long minEnd_implementation2(int n, int x) {
        n--;
        long ans = x;
        int i = 0, j = 0; // i在ans里找是0的位置，j遍历n - 1的有效位
        while ((n >> j) > 0) {
            while ((ans >> i & 1) > 0) {
                i++;
            }
            ans |= ((long)(n >> j & 1)) << i;
            i++;
            j++;
        }
        return ans;
    }

    // 灵茶山艾府题解解法二，用lowbit，非常巧妙!
    public long minEnd_implementation3(int n, int x) {
        n--;
        long ans = x;
        int j = 0; // j遍历n - 1的有效位
        long t = ~ans; // 把ans取反，用lowbit求ans中0的位置
        while ((n >> j) > 0) {
            long lowbit = t & (-t); // 获得lowbit，这是ans中最右的0的位置
            // 若n - 1现在要用的位是0，则ans这个位置上变0，若n - 1现在要用的位是1，则ans这个位置上变1，刚好可以用(n >> j & 1)与lowbit相乘
            ans |= (long)(n >> j & 1) * lowbit;
            j++;
            // 把t这一位1变成0，以免妨碍找ans中下一个0
            t ^= lowbit;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution3133 solu = new Solution3133();
        System.out.println(solu.minEnd(3, 4));
        System.out.println(solu.minEnd_implementation2(3, 4));
        System.out.println(solu.minEnd_implementation3(3, 4));
    }
}
