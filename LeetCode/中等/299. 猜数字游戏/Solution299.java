// https://leetcode.cn/problems/bulls-and-cows/description/?envType=daily-question&envId=2024-03-10

public class Solution299 {
    public String getHint(String secret, String guess) {
        // bulls的情况简单，cows的情况想成bulls考虑完后把所有没匹配上的secret中的数字按类排好，让guess剩下的数字去凑
        // secret.length == guess.length
        int n = secret.length();
        int bulls = 0, cows = 0;
        int[] map = new int[10];
        for (int i = 0; i < n; i++) {
            int sDigit = secret.charAt(i) - '0';
            int gDigit = guess.charAt(i) - '0';
            if (sDigit == gDigit) {
                bulls++;
            }
            else {
                map[sDigit]++;
            }
        }
        for (int i = 0; i < n; i++) {
            int sDigit = secret.charAt(i) - '0';
            int gDigit = guess.charAt(i) - '0';
            if (sDigit != gDigit) {
                if (map[gDigit] > 0) {
                    cows++;
                    map[gDigit]--;
                }
            }
        }
        return bulls + "A" + cows + "B";
    }

    public static void main(String[] args) {
        Solution299 solu = new Solution299();
        // System.out.println(solu.getHint("1123", "0111"));
        System.out.println(solu.getHint("1122", "1222"));
    }
}
