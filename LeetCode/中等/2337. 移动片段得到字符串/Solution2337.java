/*
url: https://leetcode.cn/problems/move-pieces-to-obtain-a-string/
LeetCode参考: https://leetcode.cn/problems/move-pieces-to-obtain-a-string/solutions/1855012/yi-dong-pian-duan-de-dao-zi-fu-chuan-by-0j7py/
*/

public class Solution2337 {
    public boolean canChange(String start, String target) {
        int i = 0, j = 0;
        int n = start.length();
        while (i < n && j < n) {
            while (i < n && start.charAt(i) == '_') i++;
            while (j < n && target.charAt(j) == '_') j++;
            if (i < n && j < n) {
                if (start.charAt(i) != target.charAt(j)) return false;
                if (start.charAt(i) == 'L' && i < j) return false;
                if (start.charAt(i) == 'R' && i > j) return false;
                i++;
                j++;
            }
        }
        // start和target的L+R数量可能不相同
        while (i < n) {
            if (start.charAt(i++) != '_') return false;
        }
        while (j < n) {
            if (target.charAt(j++) != '_') return false;
        }
        return true;
    }

    public static void main(String[] args) {
        Solution2337 solu = new Solution2337();
        System.out.println(solu.canChange("_L__R__R_", "L______RR"));
    }
}