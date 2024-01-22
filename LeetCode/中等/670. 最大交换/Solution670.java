/*
url: https://leetcode.cn/problems/maximum-swap/?envType=daily-question&envId=2024-01-22
LeetCode参考: https://leetcode.cn/problems/maximum-swap/solutions/1818457/zui-da-jiao-huan-by-leetcode-solution-lnd5/
我的题解: https://leetcode.cn/problems/maximum-swap/solutions/2615032/liang-chong-dui-cheng-de-si-lu-dan-shi-z-zo5s/
*/

import java.util.Arrays;

public class Solution670 {
    public int maximumSwap(int num) {
        /* 单纯枚举交换的两个位置需要O(n^2)时间，寻找更低时间的算法。
        若num数位数字是逆序，则其值为最大的，否则，对每个数位上的y，若其交换，其最大值为让其与y左侧第一个小于y的数位值x交换所得的值。
        */
        int[] map = new int[10];
        Arrays.fill(map, Integer.MAX_VALUE);
        String s = String.valueOf(num);
        int n = s.length();
        // 数位值只有0-9，用一个数组记录每个数字出现的最左位置
        map[s.charAt(0) - '0'] = 0;
        int ans = num;
        for (int i = 1; i < s.length(); i++) {
            // i位置上的数字记为y，x...y，x为y左侧最靠左的比y小的值
            int x, xPos;
            int y = s.charAt(i) - '0';
            map[y] = Math.min(map[y], i);
            int yPos = i; // yPos代表y在第几位
            for (int j = 0; j <= y; j++) { // 这里写j <= y是为了让y左侧即使没比y小的，也能让y自己与自己交换，减少判断代码
                if (map[j] != Integer.MAX_VALUE) { // 若这个比y小的数字出现了
                    x = j;
                    xPos = map[x];
                    int newVal = num + (int)((y - x) * Math.pow(10, n - 1 - xPos) + (x - y) * Math.pow(10, n - 1 - yPos));
                    ans = Math.max(ans, newVal);
                }
            }
        }
        return ans;
    }

    // 官方题解的解法，考虑一个数位与右侧交换
    public int maximumSwap_implementation2(int num) {
        String s = String.valueOf(num);
        int n = s.length();
        int maxDigit = s.charAt(n - 1) - '0';
        int maxPos = n - 1;
        int ans = num;
        for (int i = n - 2; i >= 0; i--) {
            int digit = s.charAt(i) - '0';
            if (digit > maxDigit) {
                maxDigit = digit;
                maxPos = i;
            }
            int newVal = num + (int)((maxDigit - digit) * Math.pow(10, n - 1 - i) + (digit - maxDigit) * Math.pow(10, n - 1 - maxPos));
            ans = Math.max(ans, newVal);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution670 solu = new Solution670();
        System.out.println(solu.maximumSwap(22341345));
        System.out.println(solu.maximumSwap_implementation2(22341345));
    }
}
