/*
url: https://leetcode.cn/problems/find-the-punishment-number-of-an-integer/?envType=daily-question&envId=2023-10-25
LeetCode参考: https://leetcode.cn/problems/find-the-punishment-number-of-an-integer/solutions/2496001/qiu-yi-ge-zheng-shu-de-cheng-fa-shu-by-l-ht5e/
*/

public class Solution2698 {
    public int punishmentNumber(int n) {
        int ans = 0;
        for (int i = 0; i <= n; i++) {
            String s = String.valueOf(i * i);
            if (findSum(s, i, 0)) {
                ans += i * i;
            }
        }
        return ans;
    }

    private boolean findSum(String s, int target, int start) {
        // 这样写也行，不过用时相比下面的写法多了很多，看来Integer.parseInt(s.substring())的调用开销有点大
        /* if (start >= s.length()) return target == 0;
        for (int i = start + 1; i <= s.length(); i++) { // 列举第一个分割出的子串
            int sub = Integer.parseInt(s.substring(start, i));
            if (target - sub < 0) break;
            if (findSum(s, target - sub, i)) {
                return true;
            }
        }
        return false; */


        /* 参考https://leetcode.cn/problems/find-the-punishment-number-of-an-integer/solutions/2496001/qiu-yi-ge-zheng-shu-de-cheng-fa-shu-by-l-ht5e/，
        改了下写法，用sum减少Integer.parseInt(s.substring())的调用
        */
        if (start == s.length()) return target == 0;
        int sum = 0;
        for (int i = start; i < s.length(); i++) {
            sum = sum * 10 + s.charAt(i) - '0'; // 枚举出的第一个子串的值
            if (target - sum < 0) break;
            if (findSum(s, target - sum, i + 1)) {
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        Solution2698 solu = new Solution2698();
        System.out.println(solu.punishmentNumber(37));
    }
}
