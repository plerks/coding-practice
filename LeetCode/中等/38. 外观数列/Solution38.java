// https://leetcode.cn/problems/count-and-say/

public class Solution38 {
    public String countAndSay(int n) {
        String ans = "1";
        for (int i = 1; i < n; i++) {
            ans = resolve(ans);
        }
        return ans;
    }

    private String resolve(String s) {
        StringBuilder sb = new StringBuilder();
        int num = s.charAt(0) - '0';
        int count = 1;
        for (int i = 1; i < s.length(); i++) {
            if (s.charAt(i) - '0' == num) {
                count++;
            }
            else {
                sb.append(count);
                sb.append(num);
                num = s.charAt(i) - '0';
                count = 1;
            }
        }
        sb.append(count);
        sb.append(num);
        return sb.toString();
    }

    public static void main(String[] args) {
        Solution38 solu = new Solution38();
        System.out.println(solu.countAndSay(4));
    }
}