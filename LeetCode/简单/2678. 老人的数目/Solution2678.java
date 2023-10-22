// https://leetcode.cn/problems/number-of-senior-citizens/?envType=daily-question&envId=2023-10-23

public class Solution2678 {
    public int countSeniors(String[] details) {
        int ans = 0;
        for (String s : details) {
            if (s.charAt(12) - '0' + 10 * (s.charAt(11) - '0') > 60) {
                ans++;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2678 solu = new Solution2678();
        System.out.println(solu.countSeniors(new String[]{"7868190130M7522","5303914400F9211","9273338290F4010"}));
    }
}
